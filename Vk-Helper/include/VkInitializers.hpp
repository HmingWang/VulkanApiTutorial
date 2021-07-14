#pragma once

#include <vulkan/vulkan.h>

namespace VkHelper
{
	VkApplicationInfo ApplicationInfo(const char* app_name, uint32_t app_ver, const char* engine_name, uint32_t engine_ver, uint32_t api_version);
}