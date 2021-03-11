cmake_minimum_required(VERSION 3.16)

project(Project_LightBoard)

#CCache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_FOUND}")
    message(STATUS "Using Ccache")
endif(CCACHE_FOUND)

#Compiler Options
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        string(APPEND CMAKE_C_FLAGS " -O0 -g")
        string(APPEND CMAKE_CXX_FLAGS " -O0 -g")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES Release)
        string(APPEND CMAKE_C_FLAGS " -O3 -DNDEBUG -fmerge-all-constants -fomit-frame-pointer -flto")
        string(APPEND CMAKE_CXX_FLAGS " -O3 -DNDEBUG -fmerge-all-constants -fomit-frame-pointer -flto")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
        string(APPEND CMAKE_C_FLAGS " -O3 -g -fmerge-all-constants -flto")
        string(APPEND CMAKE_CXX_FLAGS " -O3 -g -fmerge-all-constants -flto")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
        string(APPEND CMAKE_C_FLAGS " -Os -DNDEBUG -fmerge-all-constants -fomit-frame-pointer -flto")
        string(APPEND CMAKE_CXX_FLAGS " -Os -DNDEBUG -fmerge-all-constants -fomit-frame-pointer  -flto")
    endif()
endif()

#LLD
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    find_program(LLD_FOUND ld.lld)
    if(LLD_FOUND)
        string(APPEND CMAKE_EXE_LINKER_FLAGS " -fuse-ld=lld")
        string(APPEND CMAKE_SHARED_LINKER_FLAGS " -fuse-ld=lld")
        string(APPEND CMAKE_MODULE_LINKER_FLAGS " -fuse-ld=lld")
        message(STATUS "Using LLD Linker")
    endif()
endif()

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

#Add Source Files for Build
file(GLOB_RECURSE ENGINE_SOURCE CONFIGURE_DEPENDS
        "Engine/*.h"
        "Engine/*.cpp"
        "Engine/*.hpp"
        )
add_executable(Project_LightBoard ${ENGINE_SOURCE} Engine/Render/Vulkan/Shader/vulkanShader.cpp Engine/Render/Vulkan/Shader/vulkanShader.h)

#Compile and Include Shaders
include("${CMAKE_CURRENT_SOURCE_DIR}/Modules/CompileShaders.cmake")
add_dependencies(Project_LightBoard Shaders)
add_custom_command(TARGET Project_LightBoard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Project_LightBoard>/Shaders/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/Shaders"
        "$<TARGET_FILE_DIR:Project_LightBoard>/Shaders")

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "DEBUG")



#---------------------------Rendering------------------------
#GLM
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libs/glm)
target_link_libraries(Project_LightBoard glm)

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

#Vulkan Memory Allocator Hpp
#file(GLOB_RECURSE VulkanMemoryAllocator_Hpp_SOURCE CONFIGURE_DEPENDS
#        "${CMAKE_CURRENT_SOURCE_DIR}/Libs/VulkanMemoryAllocator-Hpp/*.h"
#        "${CMAKE_CURRENT_SOURCE_DIR}/Libs/VulkanMemoryAllocator-Hpp/*.cpp"
#        "${CMAKE_CURRENT_SOURCE_DIR}/Libs/VulkanMemoryAllocator-Hpp/*.hpp"
#        )
#add_library(VulkanMemoryAllocator-Hpp INTERFACE)
#target_sources(VulkanMemoryAllocator-Hpp INTERFACE ${VulkanMemoryAllocator_Hpp_SOURCE})
#target_link_libraries(Project_LightBoard VulkanMemoryAllocator-Hpp)

#Vookoo
