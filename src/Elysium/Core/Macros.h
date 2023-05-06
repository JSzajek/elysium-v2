#pragma once

#define ELYSIUM_EXPAND_MACRO(x) x
#define ELYSIUM_STRINGIFY_MACRO(x) #x

#define ELYSIUM_EXPAND_MACRO_STRING(x) ELYSIUM_STRINGIFY_MACRO(x)

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define COUNT_OF(A) (sizeof(A) / sizeof(*A))
