//
// Created by 王海明 on 2021/7/23.
//

#include <iostream>
#include "VulkanLayerAndExtension.h"
#include "VulkanApplication.h"

VkResult VulkanLayerAndExtension::getInstanceLayerProperties() {
    uint32_t instanceLayerCount;
    VkResult result;
    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount,nullptr);
    assert(result==VK_SUCCESS);
    std::vector<VkLayerProperties> layerProperties(instanceLayerCount);
    vkEnumerateInstanceLayerProperties(&instanceLayerCount,layerProperties.data());

    for(auto globalLayerProp:layerProperties){

        LayerProperties layerProps;
        layerProps.properties=globalLayerProp;

        result= getExtensionProperties(layerProps);
        assert(result==VK_SUCCESS);

        this->layerPropertiesList.push_back(layerProps);
    }
    return VK_SUCCESS;
}

VkResult
VulkanLayerAndExtension::getExtensionProperties(LayerProperties &layerProperties, VkPhysicalDevice *physicalDevice) {
    VkResult result;
    uint32_t extensionCount;
    //获取设备相关扩展
    if(physicalDevice){
        result= vkEnumerateDeviceExtensionProperties(*physicalDevice,
                                                     layerProperties.properties.layerName,
                                                     &extensionCount,
                                                     nullptr);
        assert(result==VK_SUCCESS);
        layerProperties.extensions.resize(extensionCount);
        result= vkEnumerateDeviceExtensionProperties(*physicalDevice,
                                                     layerProperties.properties.layerName,
                                                     &extensionCount,
                                                     layerProperties.extensions.data());
        assert(result==VK_SUCCESS);
    }
    //获取实例相关扩展
    else{
        result= vkEnumerateInstanceExtensionProperties(layerProperties.properties.layerName,&extensionCount, nullptr);
        assert(result==VK_SUCCESS);
        layerProperties.extensions.resize(extensionCount);
        result= vkEnumerateInstanceExtensionProperties(layerProperties.properties.layerName,&extensionCount,layerProperties.extensions.data());
        assert(result==VK_SUCCESS);
    }

    return VK_SUCCESS;
}

VkResult VulkanLayerAndExtension::getDeviceExtensionProperties(VkPhysicalDevice *physicalDevice) {
    VkResult result;
    std::vector<LayerProperties>* instanceLayerProp=&VulkanApplication::GetAppInstance()->instanceObj.layerExtension.layerPropertiesList;
    for(auto globalLayerProp:*instanceLayerProp){
        LayerProperties layerProperties;
        layerProperties.properties=globalLayerProp.properties;
        result= getExtensionProperties(layerProperties,physicalDevice);
        assert(result==VK_SUCCESS);
        layerPropertiesList.push_back(layerProperties);
    }

    return VK_SUCCESS;
}

void VulkanLayerAndExtension::print() {
    std::cout<<"\nInstance Layers"<<std::endl;
    std::cout<<"================"<<std::endl;
    for(auto i:layerPropertiesList){
        std::cout<<"\n"<<i.properties.description<<"\n\t|\n\t|---[Layer Name]-->"<<i.properties.layerName<<'\n';
        for(auto j:i.extensions){
            std::cout<<"\t\t|\n\t\t|---[Layer Extension]-->"<<j.extensionName<<'\n';
        }
    }

}
