#pragma once

#include "geometric/point.hpp"
#include "geometric/rect.hpp"

class Renderer {
public:
	static void init();
	static void shutdown();

	static void setViewport(const Rect<GLint, GLsizei>& rect);

	static void setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void clear();
};