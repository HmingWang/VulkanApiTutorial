//
// Created by 王海明 on 2022/7/13.
//

#include "Log.h"

Log &Log::getInstance() {
    static Log instance{};
    return instance;

}

void Log::setLogLevel(LogLevel level) {
    logLevel = level;
}

bool Log::shouldLog(LogLevel level) {
    return level>=logLevel;
}

LogLevel Log::getLogLevel() const {
    return logLevel;
}

std::string Log::getTimestampStr()
{
    time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::tm aTm{};
    localtime_r(&tt, &aTm);

    //       YYYY   year
    //       MM     month (2 digits 01-12)
    //       DD     day (2 digits 01-31)
    //       HH     hour (2 digits 00-23)
    //       MM     minutes (2 digits 00-59)
    //       SS     seconds (2 digits 00-59)
    try
    {
        return fmt::sprintf("%04d-%02d-%02d %02d:%02d:%02d",aTm.tm_year + 1900, aTm.tm_mon + 1, aTm.tm_mday, aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
    }
    catch (std::exception const& ex)
    {
        fprintf(stderr, "Failed to initialize timestamp part of log filename! %s", ex.what());
        fflush(stderr);
        return "";
    }

}

void Log::outMessage(LogLevel level, std::string &&msg) {
    FILE* out= stdout;
    if(level>LogLevel::ERROR)
        out=stderr;

    fprintf(out,"%s\n",msg.c_str());
}

Log::Log():logLevel{LogLevel::TRACE} {
}

