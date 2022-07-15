//
// Created by 王海明 on 2022/7/4.
//

#pragma once

#include "Headers.h"
#include "VulkanWindow.h"
#include "VulkanInstance.h"
#include "VulkanDevice.h"

class VulkanApplication {
public:
    void run();

    static VulkanApplication &getInstance();

    VkInstance& getVkInstance();

    bool isEnableValidationLayers();

private:
    VulkanApplication() {TRACE_CONSTRUCTOR;};
    ~VulkanApplication(){TRACE_DESTRUCTOR;};
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
    VulkanWindow *window{};
    VulkanInstance *instance{};
    VulkanDevice *device{};


    void drawFrame();
};

#define theApp VulkanApplication::getInstance()