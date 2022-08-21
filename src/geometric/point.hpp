#pragma once

#include "utility/concepts.hpp"

template <typename T>
struct Point2Cartesian;
template <typename T>
struct Point2Polar;

template <typename T>
using Point2 = Point2Cartesian<T>;

template <typename T>
constexpr T length2(const Point2Cartesian<T>& pt0, const Point2Cartesian<T>& pt1 = {0, 0}) {
	const auto [x, y] = pt0 - pt1;
	return x * x + y * y;
}

template <typename T>
T length(const Point2Cartesian<T>& pt0, const Point2Cartesian<T>& pt1 = {0, 0}) {
	return std::sqrt(length2(pt0, pt1));
}

// Cartesian

template <typename T>
struct Point2Cartesian {
	T x{0}, y{0};

	template <typename OtherT>
	constexpr operator Point2Cartesian<OtherT>() const {
		return {.x = static_cast<OtherT>(x), .y = static_cast<OtherT>(y)};
	}

	template <typename OtherT>
	operator Point2Polar<OtherT>() const {
		return {.r	= static_cast<OtherT>(length(*this)),
				.th = static_cast<OtherT>(std::atan2(y, x))};
	}

	constexpr Point2Cartesian& operator+=(const Point2Cartesian& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	[[nodiscard]] constexpr Point2Cartesian operator+(const Point2Cartesian& other) const {
		return {.x = x + other.x, .y = y + other.y};
	}

	[[nodiscard]] constexpr Point2Cartesian operator-(const Point2Cartesian& other) const {
		return {.x = x - other.x, .y = y - other.y};
	}
	[[nodiscard]] constexpr Point2Cartesian operator*(const T& value) const {
		return {.x = x * value, .y = y * value};
	}
};

template <typename T>
constexpr Point2Cartesian<T> operator*(const T& value, const Point2Cartesian<T>& point) {
	return {.x = point.x * value, .y = point.x * value};
}

// Polar

template <typename T>
struct Point2Polar {
	T r{0}, th{0};

	template <typename OtherT>
	constexpr operator Point2Polar<OtherT>() const {
		return {.r = static_cast<OtherT>(r), .th = static_cast<OtherT>(th)};
	}

	template <typename OtherT>
	operator Point2Cartesian<OtherT>() const {
		return {.x = static_cast<OtherT>(r * std::cos(th)),
				.y = static_cast<OtherT>(r * std::sin(th))};
	}

	// constexpr Point2Polar& operator+=(const Point2Polar& other) {}

	//[[nodiscard]] constexpr Point2Polar operator+(const Point2Polar& other) const {}

	//[[nodiscard]] constexpr Point2Polar operator-(const Point2Polar& other) const {}
	//[[nodiscard]] constexpr Point2Polar operator*(const T& value) const {}
};

// template <typename T>
// constexpr Point2Polar<T> operator*(const T& value, const Point2Polar<T>& point) {}