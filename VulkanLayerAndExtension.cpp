//
// Created by 王海明 on 2021/7/23.
//

#include <iostream>
#include "VulkanLayerAndExtension.h"
#include "VulkanApplication.h"
#include "VulkanHeader.h"

VkResult VulkanLayerAndExtension::getInstanceLayerProperties() {
    uint32_t instanceLayerCount;
    VkResult result;
    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
    assert(result == VK_SUCCESS);
    std::vector<VkLayerProperties> layerProperties(instanceLayerCount);
    vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.data());

    std::cout << "\nInstance Layers" << std::endl;
    std::cout << "================" << std::endl;
    for (auto globalLayerProp:layerProperties) {
        std::cout << "\n" << globalLayerProp.description << "\n\t|\n\t|---[Layer Name]-->" << globalLayerProp.layerName
                  << '\n';
        LayerProperties layerProps;
        layerProps.properties = globalLayerProp;

        result = getExtensionProperties(layerProps);
        assert(result == VK_SUCCESS);

        this->layerPropertiesList.push_back(layerProps);
        for (auto j:layerProps.extensions) {
            std::cout << "\t\t|\n\t\t|---[Layer Extension]-->" << j.extensionName << '\n';
        }
    }
    return VK_SUCCESS;
}

VkResult
VulkanLayerAndExtension::getExtensionProperties(LayerProperties &layerProperties, VkPhysicalDevice *physicalDevice) {
    VkResult result;
    uint32_t extensionCount;
    //获取设备相关扩展
    if (physicalDevice) {
        result = vkEnumerateDeviceExtensionProperties(*physicalDevice,
                                                      layerProperties.properties.layerName,
                                                      &extensionCount,
                                                      nullptr);
        assert(result == VK_SUCCESS);
        layerProperties.extensions.resize(extensionCount);
        result = vkEnumerateDeviceExtensionProperties(*physicalDevice,
                                                      layerProperties.properties.layerName,
                                                      &extensionCount,
                                                      layerProperties.extensions.data());
        assert(result == VK_SUCCESS);
    }
        //获取实例相关扩展
    else {
        result = vkEnumerateInstanceExtensionProperties(layerProperties.properties.layerName, &extensionCount, nullptr);
        assert(result == VK_SUCCESS);
        layerProperties.extensions.resize(extensionCount);
        result = vkEnumerateInstanceExtensionProperties(layerProperties.properties.layerName, &extensionCount,
                                                        layerProperties.extensions.data());
        assert(result == VK_SUCCESS);
    }

    return VK_SUCCESS;
}

VkResult VulkanLayerAndExtension::getDeviceExtensionProperties(VkPhysicalDevice *physicalDevice) {
    VkResult result;
    std::vector<LayerProperties> *instanceLayerProp = &theApp->instanceObj.layerExtension.layerPropertiesList;
    std::cout << "\nDevice extensions" << std::endl;
    std::cout << "==================" << std::endl;
    for (const auto &globalLayerProp:*instanceLayerProp) {
        LayerProperties layerProperties;
        layerProperties.properties = globalLayerProp.properties;
        result = getExtensionProperties(layerProperties, physicalDevice);
        assert(result == VK_SUCCESS);
        layerPropertiesList.push_back(layerProperties);
        for (auto j:layerProperties.extensions) {
            std::cout << "\t\t|\n\t\t|---[Layer Extension]-->" << j.extensionName << '\n';
        }
    }

    return VK_SUCCESS;
}

void VulkanLayerAndExtension::printLayerAndExtensionInfo() {
    std::cout << "\nInstance Layers" << std::endl;
    std::cout << "================" << std::endl;
    for (auto i:layerPropertiesList) {
        std::cout << "\n" << i.properties.description << "\n\t|\n\t|---[Layer Name]-->" << i.properties.layerName
                  << '\n';
        for (auto j:i.extensions) {
            std::cout << "\t\t|\n\t\t|---[Layer Extension]-->" << j.extensionName << '\n';
        }
    }

}

VkBool32 VulkanLayerAndExtension::areLayersSupported(std::vector<const char *> &layerNames) {
    uint32_t checkCount = layerNames.size();
    uint32_t layerCount = layerPropertiesList.size();
    std::vector<const char *> unsupportLayerNames;
    for (uint32_t i = 0; i < checkCount; ++i) {
        VkBool32 isSupported = 0;
        for (uint32_t j = 0; j < layerCount; ++j) {
            if (!strcmp(layerNames[i], layerPropertiesList[j].properties.layerName)) {
                isSupported = 1;
            }
        }
        if (!isSupported) {
            std::cout << "No Layer support found, removed from layer :" << layerNames[i] << std::endl;
            unsupportLayerNames.push_back(layerNames[i]);
        } else {
            std::cout << "Layer supported: " << layerNames[i] << std::endl;
        }
    }
    for (auto i:unsupportLayerNames) {
        auto it = std::find(layerNames.begin(), layerNames.end(), i);
        if (it != layerNames.end())
            layerNames.erase(it);
    }
    return true;
}

VkResult VulkanLayerAndExtension::createDebugReportCallback() {
    dbgCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)
            vkGetInstanceProcAddr(theApp->instanceObj.instance, "vkCreateDebugReportCallbackEXT");
    if (!dbgCreateDebugReportCallback) {
        std::cout << "Error: GetInstanceProcAddr unable to locate vkCreateDebugReportCallbackExt function.\n"
                  << std::endl;
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    dbgDestoryDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)
            vkGetInstanceProcAddr(theApp->instanceObj.instance, "vkDestoryDebugReportCallbackEXT");
    if (!dbgDestoryDebugReportCallback) {
        std::cout << "Error: GetInstanceProcAddr unable to locate vkDestroyDebugReportCallbackEXT function.\n"
                  << std::endl;
        return VK_ERROR_INITIALIZATION_FAILED;
    }


    VkResult result = dbgCreateDebugReportCallback(theApp->instanceObj.instance, &debugReportCallbackCreateInfoExt,
                                                   nullptr, &debugReportCallbackExt);
    if (result == VK_SUCCESS) {
        std::cout << "Debug report callback object created successfully\n" << std::endl;
    }
    return result;
}

VkBool32
VulkanLayerAndExtension::debugFunction(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
                                       size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
                                       void *pUserData) {
    if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
        std::cout << "[VK_DEBUG_REPORT] ERROR: [" << pLayerPrefix << "] Code " << msgCode << ": " << pMsg << std::endl;
    } else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
        std::cout << "[VK_DEBUG_REPORT] WARNING: [" << pLayerPrefix << "] Code " << msgCode << ": " << pMsg
                  << std::endl;
    } else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
        std::cout << "[VK_DEBUG_REPORT] INFORMATION: [" << pLayerPrefix << "] Code " << msgCode << ": " << pMsg
                  << std::endl;
    } else if (msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
        std::cout << "[VK_DEBUG_REPORT] PERFORMANCE: [" << pLayerPrefix << "] Code " << msgCode << ": " << pMsg
                  << std::endl;
    } else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
        std::cout << "[VK_DEBUG_REPORT] DEBUG: [" << pLayerPrefix << "] Code " << msgCode << ": " << pMsg << std::endl;
    } //else return VK_FALSE;

    return VK_SUCCESS;
}

void VulkanLayerAndExtension::destoryDebugReportCallback() {
    dbgDestoryDebugReportCallback(theApp->instanceObj.instance,debugReportCallbackExt, nullptr);
}

void VulkanLayerAndExtension::initDebugReportCallbackCreateInfo() {

    debugReportCallbackCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    debugReportCallbackCreateInfoExt.pfnCallback = debugFunction;
    debugReportCallbackCreateInfoExt.pNext = nullptr;
    debugReportCallbackCreateInfoExt.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT
                                             | VK_DEBUG_REPORT_INFORMATION_BIT_EXT
                                             | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT
                                             | VK_DEBUG_REPORT_ERROR_BIT_EXT
                                             | VK_DEBUG_REPORT_DEBUG_BIT_EXT;
}
