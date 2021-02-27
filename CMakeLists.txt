cmake_minimum_required(VERSION 3.16)

#Use Clang if available
find_program(CLANG_FOUND clang)
if(CLANG_FOUND)
    SET (CMAKE_C_COMPILER "/usr/bin/clang")
    SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()

project(Project_LightBoard)

#Compiler Options
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        string(APPEND CMAKE_C_FLAGS " -O0 -g")
        string(APPEND CMAKE_CXX_FLAGS " -O0 -g")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES Release)
        string(APPEND CMAKE_C_FLAGS " -O3 -DNDEBUG -fmerge-all-constants -fomit-frame-pointer")
        string(APPEND CMAKE_CXX_FLAGS " -O3 -DNDEBUG -fmerge-all-constants -fomit-frame-pointer")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
        string(APPEND CMAKE_C_FLAGS " -O3 -g -fmerge-all-constants")
        string(APPEND CMAKE_CXX_FLAGS " -O3 -g -fmerge-all-constants")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
        string(APPEND CMAKE_C_FLAGS " -Os -DNDEBUG -fmerge-all-constants")
        string(APPEND CMAKE_CXX_FLAGS " -Os -DNDEBUG -fmerge-all-constants")
    endif()
endif()

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
string(APPEND CMAKE_C_FLAGS " ${ARCH_FLAGS} ${AVX_FLAGS} ${SSE_FLAGS}")
string(APPEND CMAKE_CXX_FLAGS " ${ARCH_FLAGS} ${AVX_FLAGS} ${SSE_FLAGS}")

#Print Full flags
message(STATUS "Using C Flags: ${CMAKE_C_FLAGS}")
message(STATUS "Using C++ Flags: ${CMAKE_CXX_FLAGS}")

add_executable(Project_LightBoard Engine/main.cpp Engine/Render/renderManager.cpp Engine/Render/renderManager.h Engine/Render/windowManager.cpp Engine/Render/windowManager.h Engine/Render/Vulkan/vulkanManager.cpp Engine/Render/Vulkan/vulkanManager.h Engine/Render/Vulkan/vulkanDebugUtils.cpp Engine/Render/Vulkan/vulkanDebugUtils.h Engine/Render/Vulkan/vulkanBoilerplateManager.cpp Engine/Render/Vulkan/vulkanBoilerplateManager.h Engine/Render/Vulkan/vulkanGraphicsPipelineManager.cpp Engine/Render/Vulkan/vulkanGraphicsPipelineManager.h)

#LTO
set_property(TARGET Project_LightBoard PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "DEBUG")



#---------------------------Rendering------------------------
#GLM
set(glm_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)
target_link_libraries(Project_LightBoard glm::glm)

#GLFM
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libs/glfw)
target_link_libraries(Project_LightBoard glfw)

#Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(Project_LightBoard vulkan)

#Vk-bootstrap
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libs/vk-bootstrap)
target_link_libraries(Project_LightBoard vk-bootstrap)

#Vulkan Memory Allocator
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libs/VulkanMemoryAllocator)
target_link_libraries(Project_LightBoard VulkanMemoryAllocator)