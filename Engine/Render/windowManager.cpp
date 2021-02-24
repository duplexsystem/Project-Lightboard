//
// Created by duplex on 2/22/21.
//

#include "windowManager.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

GLFWwindow* window;


void windowManager :: initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Project Lightboard", nullptr, nullptr);
}

const char** windowManager :: getWindowExtents(uint32_t glfwExtensionCount) {
    return glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
}

bool windowManager :: shouldClose() {
    return glfwWindowShouldClose(window);
}

void windowManager :: pollWindow() {
    glfwPollEvents();
}

void windowManager :: cleanupWindow() {
    glfwDestroyWindow(window);

    glfwTerminate();
}
