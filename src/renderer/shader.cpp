#include "shader.h"

#include "utility/log.hpp"
#include "utility/tracer.h"

#include "core/assert.h"

Shader::Shader(const std::string& name) {
	profileTraceFunc();

	id_ = glCreateProgram();

	std::array<GLuint, std::size(shaderTypes)> shaderIds{0};

	auto curerntShaderId = shaderIds.begin();
	for (auto&& [type, extension] : shaderTypes) {
		auto shaderFile = loadShaderFile(name, extension);
		auto shaderSrc	= parseSource(shaderFile);

		*curerntShaderId = compileShader(type, shaderSrc.c_str());

		glAttachShader(id_, *curerntShaderId);

		++curerntShaderId;
	}

	glLinkProgram(id_);
	glValidateProgram(id_);

	for (auto&& shaderId : shaderIds)
		if (shaderId != 0)
			glDeleteShader(shaderId);

	uniforms_.shrink_to_fit();
	loadUniformLocations();
}

Shader::~Shader() {
	profileTraceFunc();

	if (id_)
		glDeleteProgram(id_);
}

Shader::Shader(Shader&& other) : id_(std::move(other.id_)), uniforms_(std::move(other.uniforms_)) {
	other.id_ = 0;
}

Shader& Shader::operator=(Shader&& other) {
	id_		  = std::move(other.id_);
	uniforms_ = std::move(other.uniforms_);

	other.id_ = 0;

	return *this;
}

std::ifstream Shader::loadShaderFile(std::string_view name, std::string_view extension) {
	profileTraceFunc();

	using namespace std::string_literals;
	std::string fileName =
		"assets/shaders/"s + name.data() + '/' + name.data() + '.' + extension.data() + ".glsl";

	std::ifstream file{fileName};

	debugAssert(
		file.is_open(),
		fmt::format("{0}.{1}.glsl not found in assets/shaders/{0}/ folder!\n", name, extension));

	return file;
}

std::string Shader::parseSource(std::ifstream& file) {
	profileTraceFunc();

	std::string src{};

	for (std::string line; std::getline(file, line); src += line + '\n') {
		if (line.find("uniform") == std::string::npos)
			continue;

		const auto semicolonPos =
			std::find_if(std::execution::par_unseq, line.rbegin(), line.rend(),
						 [](const char c) { return c != ' ' && c != '\t'; });
		const auto uniformRBeginPos = semicolonPos + 1;

		const auto uniformREndPos =
			std::find_if(std::execution::par_unseq, uniformRBeginPos, line.rend(),
						 [](const char c) { return c == ' ' || c == '\t'; });

		uniforms_.emplace_back(std::string{uniformREndPos.base(), uniformRBeginPos.base()}, -1);

		debugLog("{} uniform found!\n", uniforms_.back().name);
	}

	return src;
}

GLuint Shader::compileShader(GLenum type, const GLchar* source) {
	profileTraceFunc();

	auto shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, nullptr);
	glCompileShader(shaderId);

	if constexpr (DEBUG) {
		auto success = GL_TRUE;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar message[1024];
			glGetShaderInfoLog(shaderId, sizeof(message), nullptr, message);
			fmt::print(stderr, "Failed to compile {}shader: {}",
					   type == GL_VERTEX_SHADER	  ? "vertex " :
					   type == GL_FRAGMENT_SHADER ? "fragment " :
													"",
					   message);
			debugBreak();
			glDeleteShader(shaderId);
			return 0;
		}
	}

	return shaderId;
};

void Shader::bind() {
	glUseProgram(id_);
}

void Shader::loadUniformLocations() {
	profileTraceFunc();

	bind();

	for (Uniform& uniform : uniforms_) {
		uniform.location = glGetUniformLocation(id_, uniform.name.c_str());
		debugLog("{} uniform {}!\n", uniform.name,
				 uniform.location == -1 ? "not loaded" : "loaded");
	}
}