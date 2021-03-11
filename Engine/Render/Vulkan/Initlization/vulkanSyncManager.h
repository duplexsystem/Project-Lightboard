//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANSYNCMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANSYNCMANAGER_H

#include <vulkan/vulkan.hpp>
#include <vector>

class vulkanSyncManager {
    public:
        static const int MAX_FRAMES_IN_FLIGHT;

        static std::vector<vk::Semaphore> imageAvailableSemaphores;

        static std::vector<vk::Semaphore> renderFinishedSemaphores;

        static std::vector<vk::Fence> inFlightFences;

        static std::vector<vk::Fence> imagesInFlight;

        static size_t currentFrame;

        static void initSync();

        static void cleanupSync();
};


#endif //PROJECT_LIGHTBOARD_VULKANSYNCMANAGER_H
