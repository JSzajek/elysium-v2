#pragma once

#include "Elysium/core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory.h>

namespace Elysium
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#if ELYSIUM_DEBUG
// Core log macros
#define ELYSIUM_CORE_TRACE(...)	::Elysium::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ELYSIUM_CORE_INFO(...)	::Elysium::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ELYSIUM_CORE_WARN(...)	::Elysium::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ELYSIUM_CORE_ERROR(...)	::Elysium::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ELYSIUM_CORE_FATAL(...)	::Elysium::Log::GetCoreLogger()->critical(__VA_ARGS__)
#else
// Release build stripped
#define ELYSIUM_CORE_TRACE(...)
#define ELYSIUM_CORE_INFO(...)
#define ELYSIUM_CORE_WARN(...)	::Elysium::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ELYSIUM_CORE_ERROR(...) ::Elysium::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ELYSIUM_CORE_FATAL(...)	::Elysium::Log::GetCoreLogger()->critical(__VA_ARGS__)
#endif

#if ELYSIUM_DEBUG
	// Client log macros
#define ELYSIUM_TRACE(...)		::Elysium::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ELYSIUM_INFO(...)		::Elysium::Log::GetClientLogger()->info(__VA_ARGS__)
#define ELYSIUM_WARN(...)		::Elysium::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ELYSIUM_ERROR(...)		::Elysium::Log::GetClientLogger()->error(__VA_ARGS__)
#define ELYSIUM_FATAL(...)		::Elysium::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	// Release build stripped
#define ELYSIUM_TRACE(...)		::Elysium::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ELYSIUM_INFO(...)		::Elysium::Log::GetClientLogger()->info(__VA_ARGS__)
#define ELYSIUM_WARN(...)		::Elysium::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ELYSIUM_ERROR(...)		::Elysium::Log::GetClientLogger()->error(__VA_ARGS__)
#define ELYSIUM_FATAL(...)		::Elysium::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif