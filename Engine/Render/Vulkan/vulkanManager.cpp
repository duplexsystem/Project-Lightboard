//
// Created by duplex on 2/22/21.
//

#include "vulkanManager.h"
#include "Initlization/vulkanBoilerplateManager.h"
#include "Initlization/vulkanGraphicsPipelineManager.h"
#include "Initlization/vulkanRenderPassManager.h"
#include "Initlization/vulkanFramebufferManager.h"
#include "Initlization/vulkanCommandPoolManager.h"
#include "Initlization/vulkanCommandBufferManager.h"
#include "Initlization/vulkanSyncManager.h"
#include "Render/vulkanRender.h"

#include <vulkan/vulkan.h>

VkInstance vulkanManager :: instance;

VkSurfaceKHR vulkanManager :: surface;

VkPhysicalDevice vulkanManager :: physicalDevice;

VkDevice vulkanManager :: device;

VkQueue vulkanManager :: graphicsQueue;
uint32_t vulkanManager :: graphicsQueueFamily;

VkQueue vulkanManager :: presentQueue;
uint32_t vulkanManager :: presentQueueFamily;

VkSwapchainKHR vulkanManager :: swapChain;
std::vector<VkImage> vulkanManager :: swapChainImages;
VkFormat vulkanManager :: swapChainImageFormat;
VkExtent2D vulkanManager :: swapChainExtent;
std::vector<VkImageView> vulkanManager :: swapChainImageViews;


void vulkanManager :: initVulkan() {
    vulkanBoilerplateManager::initBoilerplate();

    initVulkanPipeline(true);

    vulkanSyncManager::initSync();
}

void vulkanManager :: initVulkanPipeline(bool initCommandPool) {

    vulkanRenderPassManager::initRenderPass();

    vulkanGraphicsPipelineManager::initGraphicsPipeline();

    vulkanFramebufferManager::initFramebuffer();

    if (initCommandPool) {
        vulkanCommandPoolManager::initCommandPool();
    }

    vulkanCommandBufferManager::initCommandBuffer();
};

void vulkanManager :: pollVulkan() {
    vulkanRender::pollRender();
}

void vulkanManager :: cleanupVulkanPipeline() {
    vkDeviceWaitIdle(device);

    vulkanFramebufferManager::cleanupFramebuffer();

    vulkanCommandBufferManager::cleanupCommandBuffer();

    vulkanGraphicsPipelineManager::cleanupGraphicsPipeline();

    vulkanRenderPassManager::cleanupRenderPass();
}

void vulkanManager :: cleanupVulkan() {
    cleanupVulkanPipeline();

    vulkanSyncManager::cleanupSync();

    vulkanCommandPoolManager::cleanupCommandPool();

    vulkanBoilerplateManager::cleanupBoilerplate();
}


