//
// Created by duplex on 2/25/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANBOILERPLATEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANBOILERPLATEMANAGER_H

#include "../Shader/vulkanShader.h"

#include <vulkan/vulkan.hpp>
#include <VkBootstrap.h>

class vulkanBoilerplateManager {
    public:
        static vkb::Instance vkbInstance;

        static const std::vector<const char*> neededDeviceExtensions;

        static const std::vector<const char*> desiredDeviceExtensions;

        static vkb::PhysicalDevice vkbPhysicalDevice;

        static vkb::Device vkbDevice;

        static vkb::Swapchain vkbSwapChain;

        static void initBoilerplate();

        static void initBoilerplatePipeline(vulkanShader shaderArray[]);

        static void reinitSwapChain();

        static void cleanupBoilerplate();

    private:
        static void initImageViews();
};


#endif //PROJECT_LIGHTBOARD_VULKANBOILERPLATEMANAGER_H
