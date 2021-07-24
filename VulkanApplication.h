//
// Created by 王海明 on 2021/7/24.
//

#pragma once
#include "vulkan/vulkan.h"
#include "vector"
#include "string"
#include "VulkanInstance.h"

class VulkanApplication {
private:
    VulkanApplication();
    static VulkanApplication *appInstance;
public:
    VulkanInstance instanceObj;

    static VulkanApplication* GetAppInstance();
    ~VulkanApplication();
    VkResult createVulkanInstance(std::vector<const char *>& layers,std::vector<const char *>& extensions,const char* applicationName);
    void initialize(std::vector<const char *> &layers, std::vector<const char *> &extensions,const char * appName);
    VkResult enumeratePhysicalDevices(std::vector<VkPhysicalDevice>& physicalDevices);
};


