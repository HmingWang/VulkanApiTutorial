//
// Created by 王海明 on 2022/7/4.
//

#include "VulkanApplication.h"

#include <memory>

void VulkanApplication::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanUp();

}

void VulkanApplication::initWindow() {
    window = new VulkanWindow(width, height, appName.data());

}

void VulkanApplication::initVulkan() {
    instance = new VulkanInstance(validationLayers, VulkanWindow::getRequiredExtensions(), appName.data());
    if(enableValidationLayers)
        instance->getLayerAndExtension().createDebugMessenger();



}

void VulkanApplication::mainLoop() {
    while (!window->shouldClose()) {
        drawFrame();
        window->pollEvents();
    }
    std::cout<<std::endl;
}

void VulkanApplication::cleanUp() {
    if(enableValidationLayers)
        instance->getLayerAndExtension().destroyDebugMessenger();
    delete instance;
    delete window; //调用析构函数

}

VulkanApplication &VulkanApplication::getInstance() {
    static std::unique_ptr<VulkanApplication> app;
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        app = std::make_unique<VulkanApplication>();

    });
    return *app;
}

VkInstance& VulkanApplication::getVkInstance() {
    return instance->getVkInstance();
}

void VulkanApplication::drawFrame() {
    LOG_TRACE(".");
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool VulkanApplication::isEnableValidationLayers() {
    return enableValidationLayers;
}
