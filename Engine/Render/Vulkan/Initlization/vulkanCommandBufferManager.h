//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANCOMMANDBUFFERMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANCOMMANDBUFFERMANAGER_H

#include <vulkan/vulkan.hpp>
#include <vector>

class vulkanCommandBufferManager {
    public:
        static std::vector<vk::CommandBuffer> commandBuffers;

        static void initCommandBuffer();

        static void cleanupCommandBuffer();
};


#endif //PROJECT_LIGHTBOARD_VULKANCOMMANDBUFFERMANAGER_H
