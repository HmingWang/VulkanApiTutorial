//
// Created by 王海明 on 2022/7/4.
//

#include "VulkanWindow.h"
#include "VulkanApplication.h"

bool VulkanWindow::isInitialized{false};

VulkanWindow::VulkanWindow(int width, int height, const char *windowName) {
    TRACE_CONSTRUCTOR;
    if (!isInitialized) {
        int res = glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        if (res == GLFW_FALSE)
            throw std::runtime_error("failed to init glfw!");
        isInitialized = true;
    }
    window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
    if (window == nullptr)
        throw std::runtime_error("failed to create glfw window!");

    surface = {};
}

VulkanWindow::~VulkanWindow() {
    TRACE_DESTRUCTOR;
    glfwDestroyWindow(window);
    //应该等最后一个对象销毁时销毁，因为目前只有一个窗口对象所以再次销毁。
    glfwTerminate();
}

std::vector<const char *> VulkanWindow::getRequiredExtensions() {

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (theApp.isEnableValidationLayers()) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

bool VulkanWindow::shouldClose() {

    return glfwWindowShouldClose(window);
}

void VulkanWindow::pollEvents() {
    return glfwPollEvents();

}

void VulkanWindow::createSurface() {
    if (surface == nullptr) {
        VkResult result = glfwCreateWindowSurface(theApp.getVkInstance(), window, nullptr, &surface);
        if (result != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface");
    }
}

void VulkanWindow::destroySurface() {
    vkDestroySurfaceKHR(theApp.getVkInstance(), surface, nullptr);
}

VkSurfaceKHR &VulkanWindow::getSurface() {
    if (surface == nullptr) {
        createSurface();
    }
    return surface;
}
