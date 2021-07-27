//
// Created by 王海明 on 2021/7/27.
//

#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer(VulkanApplication* app,VulkanDevice* device) {
    application=app;
    deviceObj=device;
    swapChainObj=new VulkanSwapChain(this);
}

void VulkanRenderer::createPresentationWindow(int &w, int &h) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    hWindow=glfwCreateWindow(w,h,windowName.c_str(), nullptr, nullptr);
}

VulkanRenderer::~VulkanRenderer() {
    glfwDestroyWindow(hWindow);
    glfwTerminate();

}

void VulkanRenderer::initialize() {
    createPresentationWindow(windowWidth,windowHeight);
    swapChainObj->initializeSwapChain();
    createCommandPool();
    builSwapChainAndDepthImage();

}
void VulkanRenderer::render(){
    while(!glfwWindowShouldClose(hWindow)){
        glfwPollEvents();
    }
}

void VulkanRenderer::builSwapChainAndDepthImage() {
    deviceObj->getDeviceQueue();
    swapChainObj->createSwapChain(cmdDepthImage);
    createDepthImage();
}

void VulkanRenderer::createCommandPool() {
    VulkanDevice* deviceObj=application->deviceObj;
    VkCommandPoolCreateInfo cmdPoolInfo ={};
    cmdPoolInfo.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmdPoolInfo.queueFamilyIndex=deviceObj->graphicsQueueWithPresentIndex;//?
    vkCreateCommandPool(deviceObj->device,&cmdPoolInfo, nullptr,&cmdPool);

}
