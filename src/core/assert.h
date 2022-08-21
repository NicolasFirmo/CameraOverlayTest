#pragma once

#include "core/macros.h"

#include "utility/log.hpp"
#include "utility/file_path.h"

#if defined(PLATFORM_WINDOWS)
static constexpr auto srcDirName = "src\\";
#elif defined(PLATFORM_UNIX)
static constexpr auto srcDirName = "src/";
#else
#error Only Windows and Unix supported for now!
#endif

#ifndef NDEBUG
#define debugAssert(x, message)                                                                    \
	if (!(x)) {                                                                                    \
		static constexpr auto fileName = getRelativePath(__FILE__, srcDirName);                    \
		debugLog("assertion falied on line {} of {} in {}\n\t{}\n", __LINE__, funcSign, fileName,  \
				 message);                                                                         \
		debugBreak();                                                                              \
	}
#else
#if defined(_MSC_VER)
#define debugAssert(x, message)                                                                    \
	__pragma(warning(push)) __pragma(warning(disable : 4834 4552 4555 6031)) x;                    \
	__pragma(warning(pop))
#elif defined(__GNUC__) || defined(__clang__)
#define debugAssert(x, message)                                                                    \
	_Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wunused-value\"") x;         \
	_Pragma("GCC diagnostic pop")
#else
#define debugAssert(x, message) x
#endif // defined(__GNUC__) || defined(__clang__)
#endif // NDEBUG