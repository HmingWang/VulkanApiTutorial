//
// Created by 王海明 on 2021/7/23.
//

#pragma once

#include<vulkan/vulkan.h>
#include<vector>

struct LayerProperties {
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension {

private:
    std::vector<LayerProperties> layerPropertiesList;
    std::vector<const char *> appRequestedLayerName;
    std::vector<const char *> appRequestedExtensionName;
    PFN_vkCreateDebugReportCallbackEXT dbgCreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT dbgDestoryDebugReportCallback;

public:
    std::vector<const char *> instanceExtensionNames;
    std::vector<const char *> instanceLayerNames;
    VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfoExt = {};
    VkDebugReportCallbackEXT debugReportCallbackExt;
    //层和对应扩展列表
    VkResult getInstanceLayerProperties();

    //基于设备的扩展
    VkResult getDeviceExtensionProperties(VkPhysicalDevice *physicalDevice);

    void printLayerAndExtensionInfo();

    VkBool32 areLayersSupported(std::vector<const char *> &layerNames);

    VkResult createDebugReportCallback();
    void initDebugReportCallbackCreateInfo();

    VKAPI_ATTR static VkBool32 VKAPI_CALL
    debugFunction(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location,
                  int32_t msgCode, const char *pLayerPrefix, const char *pMsg, void *pUserData);
    void destoryDebugReportCallback();

private:
    //全局扩展
    VkResult getExtensionProperties(LayerProperties &layerProperties, VkPhysicalDevice *physicalDevice = nullptr);

};
