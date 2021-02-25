//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANPHYSICALDEVICEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANPHYSICALDEVICEMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>
#include <cstdint>
#include "vulkanSwapChainManager.h"

class vulkanPhysicalDeviceManager {
    public:
        static VkPhysicalDevice physicalDevice;

        static bool checkValidationLayerSupport();

        static std::vector<const char*> getRequiredPhysicalExtensions();

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        static void initPhysicalDevice();

private:
        static int rateDeviceSuitability(VkPhysicalDevice);
};


#endif //PROJECT_LIGHTBOARD_VULKANPHYSICALDEVICEMANAGER_H
