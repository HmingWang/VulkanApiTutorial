//
// Created by 王海明 on 2022/7/13.
//

#pragma once

#include "Headers.h"

#define NAME(x) #x

enum class LogLevel : uint8 {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5,
    DISABLED = 6,
};

class Log {
public :
    static Log &getInstance();

    bool shouldLog(LogLevel level);

    void setLogLevel(LogLevel level);

    [[nodiscard]] LogLevel getLogLevel() const;

    template<typename Format, typename... Args>
    inline void
    outMessage(LogLevel level, std::string &&file, std::string &&func, int &&line, Format &&fmt, Args &&... args) {
        outMessage(level, fmt::sprintf("[%s][%d][%5s][%16.16s][%3d]:%s",
                                       getTimestampStr().c_str(),
                                       Process::getPid(), getLogLevelName(level), func, line,
                                       fmt::format(std::forward<Format>(fmt), std::forward<Args>(args)...)));
    };

private:
    Log();

    ~Log() = default;

    static void outMessage(LogLevel, std::string &&msg);

    static std::string getLogLevelName(LogLevel level) {
        static std::string logLevelName[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
        return logLevelName[static_cast<int>(level)];
    }

private:
    LogLevel logLevel;

    static std::string getTimestampStr();
};


#define log Log::getInstance()
#define LOG_TRACE(...)  log.outMessage(LogLevel::TRACE,__FILE__,__FUNCTION__, __LINE__,__VA_ARGS__)
#define LOG_DEBUG(...)  log.outMessage(LogLevel::DEBUG,__FILE__,__FUNCTION__, __LINE__,__VA_ARGS__)
#define LOG_INFO(...)  log.outMessage(LogLevel::INFO,__FILE__,__FUNCTION__, __LINE__,__VA_ARGS__)
#define LOG_WARN(...)  log.outMessage(LogLevel::WARN,__FILE__,__FUNCTION__, __LINE__,__VA_ARGS__)
#define LOG_ERROR(...)  log.outMessage(LogLevel::ERROR,__FILE__,__FUNCTION__, __LINE__,__VA_ARGS__)
#define LOG_FATAL(...)  log.outMessage(LogLevel::FATAL,__FILE__,__FUNCTION__, __LINE__,__VA_ARGS__)
