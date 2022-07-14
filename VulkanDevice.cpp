//
// Created by 王海明 on 2022/7/14.
//

#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VkInstance instance) {
    if(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr)!=VK_SUCCESS)
        throw std::runtime_error("failed to enumerate physical device count!");
    physicalDeviceList.resize(deviceCount);
    if(vkEnumeratePhysicalDevices(instance,&deviceCount,physicalDeviceList.data())!=VK_SUCCESS)
        throw std::runtime_error("failed to enumerate physical device!");

    physicalDevice=selectPhysicalDevice();
}

VkPhysicalDevice VulkanDevice::selectPhysicalDevice(){
    //todo rank for the gpu list
    return physicalDeviceList.front();
}

