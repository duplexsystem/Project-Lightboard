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
        static const uint32_t WIDTH;

        static const uint32_t HEIGHT;

        static GLFWwindow* window;

        static bool framebufferResized;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        static void initWindow();

        static const char** getWindowExtents(uint32_t &glfwExtensionCount);

        static VkResult initWindowSurface(VkInstance instance, VkSurfaceKHR &surface);

        static void pollWindow();

        static void waitWhileMinimized();

        static bool shouldClose();

        static void cleanupWindow();
};


#endif //PROJECT_LIGHTBOARD_WINDOWMANAGER_H
