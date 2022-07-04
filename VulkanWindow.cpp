//
// Created by 王海明 on 2022/7/4.
//

#include "VulkanWindow.h"

bool VulkanWindow::isInitialized{false};

VulkanWindow::VulkanWindow(int width, int height,const char* windowName) {
    if(!isInitialized){
        int res=glfwInit();
        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
        if(res==GLFW_FALSE)
            throw std::runtime_error("failed to init glfw!");
        isInitialized=true;
    }
    window=glfwCreateWindow(width,height,windowName, nullptr, nullptr);
    if(window == nullptr)
        throw std::runtime_error("failed to create glfw window!");
}

VulkanWindow::~VulkanWindow() {
    glfwDestroyWindow(window);
}
