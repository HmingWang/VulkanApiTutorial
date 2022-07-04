//
// Created by 王海明 on 2022/7/4.
//

#pragma once
#include "Headers.h"
#include "VulkanWindow.h"

class VulkanApplication {
public:
    void run();
    static VulkanApplication& getInstance();
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanUp();

    VulkanWindow* window;
    const int width=800;
    const int height=600;
    const std::string appName="hello world";

};

#define theApp VulkanApplication::getInstance()