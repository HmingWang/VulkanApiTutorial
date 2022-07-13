//
// Created by 王海明 on 2022/7/4.
//
#include "Headers.h"
#include "VulkanApplication.h"
#include "Log.h"

int main() {
    LOG_DEBUG("my vulkan application start ...");

    try {
        theApp.run();
    } catch (std::exception &e) {
        LOG_ERROR(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}