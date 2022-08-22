#pragma once

#include "geometric/size.hpp"

class Window {
public:
	static void init(const char* title, const Size2<GLsizei>& size = {.w = 800, .h = 600},
					 bool vsyncEnabled = true);
	static void shutdown();

	static bool closing();

	static void pollEvents();

	static void showFrame();

	[[nodiscard]] static const auto& size() { return size_; }
	[[nodiscard]] static auto width() { return size_.w; }
	[[nodiscard]] static auto height() { return size_.h; }
	[[nodiscard]] static auto aspectRatio() { return double(size_.w) / size_.h; }

	static void setVsync(bool enabled);
	[[nodiscard]] static bool isVsyncOn() { return vsync_ != 0; }

	static void setTitle(const char* title);

private:
	static LRESULT CALLBACK eventCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	// static void mouseButtonCallback(...
	// static void mouseMoveCallback(...
	// static void windowSizeCallback(...

	static HWND handle_;
	static HDC deviceContext_;
	static HGLRC renderingContext_;

	static MSG message_;

	static Size2<GLsizei> size_;
	static int vsync_;
	static bool closing_;
};