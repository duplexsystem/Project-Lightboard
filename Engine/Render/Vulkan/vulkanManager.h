//
// Created by duplex on 2/22/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANMANAGER_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include <VkBootstrap.h>

class vulkanManager {
    public:
        static vk::Instance instance;

        static vk::SurfaceKHR surface;

        static vk::PhysicalDevice physicalDevice;

        static vk::Device device;

        static vk::Queue graphicsQueue;

        static uint32_t graphicsQueueFamily;

        static vk::Queue presentQueue;

        static uint32_t presentQueueFamily;

        static vk::SwapchainKHR swapChain;

        static std::vector<vk::Image> swapChainImages;

        static vk::Format swapChainImageFormat;

        static vk::Extent2D swapChainExtent;

        static std::vector<vk::ImageView> swapChainImageViews;

        static void initVulkan();

        static void initVulkanPipeline(bool initCommandPool);

        static void pollVulkan();

        static void cleanupVulkanPipeline();

        static void cleanupVulkan();
};


#endif //PROJECT_LIGHTBOARD_VULKANMANAGER_H
