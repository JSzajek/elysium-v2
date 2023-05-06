#pragma once

#include "Elysium/Core/Base.h"
#include "Elysium/Core/Macros.h"

#include "Elysium/Logging/Log.h"

#include <filesystem>

#ifdef ELYSIUM_ENABLE_ASSERTS

// Alternatively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define ELYSIUM_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ELYSIUM##type##ERROR(msg, __VA_ARGS__); ELYSIUM_DEBUGBREAK(); } }
#define ELYSIUM_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ELYSIUM_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define ELYSIUM_INTERNAL_ASSERT_NO_MSG(type, check) ELYSIUM_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ELYSIUM_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define ELYSIUM_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ELYSIUM_INTERNAL_ASSERT_GET_MACRO(...) ELYSIUM_EXPAND_MACRO( ELYSIUM_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ELYSIUM_INTERNAL_ASSERT_WITH_MSG, ELYSIUM_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define ELYSIUM_ASSERT(...) ELYSIUM_EXPAND_MACRO( ELYSIUM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define ELYSIUM_CORE_ASSERT(...) ELYSIUM_EXPAND_MACRO( ELYSIUM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define ELYSIUM_ASSERT(...)
#define ELYSIUM_CORE_ASSERT(...)
#endif