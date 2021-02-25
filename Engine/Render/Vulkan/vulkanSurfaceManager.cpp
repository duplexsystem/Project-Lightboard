//
// Created by duplex on 2/24/21.
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vulkanSurfaceManager.h"
#include "vulkanManager.h"
#include "../windowManager.h"

#include <vulkan/vulkan.h>
#include <stdexcept>

VkSurfaceKHR vulkanSurfaceManager :: surface;

void vulkanSurfaceManager :: initSurface() {
    if (glfwCreateWindowSurface(vulkanManager::instance, windowManager::window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void vulkanSurfaceManager :: cleanupSurface() {
    vkDestroySurfaceKHR(vulkanManager::instance, surface, nullptr);
}