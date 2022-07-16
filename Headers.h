//
// Created by 王海明 on 2022/7/4.
//

#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<chrono>
#include<cassert>
#include "Define.h"
#include "fmt/format.h"
#include "fmt/printf.h"
#include "Process.h"
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Log.h"


#ifdef NDEBUG
    #define TRACE_CONSTRUCTOR
    #define TRACE_DESTRUCTOR
#else
#   define TRACE_DESTRUCTOR  LOG_TRACE(" 析构函数: {}",__func__)
#   define TRACE_CONSTRUCTOR LOG_TRACE(" 构造函数: {}",__func__)
#endif
////////////////////////


const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#if(SYSTEM_OS==OS_MACOS)
        "VK_KHR_portability_subset"
#endif
};