//
// Created by 王海明 on 2022/7/14.
//

#pragma once

#include "Define.h"
#include "Headers.h"
#include "VulkanLayerAndExtension.h"

class VulkanDevice {
public :
    VulkanDevice(VkInstance,const std::vector<const char *>&, const std::vector<const char *>&);
    ~VulkanDevice();




private:
    uint32 deviceCount{};
    VkPhysicalDevice physicalDevice{};
    std::vector<VkPhysicalDevice> physicalDeviceList{};
    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDevice device{}; //logical device

    VkQueue queue{};                            // Vulkan Queues object
    std::vector<VkQueueFamilyProperties> queueFamilyProps;                // Store all queue families exposed by the physical device. attributes
    uint32 graphicsQueueIndex{};                // Stores graphics queue index
    uint32 graphicsQueueWithPresentIndex{};  // Number of queue family exposed by device
    uint32 queueFamilyCount{};                // Device specificc layer and extensions

    void selectPhysicalDevice();

    void selectGraphicsQueueHandle();

    void selectDeviceQueue();

    VulkanLayerAndExtension layerExtension;

    void createDevice();
    void destroyDevice();
    void getDeviceQueue();


};


