#include "window_windows.h"

#include "app.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/tracer.h"

#include "core/assert.h"

HWND Window::handle_			= nullptr;
HDC Window::deviceContext_		= nullptr;
HGLRC Window::renderingContext_ = nullptr;

MSG Window::message_{};

Size2<GLsizei> Window::size_{};
int Window::vsync_{};
bool Window::closing_ = false;

void Window::init(const char* title, const Size2<GLsizei>& size, const bool vsyncEnabled) {
	profileTraceFunc();

	size_ = size;

	WNDCLASSEXA windowClass{};
	windowClass.cbSize		  = sizeof(WNDCLASSEXA);
	windowClass.style		  = CS_OWNDC;
	windowClass.lpfnWndProc	  = Window::eventCallback;
	windowClass.hInstance	  = GetModuleHandle(nullptr); //  get hInstance
	windowClass.lpszClassName = "StaticWindowsWindow";

	RegisterClassExA(&windowClass);

	handle_ = CreateWindowExA(NULL, windowClass.lpszClassName, title, WS_CAPTION | WS_SYSMENU, 0, 0,
							  size.w, size.h, nullptr, nullptr, windowClass.hInstance, nullptr);

	deviceContext_ = GetDC(handle_);

	PIXELFORMATDESCRIPTOR pfd{};
	pfd.nSize		 = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	 = 1;
	pfd.dwFlags		 = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType	 = PFD_TYPE_RGBA;
	pfd.cColorBits	 = 32;
	pfd.cDepthBits	 = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType	 = PFD_MAIN_PLANE;

	const auto pixelFormat = ChoosePixelFormat(deviceContext_, &pfd);
	debugAssert(pixelFormat != 0,
				"Unable to choose pixel format for the specified descriptor! (Windows)");
	SetPixelFormat(deviceContext_, pixelFormat, &pfd);

	renderingContext_ = wglCreateContext(deviceContext_);

	wglMakeCurrent(deviceContext_, renderingContext_);

	debugAssert(gladLoaderLoadGL(), "Failed to initialize OpenGL context!");

	ShowWindow(handle_, SW_SHOW);

	debugLog("OpenGL info:\n");
	debugLog("\tVendor: {:s}\n", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	debugLog("\tRenderer: {:s}\n", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	debugLog("\tVersion: {:s}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void Window::shutdown() {
	profileTraceFunc();

	wglMakeCurrent(deviceContext_, NULL);
	wglDeleteContext(renderingContext_);

	DestroyWindow(handle_);
}

bool Window::closing() {
	return closing_;
}

void Window::pollEvents() {
	profileTraceFunc();

	while (PeekMessageA(&message_, handle_, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message_);
		DispatchMessageA(&message_);
	}
}

void Window::showFrame() {
	profileTraceFunc();

	SwapBuffers(deviceContext_);
}

void Window::setVsync(bool enabled) {
	vsync_ = enabled ? 1 : 0;
}

void Window::setTitle(const char* title) {}

LRESULT CALLBACK Window::eventCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE: {
		closing_ = true;
		break;
	}
	case WM_MOUSEMOVE: {
		App::onEvent(MouseMoveEvent{
			{.x = static_cast<MouseMoveEvent::point_value_type>(LOWORD(lParam)),
			 .y = static_cast<MouseMoveEvent::point_value_type>(HIWORD(lParam))}
		});
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP: {
		const auto button =
			message == WM_LBUTTONDOWN || message == WM_LBUTTONUP ? MouseButton::left :
			message == WM_RBUTTONDOWN || message == WM_RBUTTONUP ? MouseButton::right :
																   MouseButton::middle;
		const auto action =
			message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN ?
				MouseAction::pressed :
				MouseAction::released;

		const auto shift = wParam & MK_SHIFT ? MouseMods::shift : MouseMods::none;
		const auto ctrl	 = wParam & MK_CONTROL ? MouseMods::ctrl : MouseMods::none;
		const auto alt	 = GetKeyState(VK_MENU) < 0 ? MouseMods::alt : MouseMods::none;
		const auto mods	 = static_cast<MouseMods>(shift | ctrl | alt);

		App::onEvent(MouseButtonEvent{button, action, mods});
		break;
	}
	}

	return DefWindowProcA(handle, message, wParam, lParam);
}
