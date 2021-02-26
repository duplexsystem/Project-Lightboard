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

        static VkQueue presentQueue;

        static VkSwapchainKHR swapChain;

        static std::vector<VkImage> swapChainImages;

        static VkFormat swapChainImageFormat;

        static VkExtent2D swapChainExtent;

        static std::vector<VkImageView> swapChainImageViews;

        static void initVulkan();

        static void cleanupVulkan();

    private:
        static void createInstance();
};


#endif //PROJECT_LIGHTBOARD_VULKANMANAGER_H
