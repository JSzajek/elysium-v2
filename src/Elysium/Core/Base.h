#pragma once

#include "Elysium/core/PlatformDetection.h"

#ifdef ELYSIUM_DEBUG
#if defined(ELYSIUM_PLATFORM_WINDOWS)
#define ELYSIUM_DEBUGBREAK() __debugbreak()
#elif defined(ELYSIUM_PLATFORM_LINUX)
#include <signal.h>
#define ELYSIUM_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define ELYSIUM_PROFILE				0
#define ELYSIUM_ENABLE_ASSERTS
#else
#define ELYSIUM_DEBUGBREAK()
#endif
