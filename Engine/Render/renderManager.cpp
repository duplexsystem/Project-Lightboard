//
// Created by duplex on 2/20/21.
//

#include "renderManager.h"
#include "windowManager.h"
#include "Vulkan/vulkanManager.h"


void renderManager :: initRender() {
    windowManager::initWindow();

    vulkanManager::initVulkan();
}

void renderManager :: pollRender() {
    while (!windowManager::shouldClose()) {
        windowManager::pollWindow();
    }
}

void renderManager :: cleanupRender() {
    vulkanManager::cleanupVulkan();

    windowManager::cleanupWindow();
}

