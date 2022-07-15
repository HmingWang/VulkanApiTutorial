//
// Created by 王海明 on 2022/7/14.
//

#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VkInstance instance,const std::vector<const char *>& layers, const std::vector<const char *>& extensions) {
    TRACE_CONSTRUCTOR;
    layerExtension.setLayerNames(layers);
    layerExtension.setExtensionNames(extensions);
    if (vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr) != VK_SUCCESS)
        throw std::runtime_error("failed to enumerate physical device count!");
    physicalDeviceList.resize(deviceCount);
    if (vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDeviceList.data()) != VK_SUCCESS)
        throw std::runtime_error("failed to enumerate physical device!");

    selectPhysicalDevice();
    selectGraphicsQueueHandle();
    createDevice();
    getDeviceQueue();
}

void  VulkanDevice::selectPhysicalDevice() {
    //todo rank for the gpu list
    physicalDevice= physicalDeviceList.at(0);// 用第一个gpu

    //get physical device queue family count & props.
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    queueFamilyProps.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProps.data());
}

void VulkanDevice::selectGraphicsQueueHandle() {
    //	1. Get the number of Queues supported by the Physical device
    //	2. Get the properties each Queue type or Queue Family
    //			There could be 4 Queue type or Queue families supported by physical device -
    //			Graphics Queue	- VK_QUEUE_GRAPHICS_BIT
    //			Compute Queue	- VK_QUEUE_COMPUTE_BIT
    //			DMA				- VK_QUEUE_TRANSFER_BIT
    //			Spare memory	- VK_QUEUE_SPARSE_BINDING_BIT
    //	3. Get the index ID for the required Queue family, this ID will act like a handle index to queue.

    bool found = false;
    // 1. Iterate number of Queues supported by the Physical device
    for (unsigned int i = 0; i < queueFamilyCount; i++){
        // 2. Get the Graphics Queue type
        //		There could be 4 Queue type or Queue families supported by physical device -
        //		Graphics Queue		- VK_QUEUE_GRAPHICS_BIT
        //		Compute Queue		- VK_QUEUE_COMPUTE_BIT
        //		DMA/Transfer Queue	- VK_QUEUE_TRANSFER_BIT
        //		Spare memory		- VK_QUEUE_SPARSE_BINDING_BIT

        if (queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
            // 3. Get the handle/index ID of graphics queue family.
            found				= true;
            graphicsQueueIndex	= i;
            break;
        }
    }
    // Assert if there is no queue found.
    assert(found);
}

void VulkanDevice::selectDeviceQueue() {

}

void VulkanDevice::createDevice() {


    // Create Device with available queue information.
    float queuePriorities[1]			= { 0.0 };
    VkDeviceQueueCreateInfo queueInfo	= {};
    queueInfo.queueFamilyIndex			= graphicsQueueIndex;
    queueInfo.sType						= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.pNext						= nullptr;
    queueInfo.queueCount				= 1;
    queueInfo.pQueuePriorities			= queuePriorities;


    vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

    VkPhysicalDeviceFeatures setEnabledFeatures = {VK_FALSE};
    setEnabledFeatures.samplerAnisotropy = deviceFeatures.samplerAnisotropy;

    VkDeviceCreateInfo deviceInfo		= {};
    deviceInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pNext					= nullptr;
    deviceInfo.queueCreateInfoCount		= 1;
    deviceInfo.pQueueCreateInfos		= &queueInfo;
    deviceInfo.enabledLayerCount		= layerExtension.getLayerNames().size();
    deviceInfo.ppEnabledLayerNames		= !layerExtension.getLayerNames().empty()?layerExtension.getLayerNames().data(): nullptr;									// Device layers are deprecated
    deviceInfo.enabledExtensionCount	= layerExtension.getExtensionNames().size();
    deviceInfo.ppEnabledExtensionNames	= !layerExtension.getExtensionNames().empty() ? layerExtension.getExtensionNames().data() : nullptr;
    deviceInfo.pEnabledFeatures			= &setEnabledFeatures;

    if(vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device)!=VK_SUCCESS){
        throw std::runtime_error("failed to create device!");
    }
}

void VulkanDevice::destroyDevice() {
    vkDestroyDevice(device, nullptr);
}

VulkanDevice::~VulkanDevice() {
    TRACE_DESTRUCTOR;
    destroyDevice();
}

void VulkanDevice::getDeviceQueue() {
    vkGetDeviceQueue(device, graphicsQueueIndex,0,&queue);
}

