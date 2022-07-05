//
// Created by 王海明 on 2022/7/4.
//

#pragma once
#include "Headers.h"


class VulkanLayerAndExtension {
public:
    VulkanLayerAndExtension();
    ~VulkanLayerAndExtension();


    //debug utils messenger callback
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                 VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                 void *pUserData);

    void createDebugMessenger();
    void destroyDebugMessenger();

    [[nodiscard]] const std::vector<const char *> &getExtensionNames() const;
    [[nodiscard]] const std::vector<const char *> &getLayerNames() const;
    void setExtensionNames(const std::vector<const char *> &extensionNames);
    void setLayerNames(const std::vector<const char *> &layerNames);
    VkDebugUtilsMessengerCreateInfoEXT & getDebugUtilsMessengerCreateInfoExt();

private:
    std::vector<const char *> extensionNames;
    std::vector<const char *> layerNames;
    std::vector<VkLayerProperties> layerPropertyList;
    VkDebugUtilsMessengerEXT debugMessenger;

    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerExt;
    PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;

    VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoExt;


};


