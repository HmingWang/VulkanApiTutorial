#include<vulkan/vulkan.h>
#include <cassert>
VkInstance instance = VK_NULL_HANDLE;

void setup() 
{
    const uint32_t extension_count = 1;
    const char* instance_extentions[extension_count] = { "VK_EXT_debug_report" };
    const uint32_t layer_count = 1;
    const char* instance_layers[layer_count] = { "VK_LAYER_KHRONOS_validation" };

    assert(VkHelper::CheckLayerSupport(instance_layers, 1) && "Unsupported Layers Found");
}
int main()
{
    setup();
    const char *instance_layers[]={"VK_LAYER_KHRONOS_validation"};
    const char* instance_extentions[] = { "VK_EXT_debug_report" };

    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Instance";
    app_info.pEngineName = "my engin";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_MAKE_VERSION(1, 1, 108);

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = 1;
    create_info.ppEnabledExtensionNames = instance_extentions;
    create_info.enabledLayerCount = 1;
    create_info.ppEnabledLayerNames = instance_layers;

    VkResult result = vkCreateInstance(&create_info, NULL, &instance);
    assert(result == VK_SUCCESS);

    vkDestroyInstance(instance, NULL);
    return 0;
}