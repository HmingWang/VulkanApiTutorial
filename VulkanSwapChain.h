//
// Created by 王海明 on 2022/7/15.
//

#pragma once

#include "Headers.h"

class VulkanSwapChain {
public:
    VulkanSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

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

    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> &availableFormats);

    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    void createSwapChain();
};
