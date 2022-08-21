#include "sleeper_unix.h"

#include "core/assert.h"

#include <ctime>

void Sleeper::init() {}

void Sleeper::sleep(int64_t microseconds) {
	const timespec requestedTime{.tv_sec = 0, .tv_nsec = microseconds * 1'000};
	nanosleep(&requestedTime, nullptr);
}

void Sleeper::preciseSync(int64_t microseconds, const Timer& timer) {
	sleep(microseconds - wakeupError - timer.getMicrosecondsElapsed());
	while (timer.getMicrosecondsElapsed() < microseconds) {}
}