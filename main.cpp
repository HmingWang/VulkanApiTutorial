#include <iostream>
#include "VulkanLayerAndExtension.h"
#include "VulkanApplication.h"
#include "vector"

using namespace std;

std::vector<const char *> layers={
        "VK_LAYER_LUNARG_api_dump",
        "VK_LAYER_KHRONOS_validation"
};
std::vector<const char *> extensions={
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME
};

int main(){
//    VulkanLayerAndExtension layerAndExtension={};
//    layerAndExtension.getInstanceLayerProperties();
//    layerAndExtension.print();
    VulkanApplication *app=VulkanApplication::GetAppInstance();
    app->initialize(layers, extensions,"app");
}