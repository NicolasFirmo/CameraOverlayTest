#pragma once

[[nodiscard]] constexpr uint8_t floatToUint8(float normalized) {
	return 0xff * std::clamp(normalized, 0.0F, 1.0F);
}