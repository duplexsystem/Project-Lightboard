//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANFRAMEBUFFERMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANFRAMEBUFFERMANAGER_H

#include <vulkan/vulkan.hpp>
#include <vector>

class vulkanFramebufferManager {
    public:
        static std::vector<vk::Framebuffer> swapChainFramebuffers;

        static void initFramebuffer();

        static void cleanupFramebuffer();
};


#endif //PROJECT_LIGHTBOARD_VULKANFRAMEBUFFERMANAGER_H
