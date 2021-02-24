//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANLOGICALDEVICEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANLOGICALDEVICEMANAGER_H

#include <vulkan/vulkan.h>

class vulkanLogicalDeviceManager {
    public:
        static VkDevice device;

        static void initLogicalDevice();

        static void cleanupLogicalDevice();
};


#endif //PROJECT_LIGHTBOARD_VULKANLOGICALDEVICEMANAGER_H
