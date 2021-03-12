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

#include <vulkan/vulkan.hpp>
#include <iostream>

vk::Instance vulkanManager :: instance;

vk::SurfaceKHR vulkanManager :: surface;

vk::PhysicalDevice vulkanManager :: physicalDevice;

vk::Device vulkanManager :: device;

vk::Queue vulkanManager :: graphicsQueue;
uint32_t vulkanManager :: graphicsQueueFamily;

vk::Queue vulkanManager :: presentQueue;
uint32_t vulkanManager :: presentQueueFamily;

vk::SwapchainKHR vulkanManager :: swapChain;
std::vector<vk::Image> vulkanManager :: swapChainImages;
vk::Format vulkanManager :: swapChainImageFormat;
vk::Extent2D vulkanManager :: swapChainExtent;
std::vector<vk::ImageView> vulkanManager :: swapChainImageViews;


void vulkanManager :: initVulkan() {
    vulkanBoilerplateManager::initBoilerplate();

    initVulkanPipeline(true);

    vulkanSyncManager::initSync();
}

void vulkanManager :: initVulkanPipeline(bool initCommandPool) {

    vulkanRenderPassManager::initRenderPass();

    std::vector<vulkanShader> shaders{vulkanShader("triangle.frag"), vulkanShader("triangle.vert")};

    vulkanGraphicsPipelineManager::initGraphicsPipeline(shaders);

    for (vulkanShader shader : shaders) {
        device.destroyShaderModule(shader.shaderModule, nullptr);
    }
    shaders.clear(); //TODO MEMORY LEAK

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


