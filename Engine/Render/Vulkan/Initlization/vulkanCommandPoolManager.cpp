//
// Created by duplex on 2/27/21.
//

#include "vulkanCommandPoolManager.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.hpp>

vk::CommandPool vulkanCommandPoolManager :: commandPool;

void vulkanCommandPoolManager :: initCommandPool() {
    vk::CommandPoolCreateInfo poolInfo{};
    poolInfo.queueFamilyIndex = vulkanManager::graphicsQueueFamily;

    auto commandPoolReturn = vulkanManager::device.createCommandPool(&poolInfo, nullptr, &commandPool);
    if (commandPoolReturn!= vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create Command Pool. Error: " + std::string(vulkanDebugUtils::to_string(commandPoolReturn)) + "\n");
    }

}

void vulkanCommandPoolManager :: cleanupCommandPool() {
    vkDestroyCommandPool(vulkanManager::device, commandPool, nullptr);
}
