//
// Created by duplex on 2/24/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANSURFACEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANSURFACEMANAGER_H


class vulkanSurfaceManager {
    public:
        static VkSurfaceKHR surface;

        static void initSurface();

        static void cleanupSurface();
};


#endif //PROJECT_LIGHTBOARD_VULKANSURFACEMANAGER_H
