//
// Created by 王海明 on 2021/7/27.
//
#pragma once

#include "VulkanHeader.h"

class VulkanRenderer {

public :
    VulkanRenderer(VulkanApplication *app, VulkanDevice *device);
    ~VulkanRenderer();
    void initialize();
    void createPresentationWindow(int& w,int& h);
    void createCommandPool();
    void createSwapChain();
    void createDepthImage();


    GLFWwindow * hWindow;
    std::string windowName;
    VkCommandBuffer cmdDepthImage;
    VkCommandPool cmdPool;
    int windowWidth;
    int windowHeight;

    struct {VkFormat format;
        VkImage image;
        VkDeviceMemory mem;
        VkImageView view;
    } Depth;

private:
    VulkanSwapChain* swapChainObj;
    VulkanApplication* application;
    VulkanDevice* deviceObj;

    void builSwapChainAndDepthImage();

    void render();
};


