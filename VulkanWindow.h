//
// Created by 王海明 on 2022/7/4.
//
// 所有窗口相关，glfw相关，封装在此类中，对其他类屏蔽glfw
#pragma once
#include "Headers.h"

class VulkanWindow {

public:
    VulkanWindow(int width,int height,const char* windowName);
    ~VulkanWindow();

    static std::vector<const char*> getRequiredExtensions();
    bool shouldClose();
    void pollEvents();
private:
    GLFWwindow* window;
    VkSurfaceKHR  surface;
public:
    void createSurface();
    void destroySurface();
    VkSurfaceKHR& getSurface();

private:
    static bool isInitialized;

};


