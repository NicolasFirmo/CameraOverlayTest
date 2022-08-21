#include "app.h"

#include "window.h"

#include "renderer/renderer.h"
#include "renderer/shader.h"

#include "events/mouse_event.h"
#include "events/window_size_event.h"

#include "utility/log.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

#include "core/sleeper.h"
#include "core/assert.h"

bool App::running = false;

App::ExitCode App::init() {
	profileTraceFunc();

	Window::init("StickTheStick", {.w = 600, .h = 480});
	Renderer::init();
	Renderer::setViewport({.size = Window::size()});

	resizeView(Window::size());

	Sleeper::init();

	return ExitCode::success;
}

App::ExitCode App::run() {
	profileTraceFunc();
	using namespace std::chrono;

	running = true;
	{
		while (running && !Window::closing()) {
			profileTraceScope("app run loop");
			Window::pollEvents();

			Renderer::setDrawColor(1.0F, 1.0F, 1.0F, 1.0F);
			Renderer::clear();

			Window::showFrame();
		}
	}

	shutdown();
	return ExitCode::success;
}

void App::shutdown() {
	profileTraceFunc();

	running = false;
	Renderer::shutdown();
	Window::shutdown();
}

void App::onEvent(Event&& evt) {
	debugLog("app: {}\n", evt);

	auto type = evt.getType();

	switch (type) {
	case Event::Type::windowSize: {
		resizeView(static_cast<WindowSizeEvent&>(evt).size);
		break;
	}
	case Event::Type::mouseButton: {
		break;
	}
	case Event::Type::mouseMove: {
		break;
	}
	default: break;
	}
}

void App::resizeView(const Size2<GLsizei>& size) {
	Renderer::setViewport({.size = size});
}