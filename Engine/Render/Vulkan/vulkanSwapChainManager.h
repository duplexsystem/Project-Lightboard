//
// Created by duplex on 2/24/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANSWAPCHAINMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANSWAPCHAINMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class vulkanSwapChainManager {
    public:
        static VkSwapchainKHR swapChain;

        static std::vector<VkImage> swapChainImages;

        static VkFormat swapChainImageFormat;

        static VkExtent2D swapChainExtent;

        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&);

        static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);

        static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);

        static void initSwapChain();

        static void cleanupSwapChain();
};


#endif //PROJECT_LIGHTBOARD_VULKANSWAPCHAINMANAGER_H
