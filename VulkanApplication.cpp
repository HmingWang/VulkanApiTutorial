//
// Created by 王海明 on 2021/7/24.
//

#include "VulkanApplication.h"
#include "VulkanHeader.h"

VulkanApplication::VulkanApplication() {
    instanceObj.layerExtension.getInstanceLayerProperties();
}

VulkanApplication::~VulkanApplication() = default;

VkResult
VulkanApplication::createVulkanInstance(std::vector<const char *> &layers, std::vector<const char *> &extensions,
                                        const char *applicationName) {
    instanceObj.createInstance(layers, extensions, applicationName);
    return VK_SUCCESS;
}

void VulkanApplication::initialize(std::vector<const char *> &layers, std::vector<const char *> &extensions,
                                   std::vector<const char *> deviceExtensions, char *appName) {
    createVulkanInstance(layers, extensions, appName);
    std::vector<VkPhysicalDevice> gpuList = {};
    enumeratePhysicalDevices(gpuList);
    if (gpuList.empty())
        throw std::runtime_error("find physical device error!");
    if (!gpuList.empty()) {
        handShakeWithDevice(&gpuList[0], layers, deviceExtensions);
    }
}

VulkanApplication *VulkanApplication::appInstance = nullptr;

VulkanApplication *VulkanApplication::GetAppInstance() {
    if (appInstance == nullptr) {
        appInstance = new VulkanApplication();
    }
    return appInstance;
}

VkResult VulkanApplication::enumeratePhysicalDevices(std::vector<VkPhysicalDevice> &physicalDevices) const {
    uint32_t deviceCount;
    VkResult result = vkEnumeratePhysicalDevices(instanceObj.instance, &deviceCount, nullptr);
    assert(result == VK_SUCCESS);
    physicalDevices.resize(deviceCount);
    result = vkEnumeratePhysicalDevices(instanceObj.instance, &deviceCount, physicalDevices.data());
    assert(result == VK_SUCCESS);
    return result;
}

VkResult VulkanApplication::handShakeWithDevice(VkPhysicalDevice *gpu, std::vector<const char *> &layer,
                                                std::vector<const char *> &extensions) {
    //vulkan设备对象
    deviceObj = new VulkanDevice(gpu);
    if (!deviceObj)
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    //设备可用层和扩展信息
    deviceObj->layerExtension.getDeviceExtensionProperties(gpu);
    //deviceObj->layerExtension.print();
    //获取设备属性
    vkGetPhysicalDeviceProperties(*gpu, &deviceObj->deviceProperties);
    //获取设备内存属性
    vkGetPhysicalDeviceMemoryProperties(*gpu, &deviceObj->deviceMemoryProperties);
    //获取设备可用队列和属性
    deviceObj->getPhysicalDeviceQueuesAndProperties();
    //获取图形流水线队列
    deviceObj->getGraphicsQueueHandle();
    //创建逻辑设备
    deviceObj->createDevice(layer, extensions);

    return VK_SUCCESS;
}


