#pragma once

class Timer {
public:
	using clock = std::chrono::high_resolution_clock;

	void startCounting();
	[[nodiscard]] int64_t getMicrosecondsElapsed() const;
	[[nodiscard]] double getSecondsElapsed() const;

private:
	clock::time_point startTime_ = clock::now();
};