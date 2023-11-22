/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/proton_interface.h"

#include <string_view>
#include <string.h>

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif


namespace ProtonEngine::Core
{

enum class LogLevel
{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARNING = 3,
    ERROR = 4
};

class PROTON_API Logger
{
public:
    Logger() = delete;

    static void setLogLevel(LogLevel level);

    static void logTrace(std::string_view file, int line, std::string_view message);
    static void logDebug(std::string_view file, int line, std::string_view message);
    static void logInfo(std::string_view file, int line, std::string_view message);
    static void logWarning(std::string_view file, int line, std::string_view message);
    static void logError(std::string_view file, int line, std::string_view message);

private:
    static LogLevel m_level;

    static void printMessage(std::string_view message);
};

#ifndef DISTRIBUTION_BUILD
#define PROTON_LOG_TRACE(message) ProtonEngine::Core::Logger::logTrace(__FILENAME__, __LINE__, message);
#define PROTON_LOG_DEBUG(message) ProtonEngine::Core::Logger::logDebug(__FILENAME__, __LINE__, message);
#define PROTON_LOG_INFO(message) ProtonEngine::Core::Logger::logInfo(__FILENAME__, __LINE__, message);
#define PROTON_LOG_WARNING(message) ProtonEngine::Core::Logger::logWarning(__FILENAME__, __LINE__, message);
#define PROTON_LOG_ERROR(message) ProtonEngine::Core::Logger::logError(__FILENAME__, __LINE__, message);
#else
#define PROTON_LOG_TRACE(message)
#define PROTON_LOG_DEBUG(message)
#define PROTON_LOG_INFO(message)
#define PROTON_LOG_WARNING(message)
#define PROTON_LOG_ERROR(message)
#endif

} // namespace ProtonEngine::Core