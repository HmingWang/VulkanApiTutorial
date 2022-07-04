//
// Created by 王海明 on 2022/7/4.
//

#include "VulkanInstance.h"

VulkanInstance::VulkanInstance(const char* appName) {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = nullptr;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

}

VulkanInstance::~VulkanInstance() {

}