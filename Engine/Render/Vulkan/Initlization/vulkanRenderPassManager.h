//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANRENDERPASSMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANRENDERPASSMANAGER_H

#include <vulkan/vulkan.hpp>

class vulkanRenderPassManager {
    public:
        static vk::RenderPass renderPass;

        static void initRenderPass();

        static void cleanupRenderPass();
};


#endif //PROJECT_LIGHTBOARD_VULKANRENDERPASSMANAGER_H
