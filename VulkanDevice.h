//
// Created by 王海明 on 2022/7/14.
//

#pragma once

#include "Define.h"
#include "Headers.h"
class VulkanDevice {
public :
    VulkanDevice(VkInstance);
    VkPhysicalDevice selectPhysicalDevice();
private:
    uint32 deviceCount{};
    VkPhysicalDevice physicalDevice{};
    std::vector<VkPhysicalDevice> physicalDeviceList{};
};


