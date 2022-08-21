#pragma once

[[nodiscard]] constexpr auto getRelativePath(std::string_view path, std::string_view dir) {
	auto&& pos = path.rfind(dir);
	return path.substr(pos + dir.size());
}