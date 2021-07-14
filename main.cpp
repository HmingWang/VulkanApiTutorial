#include<vulkan/vulkan.h>
#include<VkCore.hpp>
#include <cassert>
#include<string>

VkInstance instance = static_cast<VkInstance>(VK_NULL_HANDLE);
VkDebugReportCallbackEXT debuger;

void Setup() {
    const uint32_t extension_count = 1;
    const char *instance_extentions[extension_count] = {"VK_EXT_debug_report"};
    const uint32_t layer_count = 1;
    const char *instance_layers[layer_count] = {"VK_LAYER_KHRONOS_validation"};

    assert(VkHelper::CheckLayersSupport(instance_layers, 1) && "Unsupported Layers Found");

    instance = VkHelper::CreateInstance(instance_extentions, extension_count, instance_layers, layer_count,
                                        "VulkanApiTutorial",
                                        VK_MAKE_VERSION(1, 0, 0), "vulkan engin", VK_MAKE_VERSION(1, 0, 0),
                                        VK_MAKE_VERSION(1, 1, 108));
    debuger = VkHelper::CreateDebugger(instance);
}

void Desdroy(){
    VkHelper::DestroyDebugger(instance,debuger);
    vkDestroyInstance(instance,NULL);
}

bool HasRequiredExtensions(const VkPhysicalDevice& device,const char** extensions, uint32_t extension_count){
    uint32_t device_extension_count=0;
    vkEnumerateDeviceExtensionProperties(device, nullptr,&device_extension_count, nullptr);
    VkExtensionProperties* extensionProperties=new VkExtensionProperties[device_extension_count];
    vkEnumerateDeviceExtensionProperties(device, nullptr,&device_extension_count, extensionProperties);

    bool extension_found=false;
    for(uint32_t i=0;i<extension_count;++i){
        extension_found=false;
        for(uint32_t j=0;j<device_extension_count;++j){
            if(strcmp(extensions[i],extensionProperties[j].extensionName)==0){
                extension_found=true;
                break;
            }
        }
        if(!extension_found)
            return false;
    }

    return true;
}
bool GetQueueFamily(const VkPhysicalDevice& device,VkQueueFlags flags,uint32_t& queue_family_index){
    uint32_t  queue_family_count=0;
    vkGetPhysicalDeviceQueueFamilyProperties(device,&queue_family_count, nullptr);
    VkQueueFamilyProperties* queueFamilyProperties=new VkQueueFamilyProperties [queue_family_count];
    vkGetPhysicalDeviceQueueFamilyProperties(device,&queue_family_count, queueFamilyProperties);
    for(uint32_t i=0;i<queue_family_count;++i){
        if(queueFamilyProperties[i].queueCount>0){
            if((queueFamilyProperties[i].queueFlags&flags)==flags){
                queue_family_index=i;
                delete[] queueFamilyProperties;
                return true;
            }
        }
    }

    delete[] queueFamilyProperties;
    return false;
}
int main() {
    Setup();
    uint32_t device_count=0;
    vkEnumeratePhysicalDevices(instance,&device_count, nullptr);
    auto *devices=new VkPhysicalDevice[device_count];
    vkEnumeratePhysicalDevices(instance,&device_count, devices);
    const uint32_t extension_count=1;
    const char* device_extensions[extension_count]={VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    VkPhysicalDevice chosen_device=VK_NULL_HANDLE;
    uint32_t chosen_queue_family_index=0;
    VkPhysicalDeviceProperties chosen_physicalDeviceProperties;
    VkPhysicalDeviceFeatures chosen_physicalDeviceFeatures;
    VkPhysicalDeviceMemoryProperties chosen_physicalDeviceMemoryProperties;
    for(uint32_t i=0;i< device_count;++i){
        if(HasRequiredExtensions(devices[i],device_extensions,extension_count)){
            uint32_t queue_family_index=0;
            if(GetQueueFamily(devices[i],VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT,queue_family_index)){
                VkPhysicalDeviceProperties physicalDeviceProperties;
                vkGetPhysicalDeviceProperties(devices[i],&physicalDeviceProperties);

                VkPhysicalDeviceFeatures physicalDeviceFeatures;
                vkGetPhysicalDeviceFeatures(devices[i],&physicalDeviceFeatures);

                VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
                vkGetPhysicalDeviceMemoryProperties(devices[i],&physicalDeviceMemoryProperties);

                if(chosen_device==VK_NULL_HANDLE){
                    chosen_device=devices[i];
                    chosen_physicalDeviceFeatures=physicalDeviceFeatures;
                    chosen_physicalDeviceProperties=physicalDeviceProperties;
                    chosen_physicalDeviceMemoryProperties=physicalDeviceMemoryProperties;
                    chosen_queue_family_index=queue_family_index;
                }

            }
        }
    }

    assert(chosen_device!=VK_NULL_HANDLE);
    Desdroy();
    return 0;
}