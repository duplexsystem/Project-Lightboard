//
// Created by duplex on 2/22/21.
//

#include "windowManager.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

const uint32_t windowManager :: WIDTH = 800;
const uint32_t windowManager :: HEIGHT = 600;

GLFWwindow* windowManager :: window;

bool windowManager :: framebufferResized = false;

void windowManager :: framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<windowManager*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

void windowManager :: initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Project Lightboard", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

const char** windowManager :: getWindowExtents(uint32_t &glfwExtensionCount) {
    return glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
}

VkResult windowManager :: initWindowSurface(VkInstance instance, VkSurfaceKHR &surface) {
    return glfwCreateWindowSurface(instance, window, NULL, &surface);
}

bool windowManager :: shouldClose() {
    return glfwWindowShouldClose(window);
}

void windowManager :: pollWindow() {
    glfwPollEvents();
}

void windowManager :: waitWhileMinimized() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }
}

void windowManager :: cleanupWindow() {
    glfwDestroyWindow(window);

    glfwTerminate();
}
