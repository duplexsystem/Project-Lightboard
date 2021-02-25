cmake_minimum_required(VERSION 3.16)
project(Project_LightBoard)

#Compiler Options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
string(APPEND CMAKE_CXX_FLAGS " -Ofast -m64")
string(APPEND CMAKE_EXE_LINKER_FLAGS " -fuse-ld=lld -m64")
string(APPEND CMAKE_SHARED_LINKER_FLAGS " -fuse-ld=lld -m64")
string(APPEND CMAKE_MODULE_LINKER_FLAGS " -fuse-ld=lld -m64")
set(ARCH amd64)

#CCache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


#Enable Opts
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindSSE.cmake")
CHECK_FOR_SSE()
string(APPEND CMAKE_CXX_FLAGS " ${SSE_FLAGS_STR}")

add_executable(Project_LightBoard Engine/main.cpp Engine/Render/renderManager.cpp Engine/Render/renderManager.h Engine/Render/windowManager.cpp Engine/Render/windowManager.h Engine/Render/Vulkan/vulkanManager.cpp Engine/Render/Vulkan/vulkanManager.h Engine/Render/Vulkan/vulkanDebugManager.cpp Engine/Render/Vulkan/vulkanDebugManager.h Engine/Render/Vulkan/vulkanPhysicalDeviceManager.cpp Engine/Render/Vulkan/vulkanPhysicalDeviceManager.h Engine/Render/Vulkan/vulkanQueueManager.cpp Engine/Render/Vulkan/vulkanQueueManager.h Engine/Render/Vulkan/vulkanLogicalDeviceManager.cpp Engine/Render/Vulkan/vulkanLogicalDeviceManager.h Engine/Render/Vulkan/vulkanSurfaceManager.cpp Engine/Render/Vulkan/vulkanSurfaceManager.h Engine/Render/Vulkan/vulkanSwapChainManager.cpp Engine/Render/Vulkan/vulkanSwapChainManager.h)

#LTO
set_property(TARGET Project_LightBoard PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "DEBUG")



#---------------------------Rendering------------------------
#GLM
set(glm_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)
target_link_libraries(Project_LightBoard glm::glm)

#GLFM
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
target_link_libraries(Project_LightBoard glfw)

#Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(Project_LightBoard vulkan)

#Vk-bootstrap
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/vk-bootstrap)
target_link_libraries(Project_LightBoard vk-bootstrap)

#Vk-bootstrap
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/VulkanMemoryAllocator)
target_link_libraries(Project_LightBoard VulkanMemoryAllocator)

#SPIRV-Headers
set(SPIRV_HEADERS_SKIP_EXAMPLES ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SPIRV-Headers)
target_link_libraries(Project_LightBoard SPIRV-Headers)

#SPIRV-Tools
set(SPIRV_SKIP_TESTS ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SPIRV-Tools)
target_link_libraries(Project_LightBoard SPIRV-Tools)

#glslang
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glslang)
target_link_libraries(glslang PRIVATE SPIRV-Tools)
target_link_libraries(Project_LightBoard glslang)

#ShaderC
set(SHADERC_SKIP_INSTALL ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_TESTS ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "" FORCE)
set(ASCIIDOCTOR_EXE ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/shaderc)
target_link_libraries(Project_LightBoard shaderc)
