cmake_minimum_required(VERSION 3.1)
set(project_name VulkanApiTutorial)
set(HAVE_LIBC TRUE)
set(src main.cpp)
set(headers)

add_subdirectory("Vk-Helper")

add_executable(${project_name} ${src} ${headers})
find_package(Vulkan)
if(Vulkan_FOUND)
    target_include_directories(${project_name} PRIVATE Vulkan::Vulkan)
    target_link_libraries(${project_name} Vulkan::Vulkan)
endif()