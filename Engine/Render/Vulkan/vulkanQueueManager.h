//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANQUEUEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANQUEUEMANAGER_H

#include <vulkan/vulkan.h>
#include <cstdint>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class vulkanQueueManager {
    public:
        static VkQueue graphicsQueue;

        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
};

#endif //PROJECT_LIGHTBOARD_VULKANQUEUEMANAGER_H
