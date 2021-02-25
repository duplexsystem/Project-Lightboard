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

const std::vector<const char*> vulkanLogicalDeviceManager :: deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void vulkanLogicalDeviceManager :: initDevice() {
    QueueFamilyIndices indices;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies;

    vulkanQueueManager :: initQueueFamilies(indices, queueCreateInfos, uniqueQueueFamilies);

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

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
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &vulkanQueueManager::presentQueue);
}

void vulkanLogicalDeviceManager :: cleanupDevice() {
    vkDestroyDevice(device, nullptr);
}