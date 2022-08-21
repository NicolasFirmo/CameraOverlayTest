#pragma once

template <class T>
concept Stringable = requires(T a) {
	{ a.toString() } -> std::convertible_to<std::string>;
};