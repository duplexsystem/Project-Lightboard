//
// Created by duplex on 2/22/21.
//

#include "vulkanManager.h"
#include "vulkanBoilerplateManager.h"
#include "vulkanImageViewManager.h"

#include <vulkan/vulkan.h>
#include <VkBootstrap.h>

VkInstance vulkanManager :: instance;

VkSurfaceKHR vulkanManager :: surface;

const std::vector<const char*> vulkanManager :: deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkPhysicalDevice vulkanManager :: physicalDevice;

VkDevice vulkanManager :: device;

VkQueue vulkanManager :: graphicsQueue;
VkQueue vulkanManager :: presentQueue;

VkSwapchainKHR vulkanManager :: swapChain;

void vulkanManager :: initVulkan() {
    vulkanBoilerplateManager::initBoilerplate();

    vulkanImageViewManager::initImageViews();
}

void vulkanManager :: cleanupVulkan() {
    vulkanImageViewManager::cleanupImageView();

    vulkanBoilerplateManager::cleanupBoilerplate();

    vkDestroySurfaceKHR(instance, surface, nullptr);

    vulkanBoilerplateManager::cleanupInstance();
}


