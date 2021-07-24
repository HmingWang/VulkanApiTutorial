//
// Created by 王海明 on 2021/7/24.
//

#include "VulkanApplication.h"

VulkanApplication::VulkanApplication() {

}

VulkanApplication::~VulkanApplication() {
}

VkResult
VulkanApplication::createVulkanInstance(std::vector<const char *> &layers, std::vector<const char *> &extensions,
                                        const char *applicationName) {
    instanceObj.createInstance(layers,extensions,applicationName);
    return VK_SUCCESS;
}

void VulkanApplication::initialize(std::vector<const char *>& layers,std::vector<const char *>& extensions,const char * appName) {
    createVulkanInstance(layers,extensions,appName);
}
VulkanApplication* VulkanApplication::appInstance = nullptr;

VulkanApplication *VulkanApplication::GetAppInstance() {
    if(appInstance== nullptr){
        appInstance= new VulkanApplication();
    }
    return appInstance;
}

VkResult VulkanApplication::enumeratePhysicalDevices(std::vector<VkPhysicalDevice> &physicalDevices) {
    uint32_t deviceCount;
    VkResult result= vkEnumeratePhysicalDevices(instanceObj.instance,&deviceCount, nullptr);
    assert(result==VK_SUCCESS);
    physicalDevices.resize(deviceCount);
    result= vkEnumeratePhysicalDevices(instanceObj.instance,&deviceCount,physicalDevices.data());
    assert(result==VK_SUCCESS);
    return result;
}


