//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANPHYSICALDEVICEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANPHYSICALDEVICEMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>
#include <cstdint>

class vulkanPhysicalDeviceManager {
    public:
        static VkPhysicalDevice physicalDevice;

        static bool checkValidationLayerSupport();

        static std::vector<const char*> getRequiredExtensions();

        static void initPhysicalDevice();

private:
        static int rateDeviceSuitability(VkPhysicalDevice);
};


#endif //PROJECT_LIGHTBOARD_VULKANPHYSICALDEVICEMANAGER_H
