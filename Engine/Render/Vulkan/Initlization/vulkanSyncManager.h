//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANSYNCMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANSYNCMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>

class vulkanSyncManager {
    public:
        static const int MAX_FRAMES_IN_FLIGHT;

        static std::vector<VkSemaphore> imageAvailableSemaphores;

        static std::vector<VkSemaphore> renderFinishedSemaphores;

        static std::vector<VkFence> inFlightFences;

        static std::vector<VkFence> imagesInFlight;

        static size_t currentFrame;

        static void initSync();

        static void cleanupSync();
};


#endif //PROJECT_LIGHTBOARD_VULKANSYNCMANAGER_H
