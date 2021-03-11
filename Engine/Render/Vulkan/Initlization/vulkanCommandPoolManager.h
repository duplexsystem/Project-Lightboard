//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANCOMMANDPOOLMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANCOMMANDPOOLMANAGER_H

#include <vulkan/vulkan.hpp>

class vulkanCommandPoolManager {
    public:
        static vk::CommandPool commandPool;

        static void initCommandPool();

        static void cleanupCommandPool();

};


#endif //PROJECT_LIGHTBOARD_VULKANCOMMANDPOOLMANAGER_H
