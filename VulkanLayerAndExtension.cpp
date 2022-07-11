//
// Created by 王海明 on 2022/7/4.
//

#include "VulkanLayerAndExtension.h"
#include "VulkanWindow.h"
#include "VulkanApplication.h"

VulkanLayerAndExtension::VulkanLayerAndExtension() {
    TRACE_CONSTRUCTOR;

    extensionNames = {};
    layerNames = {};
    layerPropertyList = {};
    debugMessenger = {};

    vkCreateDebugUtilsMessengerExt = {};
    vkDestroyDebugUtilsMessengerEXT = {};

    //debug create info
    debugUtilsMessengerCreateInfoExt = {};

    debugUtilsMessengerCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugUtilsMessengerCreateInfoExt.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugUtilsMessengerCreateInfoExt.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    debugUtilsMessengerCreateInfoExt.pfnUserCallback = debugCallback;
}

VKAPI_ATTR VkBool32 VKAPI_CALL
VulkanLayerAndExtension::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                       VkDebugUtilsMessageTypeFlagsEXT messageType,
                                       const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData) {
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        std::cerr << "[VK_DEBUG_UTILS] Error : " << pCallbackData->pMessage << std::endl;
    }
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        std::cout << "[VK_DEBUG_UTILS] Warning : " << pCallbackData->pMessage << std::endl;
    }
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        //std::cout << "[VK_DEBUG_UTILS] Verbose : " << pCallbackData->pMessage << std::endl;
    }
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        std::cout << "[VK_DEBUG_UTILS] Info : " << pCallbackData->pMessage << std::endl;
    }

    return VK_FALSE;
}

void VulkanLayerAndExtension::createDebugMessenger() {
    if (vkCreateDebugUtilsMessengerExt == nullptr) {

        vkCreateDebugUtilsMessengerExt = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                theApp.getVkInstance(),
                "vkCreateDebugUtilsMessengerEXT");

        if (vkCreateDebugUtilsMessengerExt == nullptr)
            throw std::runtime_error("failed to get proc address : vkCreateDebugUtilsMessengerExt !");

    }
    //create debug messenger
    VkResult result = vkCreateDebugUtilsMessengerExt(theApp.getVkInstance(), &debugUtilsMessengerCreateInfoExt, nullptr,
                                                     &debugMessenger);
    if (result != VK_SUCCESS)
        throw std::runtime_error("failed to create debug messenger!");

}

void VulkanLayerAndExtension::destroyDebugMessenger() {
    if (vkDestroyDebugUtilsMessengerEXT == nullptr) {
        vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                theApp.getVkInstance(),
                "vkDestroyDebugUtilsMessengerEXT");
        if (vkDestroyDebugUtilsMessengerEXT == nullptr)
            throw std::runtime_error("failed to get proc address : vkDestroyDebugUtilsMessengerEXT !");
    }
    vkDestroyDebugUtilsMessengerEXT(theApp.getVkInstance(), debugMessenger, nullptr);
}

VulkanLayerAndExtension::~VulkanLayerAndExtension() {
    TRACE_DESTRUCTOR;
}

void VulkanLayerAndExtension::setExtensionNames(const std::vector<const char *> &extensionNames) {
    VulkanLayerAndExtension::extensionNames = extensionNames;
}

void VulkanLayerAndExtension::setLayerNames(const std::vector<const char *> &layerNames) {
    VulkanLayerAndExtension::layerNames = layerNames;
}

const std::vector<const char *> &VulkanLayerAndExtension::getExtensionNames() const {
    return extensionNames;
}

const std::vector<const char *> &VulkanLayerAndExtension::getLayerNames() const {
    return layerNames;
}

VkDebugUtilsMessengerCreateInfoEXT &VulkanLayerAndExtension::getDebugUtilsMessengerCreateInfoExt() {
    return debugUtilsMessengerCreateInfoExt;
}

bool VulkanLayerAndExtension::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    layerPropertyList.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layerPropertyList.data());

    for (const char* layerName : layerNames) {
        bool layerFound = false;

        for (const auto& layerProperties : layerPropertyList) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}
