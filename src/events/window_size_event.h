#pragma once

#include "event.h"

#include "geometric/size.hpp"

struct WindowSizeEvent : public Event {
	WindowSizeEvent(Size2<int> size) : size(size) {}

	[[nodiscard]] constexpr Type getType() const override { return Type::windowSize; };
	[[nodiscard]] std::string toString() const override;

	Size2<int> size;
};