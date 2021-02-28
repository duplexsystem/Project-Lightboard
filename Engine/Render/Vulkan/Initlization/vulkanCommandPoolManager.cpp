//
// Created by duplex on 2/27/21.
//

#include "vulkanCommandPoolManager.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.h>

VkCommandPool vulkanCommandPoolManager :: commandPool;

void vulkanCommandPoolManager :: initCommandPool() {
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = vulkanManager::graphicsQueueFamily;
    poolInfo.flags = 0; // Optional

    auto commandPoolReturn = vkCreateCommandPool(vulkanManager::device, &poolInfo, nullptr, &commandPool);
    if (commandPoolReturn!= VK_SUCCESS) {
        throw std::runtime_error("Failed to create Command Pool. Error: " + std::string(vulkanDebugUtils::to_string(commandPoolReturn)) + "\n");
    }

}

void vulkanCommandPoolManager :: cleanupCommandPool() {
    vkDestroyCommandPool(vulkanManager::device, commandPool, nullptr);
}
