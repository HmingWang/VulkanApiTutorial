
#include <VkInitializers.hpp>
#include "..\include\VkInitializers.hpp"

VkApplicationInfo VkHelper::ApplicationInfo(const char * app_name, uint32_t app_ver, const char * engine_name, uint32_t engine_ver, uint32_t api_version)
{
    VkApplicationInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = app_name;                           // Application name
    info.applicationVersion = app_ver;	                        // Application version
    info.pEngineName = engine_name;                             // Engine name
    info.engineVersion = engine_ver;                            // Engine version
    info.apiVersion = api_version;                              // Required API version
    return info;
}