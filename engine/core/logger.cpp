/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/logger.h"

#include <fmt/color.h>
#include <fmt/core.h>

namespace ProtonEngine::Core
{

LogLevel Logger::m_level = LogLevel::DEBUG;

void Logger::setLogLevel(const LogLevel level)
{
    m_level = level;
}

void Logger::logTrace(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::TRACE)
        fmt::print(fmt::fg(fmt::color::gray), "[TRACE]   {}:{} - {}", file, line, message);
}

void Logger::logDebug(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::DEBUG)
        fmt::print(fmt::fg(fmt::color::dark_gray), "[DEBUG]   {}:{} - {}", file, line, message);
}

void Logger::logInfo(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::DEBUG)
        fmt::print(fmt::fg(fmt::color::white), "[INFO]    {}:{} - {}", file, line, message);
}

void Logger::logWarning(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::DEBUG)
        fmt::print(fmt::fg(fmt::color::yellow), "[WARNING] {}:{} - {}", file, line, message);
}

void Logger::logError(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::DEBUG)
        fmt::print(fmt::fg(fmt::color::red), "[ERROR]   {}:{} - {}", file, line, message);
}

} // namespace ProtonEngine::Core