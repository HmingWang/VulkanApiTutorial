//
// Created by 王海明 on 2022/7/4.
//

#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<chrono>

#define GLFW_INCLUDE_VULKAN

#include "glfw/glfw3.h"

////////////////////////
#include "Log.h"

#define TRACE_CONSTRUCTOR LOG_TRACE(" 构造函数: {}",__func__);
#define TRACE_DESTRUCTOR  LOG_TRACE(" 析构函数: {}",__func__);

const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};