//
// Created by 王海明 on 2022/7/13.
//

#ifndef VULKANAPITUTORIAL_PROCESS_H
#define VULKANAPITUTORIAL_PROCESS_H

#ifdef _WIN32
#include <process.h>
#else

#include <unistd.h>

#endif

class Process {
public:
    static int getPid(){return (int)getpid();};
};


#endif //VULKANAPITUTORIAL_PROCESS_H
