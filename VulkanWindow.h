//
// Created by 王海明 on 2022/7/4.
//

#pragma once
#include "Headers.h"

class VulkanWindow {

public:
    VulkanWindow(int width,int height,const char* windowName);
    ~VulkanWindow();

    static std::vector<const char*> getRequiredExtensions();

private:
    GLFWwindow* window;

    static bool isInitialized;

};


