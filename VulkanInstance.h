//
// Created by 王海明 on 2022/7/4.
//

#pragma once
#include "Headers.h"
#include "VulkanLayerAndExtension.h"

class VulkanInstance {
public:
    VulkanInstance(std::vector<const char*>layers,std::vector<const char *>extensions,const char* appName);
    ~VulkanInstance();
    VkInstance & getVkInstance();
private:
    VkInstance instance{};
    VulkanLayerAndExtension layerAndExtension;
public:
    VulkanLayerAndExtension &getLayerAndExtension();
};


