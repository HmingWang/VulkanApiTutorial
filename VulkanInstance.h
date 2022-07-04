//
// Created by 王海明 on 2022/7/4.
//

#pragma once
#include "Headers.h"

class VulkanInstance {
public:
    VulkanInstance(const char* appName);
    ~VulkanInstance();
private:
    VkInstance instance;
};


