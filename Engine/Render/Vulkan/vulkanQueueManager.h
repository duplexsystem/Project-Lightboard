//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANQUEUEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANQUEUEMANAGER_H

#include <vulkan/vulkan.h>
#include <cstdint>
#include <optional>
#include <vector>
#include <set>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class vulkanQueueManager {
    public:
        static VkQueue graphicsQueue;

        static VkQueue presentQueue;

        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);

        static void initQueueFamilies(QueueFamilyIndices &, std::vector<VkDeviceQueueCreateInfo> &, std::set<uint32_t> &);
};

#endif //PROJECT_LIGHTBOARD_VULKANQUEUEMANAGER_H
