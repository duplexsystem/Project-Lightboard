//
// Created by duplex on 2/25/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANBOILERPLATEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANBOILERPLATEMANAGER_H

#include <VkBootstrap.h>

class vulkanBoilerplateManager {
    public:
        static vkb::Instance vkbInstance;

        static const std::vector<const char*> deviceExtensions;

        static vkb::PhysicalDevice vkbPhysicalDevice;

        static vkb::Device vkbDevice;

        static vkb::Swapchain vkbSwapChain;

        static void initBoilerplate();

        static void cleanupBoilerplate();

        static void cleanupInstance();
};


#endif //PROJECT_LIGHTBOARD_VULKANBOILERPLATEMANAGER_H