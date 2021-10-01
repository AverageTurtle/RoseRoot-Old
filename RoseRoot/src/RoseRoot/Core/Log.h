#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace RoseRoot 
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define RR_CORE_FATAL(...) ::RoseRoot::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define RR_CORE_ERROR(...) ::RoseRoot::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RR_CORE_WARN(...)  ::RoseRoot::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RR_CORE_INFO(...)  ::RoseRoot::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RR_CORE_TRACE(...) ::RoseRoot::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Cleint log macros
#define RR_FATAL(...)      ::RoseRoot::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define RR_ERROR(...)      ::RoseRoot::Log::GetClientLogger()->error(__VA_ARGS__)
#define RR_WARN(...)       ::RoseRoot::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RR_INFO(...)       ::RoseRoot::Log::GetClientLogger()->info(__VA_ARGS__)
#define RR_TRACE(...)      ::RoseRoot::Log::GetClientLogger()->trace(__VA_ARGS__)