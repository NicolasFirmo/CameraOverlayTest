#pragma once
#include <fmt/format.h>
#include <fmt/color.h>

#include <glad/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <array>
#include <map>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <algorithm>
#include <chrono>
#include <execution>
#include <numbers>
#include <numeric>
#include <thread>
#include <utility>

#include <cstdint>
#include <limits>
#include <sys/stat.h>
#include <sys/types.h>
#include <type_traits>

#ifdef PLATFORM_WINDOWS
// Slim Windows

// target Windows 8 or later
#define _WIN32_WINNT _WIN32_WINNT_WIN8
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN

#define WIN32_EXTRA_LEAN

#define NOIME
#define NOWINRES
#define NOGDICAPMASKS
//#define NOVIRTUALKEYCODES
//#define NOWINMESSAGES
//#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
//#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
//#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
//#define NOGDI // MAKEPOINTS
//#define NOUSER // Window
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
//#define NOMSG 
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS // SetWindowLongPtrA
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NOIME
#define NOPROXYSTUB
#define NOIMAGE
#define NO
#define NOTAPE
#define ANSI_ONLY

#define STRICT

#include <Windows.h>

#endif // PLATFORM_WINDOWS