//
// Created by 王海明 on 2022/7/4.
//
#include "Headers.h"
#include "VulkanApplication.h"

int main() {
    try {
        std::cout<<"my vulkan application start ..."<<std::endl;
        theApp.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}