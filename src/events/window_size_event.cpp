#include "window_size_event.h"

std::string WindowSizeEvent::toString() const {
	return fmt::format("WindowSizeEvent{{w:{}, h:{}}}", size.w, size.h);
}