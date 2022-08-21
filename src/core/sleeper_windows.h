#pragma once

#include "utility/timer.h"

class Sleeper {
public:
	static constexpr int64_t wakeupError = 700;

	static void init();

	Sleeper();
	~Sleeper();
	Sleeper(const Sleeper&) = delete;
	Sleeper(Sleeper&& other) noexcept;
	Sleeper& operator=(const Sleeper&) = delete;
	Sleeper& operator=(Sleeper&& other) noexcept;

	void sleep(int64_t microseconds);
	void preciseSync(int64_t microseconds, const Timer& timer);

private:
	HANDLE timer_;
};