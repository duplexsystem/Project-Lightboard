//
// Created by duplex on 2/25/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANIMAGEVIEWMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANIMAGEVIEWMANAGER_H

#include <vulkan/vulkan.h>
#include <VkBootstrap.h>

class vulkanImageViewManager {
    public:
        static std::vector<VkImage> swapChainImages;

        static VkFormat swapChainImageFormat;

        static VkExtent2D swapChainExtent;

        static std::vector<VkImageView> swapChainImageViews;

        static void initImageViews();

        static void cleanupImageView();
};


#endif //PROJECT_LIGHTBOARD_VULKANIMAGEVIEWMANAGER_H
