cmake_minimum_required(VERSION 3.1)

project(VulkanApiTutorial CXX)

message("current dir: ${CMAKE_CURRENT_SOURCE_DIR}")

set(project_name VulkanApiTutorial)
set(HAVE_LIBC TRUE)

set(CMAKE_CXX_STANDARD 17)
#set_property(TARGET ${project_name} PROPERTY CMAKE_CXX_STANDARD 17)

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/gli)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)


#message(${CPP_FILES})
#set(SRC main.cpp VulkanApplication.cpp VulkanInstance.cpp VulkanLayerAndExtension.cpp VulkanApplication.h VulkanInstance.h VulkanLayerAndExtension.h)
add_executable(${project_name} main.cpp ${CPP_FILES} ${HPP_FILES} )

find_package(Vulkan)
if(Vulkan_FOUND)
    message("vulkan found")
    target_include_directories(${project_name} PRIVATE Vulkan::Vulkan)
    target_link_libraries(${project_name} Vulkan::Vulkan)
endif()

find_package(glfw3)
if(glfw3_FOUND)
    message("glfw found")
    target_include_directories(${project_name} PRIVATE glfw)
    target_link_libraries(${project_name} glfw)
endif()

