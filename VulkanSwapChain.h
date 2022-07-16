//
// Created by 王海明 on 2022/7/15.
//

#pragma once

#include "Headers.h"
#include "VulkanWindow.h"
#include "VulkanDevice.h"

class VulkanSwapChain {
public:
    VulkanSwapChain(VulkanWindow* window,VulkanDevice* device);
    ~VulkanSwapChain();
private:
    VkSurfaceCapabilitiesKHR surfaceCapabilities{};
    std::vector<VkSurfaceFormatKHR> surfaceFormats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceFormatKHR surfaceFormat{};
    VkPresentModeKHR presentMode;
    VkExtent2D extent{};
    uint32 imageCount;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    VulkanWindow* window;
    VulkanDevice* device;
    VkSwapchainKHR swapChain{};
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> &availableFormats);

    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    void createSwapChain();
};
