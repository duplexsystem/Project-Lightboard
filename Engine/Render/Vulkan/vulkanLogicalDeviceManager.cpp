//
// Created by duplex on 2/23/21.
//

#include "vulkanLogicalDeviceManager.h"
#include "vulkanQueueManager.h"
#include "vulkanPhysicalDeviceManager.h"
#include "vulkanDebugManager.h"

#include <vulkan/vulkan.h>
#include <stdexcept>

VkDevice vulkanLogicalDeviceManager :: device;

void vulkanLogicalDeviceManager :: initLogicalDevice() {
    QueueFamilyIndices indices = vulkanQueueManager::findQueueFamilies(vulkanPhysicalDeviceManager::physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

    if (vulkanDebugManager::enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanDebugManager::validationLayers.size());
        createInfo.ppEnabledLayerNames = vulkanDebugManager::validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(vulkanPhysicalDeviceManager::physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &vulkanQueueManager::graphicsQueue);
}

void vulkanLogicalDeviceManager :: cleanupLogicalDevice() {
    vkDestroyDevice(device, nullptr);
}