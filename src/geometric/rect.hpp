#pragma once
#include "size.hpp"
#include "point.hpp"

template <typename PointT, typename SizeT = PointT>
struct Rect {
	Point2<PointT> pos{};
	Size2<SizeT> size{};
};