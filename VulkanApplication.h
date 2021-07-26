//
// Created by 王海明 on 2021/7/24.
//

#pragma once

#include "vulkan/vulkan.h"
#include "vector"
#include "string"
#include "VulkanInstance.h"
#include "VulkanDevice.h"

class VulkanApplication {
private:
    VulkanApplication();

    static VulkanApplication *appInstance;
public:
    VulkanInstance instanceObj;
    VulkanDevice *deviceObj{};

    static VulkanApplication *GetAppInstance();

    ~VulkanApplication();

    VkResult createVulkanInstance(std::vector<const char *> &layers, std::vector<const char *> &extensions,
                                  const char *applicationName);

    VkResult enumeratePhysicalDevices(std::vector<VkPhysicalDevice> &physicalDevices) const;

    VkResult
    handShakeWithDevice(VkPhysicalDevice *gpu, std::vector<const char *> &layer, std::vector<const char *> &extensions);

    void initialize(std::vector<const char *> &layers, std::vector<const char *> &extensions,
                    std::vector<const char *> deviceExtensions, char *appName);
};

#define theApp (VulkanApplication::GetAppInstance())
