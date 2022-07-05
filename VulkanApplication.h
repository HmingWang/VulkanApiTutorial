//
// Created by 王海明 on 2022/7/4.
//

#pragma once

#include "Headers.h"
#include "VulkanWindow.h"
#include "VulkanInstance.h"

class VulkanApplication {
public:
    void run();

    static VulkanApplication &getInstance();

    VkInstance& getVkInstance();
    bool isEnableValidationLayers();

private:
    void initWindow();

    void initVulkan();

    void mainLoop();

    void cleanUp();

private:
    const int width = 800;
    const int height = 600;
    const std::string appName = "hello world";
    //是否开启debug模式
    const bool enableValidationLayers = true;


private:
    VulkanWindow *window;
    VulkanInstance *instance;


    void drawFrame();
};

#define theApp VulkanApplication::getInstance()