//
// Created by 王海明 on 2021/7/24.
//

#include "VulkanDevice.h"


void VulkanDevice::createDevice(std::vector<const char *> &layers, std::vector<const char *> &extensions) {
    VkResult result;
    float queuePriorities[1]={0.0f};
    VkDeviceQueueCreateInfo deviceQueueCreateInfo={};
    deviceQueueCreateInfo.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.pNext= nullptr;
    deviceQueueCreateInfo.queueFamilyIndex=graphicsQueueFamilyIndex;
    deviceQueueCreateInfo.queueCount=1;
    deviceQueueCreateInfo.pQueuePriorities=queuePriorities;

    VkDeviceCreateInfo deviceCreateInfo={};
    deviceCreateInfo.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext= nullptr;
    deviceCreateInfo.queueCreateInfoCount=1;
    deviceCreateInfo.pQueueCreateInfos=&deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount=0;
    deviceCreateInfo.ppEnabledLayerNames= nullptr;
    deviceCreateInfo.enabledExtensionCount=extensions.size();
    deviceCreateInfo.ppEnabledExtensionNames=extensions.data();
    deviceCreateInfo.pEnabledFeatures= nullptr;

    result= vkCreateDevice(*pPhysicalDevice,&deviceCreateInfo, nullptr,&device);
    assert(result==VK_SUCCESS);
}

void VulkanDevice::getPhysicalDeviceQueuesAndProperties() {
    VkResult result;
    vkGetPhysicalDeviceQueueFamilyProperties(*pPhysicalDevice,&queueFamilyCount, nullptr);
    queueFamilyProperties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(*pPhysicalDevice,&queueFamilyCount,queueFamilyProperties.data());

}

void VulkanDevice::getGraphicsQueueHandle() {
    for(uint32_t i=0;i<queueFamilyCount;++i){
        if(queueFamilyProperties[i].queueFlags&VK_QUEUE_GRAPHICS_BIT){
            graphicsQueueFamilyIndex=i;
            break;
        }
    }

}

void VulkanDevice::getDeviceQueue() {
    vkGetDeviceQueue(device,graphicsQueueFamilyIndex,0,&queue);

}

VulkanDevice::VulkanDevice(VkPhysicalDevice *p):pPhysicalDevice(p)  {

}

