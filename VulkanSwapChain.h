//
// Created by 王海明 on 2021/7/27.
//

#pragma once

#include "VulkanHeader.h"

struct SwapChainPrivateVariables {
    VkSurfaceCapabilitiesKHR surfCapabilities;
    uint32_t presentModeCount;
    std::vector<VkPresentModeKHR> presentModes;
    VkExtent2D swapChainExtent;
    uint32_t desiredNumberOfSwapChainImages;
    VkSurfaceTransformFlagBitsKHR preTransform;
    VkPresentModeKHR swapChainPresentMode;
    std::vector<VkImage> swapChainImages;
    std::vector<VkSurfaceFormatKHR> surfFormats;
};

struct SwapChainPublicVariables{
    VkSurfaceKHR surface;
    uint32_t swapChainImageCount;
    VkSwapchainKHR swapChain;
    std::vector<SwapChainBuffer> colorBuffer;
    uint32_t currentColorBuffer;
    VkFormat format;
};

class VulkanSwapChain {
public :
    void initializeSwapChain();

    void createSwapChain(const VkCommandBuffer &cmd);

    void destorySwapChain();

    SwapChainPublicVariables scPublicVars;
private:
    SwapChainPrivateVariables scPrivateVars;
    VulkanRenderer *rendererObj;
    VulkanApplication *appObj;

    VkResult createSwapChainExtensions();

    void getSupportedFormats();

    VkResult createSurface();

    uint32_t getGraphicsQueueWithPresentaionSupport();

    void getSurfaceCapabilitiesAndPresentMode();

    void createSwapChainColorBufferImages();

    void createColorImageView(const VkCommandBuffer &cmd);

};


