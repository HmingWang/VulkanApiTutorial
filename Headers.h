//
// Created by 王海明 on 2022/7/4.
//

#pragma once

#include<iostream>
#include<string>
#include<vector>

#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw3.h"


const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};