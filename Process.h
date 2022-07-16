//
// Created by 王海明 on 2022/7/13.
//

#pragma once

#ifdef _WIN32
#include <process.h>
#define GET_PID _getpid
#else
#define GET_PID getpid
#include <unistd.h>

#endif

class Process {
public:
    static int getPid(){return (int) GET_PID();};
};