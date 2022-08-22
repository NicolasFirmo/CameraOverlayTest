#pragma once

#include "event.h"

#include "geometric/size.hpp"

struct WindowSizeEvent : public Event {
	using size_value_type = int;

	WindowSizeEvent(Size2<size_value_type> size) : size(size) {}

	[[nodiscard]] constexpr Type getType() const override { return Type::windowSize; };
	[[nodiscard]] std::string toString() const override;

	Size2<size_value_type> size;
};