#pragma once

#include "spdlog/spdlog.h"


namespace Minity {

	class Log {
	private:
        static std::shared_ptr<spdlog::logger> m_CoreLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
	public:
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }
		~Log(){};
        static void Init();
	};

}  // namespace Minity

#define MN_CORE_TRACE(...)   ::Minity::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MN_CORE_INFO(...)    ::Minity::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MN_CORE_WARN(...)    ::Minity::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MN_CORE_ERROR(...)   ::Minity::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MN_CORE_FATAL(...)   ::Minity::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define MN_TRACE(...) ::Minity::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MN_INFO(...)  ::Minity::Log::GetClientLogger()->info(__VA_ARGS__)
#define MN_WARN(...)  ::Minity::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MN_ERROR(...) ::Minity::Log::GetClientLogger()->error(__VA_ARGS__)
#define MN_FATAL(...) ::Minity::Log::GetClientLogger()->critical(__VA_ARGS__)

#define MN_CORE_ASSERT(x, ...) { if(!(x)) { MN_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define MN_ASSERT(x, ...) { if(!(x)) { MN_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
