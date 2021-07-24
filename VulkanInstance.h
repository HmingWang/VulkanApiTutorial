//
// Created by 王海明 on 2021/7/24.
//

#pragma once
#include "vulkan/vulkan.h"
#include "VulkanLayerAndExtension.h"
#include "vector"
class VulkanInstance {
public:
    VkInstance instance;
    VulkanLayerAndExtension layerExtension;
public:
    VkResult createInstance(std::vector<const char *>& layers,std::vector<const char *>& extensions,const char* applicationName);
    void destroyInstance();
};


