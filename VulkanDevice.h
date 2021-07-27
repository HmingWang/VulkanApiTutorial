//
// Created by 王海明 on 2021/7/24.
//

#pragma once
#include "vulkan/vulkan.h"
#include "vector"
#include "VulkanLayerAndExtension.h"

class VulkanDevice {
    VkPhysicalDevice* pPhysicalDevice;
    std::vector<VkPhysicalDevice> physicalDeviceList;
    VkQueue queue;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    uint32_t graphicsQueueFamilyIndex;
    uint32_t queueFamilyCount;
public:
    VkDevice device;

    VulkanLayerAndExtension layerExtension;
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
    uint32_t graphicsQueueWithPresentIndex;

    explicit VulkanDevice(VkPhysicalDevice * physicalDevice);
    void createDevice(std::vector<const char*>& layers,std::vector<const char*>& extensions);
    void destroyDevice();
    void initializeDeviceQueue();
    void memoryTypeFromProperties();
    void getGraphicsQueueHandle();
    void getPhysicalDeviceQueuesAndProperties();
    void getDeviceQueue();
};


