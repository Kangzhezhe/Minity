#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Minity {
    std::shared_ptr<spdlog::logger> Log::m_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::m_ClientLogger;

    void Log::Init() {
        // Initialize core logger
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_CoreLogger = spdlog::stdout_color_mt("CORE");
        m_CoreLogger->set_level(spdlog::level::trace);

        // Initialize client logger
        m_ClientLogger = spdlog::stdout_color_mt("APP");
        m_ClientLogger->set_level(spdlog::level::trace);
    }
}

