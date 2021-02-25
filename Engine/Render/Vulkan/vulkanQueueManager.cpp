//
// Created by duplex on 2/23/21.
//

#include "vulkanQueueManager.h"
#include "vulkanSurfaceManager.h"
#include "vulkanPhysicalDeviceManager.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <set>

VkQueue vulkanQueueManager :: graphicsQueue;
VkQueue vulkanQueueManager :: presentQueue;

QueueFamilyIndices vulkanQueueManager :: findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, vulkanSurfaceManager::surface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

void vulkanQueueManager :: initQueueFamilies(QueueFamilyIndices &indices, std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos, std::set<uint32_t> &uniqueQueueFamilies) {
    indices = findQueueFamilies(vulkanPhysicalDeviceManager::physicalDevice);

    uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }
}