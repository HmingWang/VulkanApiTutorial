//
// Created by 王海明 on 2021/7/24.
//

#include "VulkanInstance.h"

VkResult VulkanInstance::createInstance(std::vector<const char *> &layers, std::vector<const char *> &extensions,
                                        const char *applicationName) {

    VkApplicationInfo applicationInfo={};
    applicationInfo.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext= nullptr;
    applicationInfo.pApplicationName=applicationName;
    applicationInfo.applicationVersion= VK_MAKE_VERSION(1,0,0);
    applicationInfo.pEngineName=applicationName;
    applicationInfo.engineVersion= VK_MAKE_VERSION(1,0,0);
    applicationInfo.apiVersion=VK_API_VERSION_1_2;

    VkInstanceCreateInfo instanceCreateInfo={};
    instanceCreateInfo.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext= nullptr;
    instanceCreateInfo.flags=0;
    instanceCreateInfo.enabledLayerCount=layers.size();
    instanceCreateInfo.ppEnabledLayerNames=layers.data();
    instanceCreateInfo.enabledExtensionCount=extensions.size();
    instanceCreateInfo.ppEnabledExtensionNames=extensions.data();
    instanceCreateInfo.pApplicationInfo=&applicationInfo;

    VkResult result= vkCreateInstance(&instanceCreateInfo, nullptr,&instance);
    assert(result==VK_SUCCESS);

    return result;
}

void VulkanInstance::destroyInstance() {
    vkDestroyInstance(instance, nullptr);
}
