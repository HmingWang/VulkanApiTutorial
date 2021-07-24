//
// Created by 王海明 on 2021/7/24.
//

#pragma once
#include "vulkan/vulkan.h"
#include "vector"
#include "VulkanLayerAndExtension.h"

class VulkanDevice {
    VkDevice device;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
    VkQueue queue;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    uint32_t graphicsQueueFamilyIndex;
    uint32_t queueFamilyCount;
    VulkanLayerAndExtension layerAndExtension;
public:
    void createDevice();
    void destroyDevice();
    void initializeDeviceQueue();
    void memoryTypeFromProperties();
    void getGraphicsQueueHandle();
    void getPhysicalDeviceQueuesAndProperties();
};


