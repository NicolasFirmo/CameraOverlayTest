#include "renderer.h"

#include "geometric/point.hpp"

#include "utility/tracer.h"

void Renderer::init() {
	profileTraceFunc();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

}

void Renderer::shutdown() {
	profileTraceFunc();
}

void Renderer::setViewport(const Rect<GLint, GLsizei>& rect) {
	const auto [x, y] = rect.pos;
	const auto [w, h] = rect.size;
	glViewport(x, y, w, h);
}

void Renderer::setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}