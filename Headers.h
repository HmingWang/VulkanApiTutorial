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

#define TRACE_CONSTRUCTOR std::cout<<"[constructor]："<<__func__<<std::endl
#define TRACE_DESTRUCTOR  std::cout<<"[destructor ]："<<__func__<<std::endl

const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};