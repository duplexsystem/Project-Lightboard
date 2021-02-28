//
// Created by duplex on 2/22/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>
#include <VkBootstrap.h>

class vulkanManager {
    public:
        static VkInstance instance;

        static VkSurfaceKHR surface;

        static VkPhysicalDevice physicalDevice;

        static VkDevice device;

        static VkQueue graphicsQueue;

        static uint32_t graphicsQueueFamily;

        static VkQueue presentQueue;

        static uint32_t presentQueueFamily;

        static VkSwapchainKHR swapChain;

        static std::vector<VkImage> swapChainImages;

        static VkFormat swapChainImageFormat;

        static VkExtent2D swapChainExtent;

        static std::vector<VkImageView> swapChainImageViews;

        static void initVulkan();

        static void initVulkanPipeline(bool initCommandPool);

        static void pollVulkan();

        static void cleanupVulkanPipeline();

        static void cleanupVulkan();
};


#endif //PROJECT_LIGHTBOARD_VULKANMANAGER_H
