cmake_minimum_required(VERSION 3.1)

project(VulkanApiTutorial CXX)

message("current dir: ${CMAKE_CURRENT_SOURCE_DIR}")

set(project_name VulkanApiTutorial)
set(HAVE_LIBC TRUE)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/external/fmt/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/gli)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/fmt/include)

add_subdirectory(external/fmt)
#message(${CPP_FILES})
#set(SRC main.cpp VulkanApplication.cpp VulkanInstance.cpp VulkanLayerAndExtension.cpp VulkanApplication.h VulkanInstance.h VulkanLayerAndExtension.h)
add_executable(${project_name} main.cpp ${CPP_FILES} ${HPP_FILES}  )
target_link_libraries(${project_name} fmt)

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message("vulkan found")
    target_include_directories(${project_name} PRIVATE Vulkan::Vulkan)
    target_link_libraries(${project_name} Vulkan::Vulkan)
endif()

if(WIN32)
set(glfw3_DIR "C:\\Program Files (x86)\\GLFW\\lib\\cmake\\glfw3")
endif()
find_package(glfw3 REQUIRED)
if(glfw3_FOUND)
    message("${GLFW_INCLUDE_DIR}")
    target_include_directories(${project_name} PRIVATE ${GLFW_INCLUDE_DIR})
    target_link_libraries(${project_name} glfw)
endif()
