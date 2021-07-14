
#include <VkCore.hpp>
#include "VkInitializers.hpp"
#include <memory>
#include <cassert>
// Compare the required layers to the available layers on the system
bool VkHelper::CheckLayersSupport(const char** layers, int count)
{
	// Find out how many layers are available on the system
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	// Using the count, tell the system how many layer definitions we want to read
	// These layer properties are the layers that are available on the system
	std::unique_ptr<VkLayerProperties[]> layerProperties(new VkLayerProperties[layerCount]());
	vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.get());

	// Loop through for each layer we want to check
	for (int i = 0; i < count; ++i)
	{
		bool layerFound = false;
		// Loop through for each available system layer and attempt to find our required layer
		for (uint32_t j = 0; j < layerCount; ++j)
		{
			// Check to see if the layer matches
			if (strcmp(layers[i], layerProperties[j].layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}
		// If we are missing the required layer, report back
		if (!layerFound)
		{
			return false;
		}
	}
	// Found all the layers
	return true;
}

VkInstance VkHelper::CreateInstance(const char** extensions, unsigned int extensions_count, const char** layers, unsigned int layerCount, const char* app_name, uint32_t app_ver,
	const char* engine_name, uint32_t engine_ver, uint32_t api_version)
{
	VkInstance instance;

	VkApplicationInfo app_info = VkHelper::ApplicationInfo(
		app_name,                                                // Application name
		app_ver,                                                 // Application version
		engine_name,                                             // Engine name
		engine_ver,                                              // Engine version
		api_version                                              // Required API version
	);

	VkInstanceCreateInfo create_info = VkHelper::InstanceCreateInfo(
		app_info,                                                // Pointer to the application information created
		extensions,                                              // The raw data of the extensions to enable
		extensions_count,                                        // The amount of extensions we wish to enable
		layers,                                                  // The raw data of the layers to enable
		layerCount                                               // The amount of layers we wish to enable
	);

	VkResult result = vkCreateInstance(
		&create_info,                                            // Information to pass to the function
		NULL,                                                    // Memory allocation callback
		&instance                                                // The Vulkan instance to be initialized
	);

	// Was the vulkan instance created successfully
	assert(result == VK_SUCCESS);

	return instance;
}
// A basic debug callback. A more advanced one could be created, but this will do for basic debugging
VKAPI_ATTR VkBool32 VKAPI_CALL MyDebugReportCallback(
        VkDebugReportFlagsEXT       flags,
        VkDebugReportObjectTypeEXT  objectType,
        uint64_t                    object,
        size_t                      location,
        int32_t                     messageCode,
        const char*                 pLayerPrefix,
        const char*                 pMessage,
        void*                       pUserData)
{
    printf("%s\n",pMessage);
    return VK_FALSE;
}
// Attach a debugger to the application to give us validation feedback.
// This is useful as it tells us about any issues without application
VkDebugReportCallbackEXT VkHelper::CreateDebugger(const VkInstance& instance)
{
    // Get the function pointer for the debug callback function within VK
    PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT =
            reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>
            (vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));


    /*PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT =
        reinterpret_cast<PFN_vkDebugReportMessageEXT>
        (vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT"));
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT =
        reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>
        (vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));*/


    // Define a CreateInfo for our new callback
    VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
    callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;            // Callback Type
    callbackCreateInfo.pNext = nullptr;
    callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |                            // What we wukk be notified about
                               VK_DEBUG_REPORT_WARNING_BIT_EXT |                                                 //...
                               VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;                                      //...
    callbackCreateInfo.pfnCallback = &MyDebugReportCallback;                              // Our function that will be called on a callback
    callbackCreateInfo.pUserData = nullptr;                                               // A custom data pointer that the user can define. Since we are calling a non member function
    // it may be usefull to pass a pointer instance of the engine or rendering libary, in this case
    // we dont need anything

    VkDebugReportCallbackEXT callback;

    // Create the new callback
    VkResult result = vkCreateDebugReportCallbackEXT(instance, &callbackCreateInfo, nullptr, &callback);

    // Was the vulkan callback created successfully
    assert(result == VK_SUCCESS);

    return callback;
}

void VkHelper::DestroyDebugger(const VkInstance & instance, const VkDebugReportCallbackEXT & debugger)
{
    auto vkDestroyDebugReportCallbackEXT =
            reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>
            (vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));

    // Destroy the debug callback
    vkDestroyDebugReportCallbackEXT(
            instance,
            debugger,
            nullptr
    );
}