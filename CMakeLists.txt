cmake_minimum_required(VERSION 3.16)
project(Project_LightBoard)

#Compiler Options
set(CMAKE_CXX_STANDARD 20)

#LLD
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    find_program(LLD_FOUND ccache)
    if(LLD_FOUND)
        string(APPEND CMAKE_EXE_LINKER_FLAGS " -fuse-ld=lld")
        string(APPEND CMAKE_SHARED_LINKER_FLAGS " -fuse-ld=lld")
        string(APPEND CMAKE_MODULE_LINKER_FLAGS " -fuse-ld=lld")
        message(STATUS "Using LLD Linker")
    endif()
endif()

#CCache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    message(STATUS "Using Ccache")
endif(CCACHE_FOUND)

#Enable System Specific Compiler Optimizations
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} "-dumpversion" OUTPUT_VARIABLE GCC_VERSION_STRING)
    if(GCC_VERSION_STRING VERSION_GREATER 4.2 AND NOT APPLE AND NOT CMAKE_CROSSCOMPILING)
        SET(ARCH_FLAGS "-march=native")
        message(STATUS "Using CPU native flags for SSE optimization: ${ARCH_FLAGS}")
    endif()
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/Modules/FindAVX.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/Modules/FindSSE.cmake")
string(APPEND CMAKE_CXX_FLAGS " ${ARCH_FLAGS} ${AVX_FLAGS} ${SSE_FLAGS}")

#General Optimizations
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        string(APPEND CMAKE_CXX_FLAGS " -O0")
        message(STATUS "Using O0")
    else()
        string(APPEND CMAKE_CXX_FLAGS " -O3")
        message(STATUS "Using O3")
    endif()
endif()

add_executable(Project_LightBoard Engine/main.cpp Engine/Render/renderManager.cpp Engine/Render/renderManager.h Engine/Render/windowManager.cpp Engine/Render/windowManager.h Engine/Render/Vulkan/vulkanManager.cpp Engine/Render/Vulkan/vulkanManager.h Engine/Render/Vulkan/vulkanDebugUtils.cpp Engine/Render/Vulkan/vulkanDebugUtils.h Engine/Render/Vulkan/vulkanBoilerplateManager.cpp Engine/Render/Vulkan/vulkanBoilerplateManager.h)

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