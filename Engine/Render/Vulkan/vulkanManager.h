//
// Created by duplex on 2/22/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>

class vulkanManager {
    public:
        static VkInstance instance;

        static void initVulkan();

        static void cleanupVulkan();

    private:
        static void createInstance();
};


#endif //PROJECT_LIGHTBOARD_VULKANMANAGER_H
