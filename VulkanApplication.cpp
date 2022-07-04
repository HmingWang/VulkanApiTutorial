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
    window=new VulkanWindow(width,height,appName.data());
    instance=new VulkanInstance(validationLayers,VulkanWindow::getRequiredExtensions(),appName.data());

}

void VulkanApplication::initVulkan() {

}

void VulkanApplication::mainLoop() {

}

void VulkanApplication::cleanUp() {
    delete window; //调用析构函数
}

VulkanApplication &VulkanApplication::getInstance() {
    static std::unique_ptr<VulkanApplication> app;
    static std::once_flag onceFlag;
    std::call_once(onceFlag,[](){
        app = std::make_unique<VulkanApplication>();
    });
    return *app;
}

VkInstance VulkanApplication::getVkInstance() {
    return instance->getInstance();
}
