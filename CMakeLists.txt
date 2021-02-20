cmake_minimum_required(VERSION 3.17)
project(Project_LightBoard )

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_LightBoard Engine/main.cpp Engine/Render/render.cpp Engine/Render/render.h)


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

#SPIRV-Tools
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SPIRV-Tools)
target_link_libraries(Project_LightBoard SPIRV-Tools)

#ShaderC
set(SHADERC_SKIP_INSTALL ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_TESTS ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/shaderc)
target_link_libraries(Project_LightBoard shaderc)
