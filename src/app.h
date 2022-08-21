#pragma once

#include "events/event.h"

#include "geometric/size.hpp"

class App {
public:
	enum class ExitCode {
		success = 0,
		applicationError
	};

	static ExitCode init();
	static ExitCode run();
	static void shutdown();

	static void onEvent(Event&& evt);

	static void resizeView(const Size2<GLsizei>& size);

private:
	static bool running;
};