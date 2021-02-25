//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANLOGICALDEVICEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANLOGICALDEVICEMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>

class vulkanLogicalDeviceManager {
    public:
        static const std::vector<const char*> deviceExtensions;

        static VkDevice device;

        static void initDevice();

        static void cleanupDevice();
};


#endif //PROJECT_LIGHTBOARD_VULKANLOGICALDEVICEMANAGER_H
