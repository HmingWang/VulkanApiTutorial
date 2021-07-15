cmake_minimum_required(VERSION 3.1)

PROJECT(VulkanApiTutorial CXX)

set(project_name VulkanApiTutorial)
set(HAVE_LIBC TRUE)
set(src main.cpp)
set(headers)
set(CMAKE_CXX_STANDARD 17)

add_executable(${project_name} ${src} ${headers})

find_package(Vulkan)
if(Vulkan_FOUND)
    target_include_directories(${project_name} PRIVATE Vulkan::Vulkan)
    target_link_libraries(${project_name} Vulkan::Vulkan)
endif()

find_package(glfw3)
if(glfw3_FOUND)
    target_include_directories(${project_name} PRIVATE glfw)
    target_link_libraries(${project_name} glfw)
endif()