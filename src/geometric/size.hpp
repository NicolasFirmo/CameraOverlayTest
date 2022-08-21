#pragma once

template <typename T>
struct Size2 {
	T w{0}, h{0};

	constexpr Size2& operator*=(const T& value) {
		w *= value;
		h *= value;
		return *this;
	}

	[[nodiscard]] constexpr Size2 operator*(const T& value) const {
		return {.w = w * value, .h = h * value};
	}
};

template <typename T>
[[nodiscard]] constexpr Size2<T> operator*(const T& value, const Size2<T>& size) {
	return {.w = size.w * value, .h = size.w * value};
}