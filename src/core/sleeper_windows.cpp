#include "sleeper_windows.h"

#include "core/assert.h"

#include "timeapi.h"

void Sleeper::init() {
	timeBeginPeriod(1);
}

Sleeper::Sleeper() {
	debugAssert((timer_ = CreateWaitableTimer(NULL, TRUE, NULL)),
				"Unable to create waitable timer for Sleeper! (Windows)");
}

Sleeper::~Sleeper() {
	if (timer_)
		CloseHandle(timer_);
}

Sleeper::Sleeper(Sleeper&& other) noexcept : timer_(other.timer_) {
	other.timer_ = nullptr;
}

Sleeper& Sleeper::operator=(Sleeper&& other) noexcept {
	timer_		 = other.timer_;
	other.timer_ = nullptr;
	return *this;
}

void Sleeper::sleep(int64_t microseconds) {
	LARGE_INTEGER li{{0}};
	li.QuadPart = static_cast<LONGLONG>(-microseconds * 10);

	debugAssert(SetWaitableTimer(timer_, &li, 0, NULL, NULL, FALSE),
				"Unable to set waitable timer for Sleeper! (Windows)");

	WaitForSingleObject(timer_, INFINITE);
}

void Sleeper::preciseSync(int64_t microseconds, const Timer& timer) {
	sleep(microseconds - wakeupError - timer.getMicrosecondsElapsed());
	while (timer.getMicrosecondsElapsed() < microseconds) {}
}