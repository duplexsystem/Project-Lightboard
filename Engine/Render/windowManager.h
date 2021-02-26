//
// Created by duplex on 2/22/21.
//

#ifndef PROJECT_LIGHTBOARD_WINDOWMANAGER_H
#define PROJECT_LIGHTBOARD_WINDOWMANAGER_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>

class windowManager {
    public:
        static GLFWwindow* window;

        static void initWindow();

        static const char** getWindowExtents(uint32_t &glfwExtensionCount);

        static VkResult initWindowSurface(VkInstance instance, VkSurfaceKHR &surface);

        static void pollWindow();

        static bool shouldClose();

        static void cleanupWindow();
};


#endif //PROJECT_LIGHTBOARD_WINDOWMANAGER_H
