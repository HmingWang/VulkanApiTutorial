//
// Created by 王海明 on 2022/7/4.
//

#include "VulkanInstance.h"

VulkanInstance::VulkanInstance(std::vector<const char*>layers,std::vector<const char *>extensions,const char* appName) {
    TRACE_CONSTRUCTOR(VulkanInstance)

    layerAndExtension.setExtensionNames(extensions);
    layerAndExtension.setLayerNames(layers);
    if(!layerAndExtension.checkValidationLayerSupport()){
        throw std::runtime_error("failed to check validation layers support!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = nullptr;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = extensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
    instanceCreateInfo.enabledLayerCount = layers.size();
    instanceCreateInfo.ppEnabledLayerNames = layers.data();
    instanceCreateInfo.pNext = &layerAndExtension.getDebugUtilsMessengerCreateInfoExt();

     VkResult result= vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
     if(result!=VK_SUCCESS)
         throw std::runtime_error("failed to create instance!");
}

VulkanInstance::~VulkanInstance() {
    TRACE_DESTRUCTOR(VulkanInstance)
    vkDestroyInstance(instance, nullptr);

}

VkInstance& VulkanInstance::getVkInstance() {
    return instance;
}

VulkanLayerAndExtension &VulkanInstance::getLayerAndExtension() {
    return layerAndExtension;
}
