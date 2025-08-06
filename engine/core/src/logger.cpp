/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/logger.h"

#include "color.h"

// #include <fmt/color.h>
// #include <fmt/core.h>
#include <format>
#include <print>
#include <utility>

namespace ProtonEngine::Core
{

LogLevel Logger::m_level = LogLevel::DEBUG;

static void printWithForegroundColor(Color color, std::string_view message)
{
    const auto red = static_cast<unsigned char>(std::to_underlying(color) >> 16 & 0xFF);
    const auto green = static_cast<unsigned char>(std::to_underlying(color) >> 8 & 0xFF);
    const auto blue = static_cast<unsigned char>(std::to_underlying(color) & 0xFF);

    std::println("\033[38;2;{};{};{}m {} \033[0m", red, green, blue, message);
}

void Logger::setLogLevel(const LogLevel level)
{
    m_level = level;
}

void Logger::logTrace(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::TRACE)
        printWithForegroundColor(Color::gray, std::format("[TRACE]   {}:{} - {}", file, line, message));
}

void Logger::logDebug(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::DEBUG)
        printWithForegroundColor(Color::dark_gray, std::format("[DEBUG]   {}:{} - {}", file, line, message));
}

void Logger::logInfo(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::INFO)
        printWithForegroundColor(Color::white, std::format("[INFO]   {}:{} - {}", file, line, message));
}

void Logger::logWarning(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::WARNING)
        printWithForegroundColor(Color::yellow, std::format("[WARN]   {}:{} - {}", file, line, message));
}

void Logger::logError(std::string_view file, int line, std::string_view message)
{
    if (m_level <= LogLevel::ERROR)
        printWithForegroundColor(Color::red, std::format("[ERROR]   {}:{} - {}", file, line, message));
}

} // namespace ProtonEngine::Core