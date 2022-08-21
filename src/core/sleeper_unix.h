#pragma once

#include "utility/timer.h"

class Sleeper {
public:
	static constexpr int64_t wakeupError = 200;

	static void init();

	Sleeper()  = default;
	~Sleeper() = default;

	Sleeper(const Sleeper&)				= delete;
	Sleeper(Sleeper&& other)			= default;
	Sleeper& operator=(const Sleeper&)	= delete;
	Sleeper& operator=(Sleeper&& other) = default;

	void sleep(int64_t microseconds);
	void preciseSync(int64_t microseconds, const Timer& timer);
};