//
// Created by 王海明 on 2021/7/23.
//

#pragma once

#include<vulkan/vulkan.h>
#include<vector>
struct LayerProperties{
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension {

private:
    std::vector<LayerProperties> layerPropertiesList;
    std::vector<const char*> appRequestedLayerName;
    std::vector<const char*> appRequestedExtensionName;
public:
    //层和对应扩展列表
    VkResult getInstanceLayerProperties();

    void print();

private:
    //全局扩展
    VkResult getExtensionProperties(LayerProperties &layerProperties,VkPhysicalDevice *physicalDevice=NULL);
    //基于设备的扩展
    VkResult getDeviceExtensionProperties(VkPhysicalDevice *physicalDevice);
};
