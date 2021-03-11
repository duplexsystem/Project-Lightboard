//
// Created by duplex on 2/27/21.
//

#include "vulkanFramebufferManager.h"
#include "../vulkanManager.h"
#include "vulkanRenderPassManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.hpp>
#include <vector>

std::vector<vk::Framebuffer> vulkanFramebufferManager :: swapChainFramebuffers;

void vulkanFramebufferManager :: initFramebuffer() {
    swapChainFramebuffers.resize(vulkanManager::swapChainImageViews.size());

    for (size_t i = 0; i < vulkanManager::swapChainImageViews.size(); i++) {
        vk::ImageView attachments[] = {
                vulkanManager::swapChainImageViews[i]
        };

        vk::FramebufferCreateInfo framebufferInfo{};
        framebufferInfo.renderPass = vulkanRenderPassManager::renderPass;
        framebufferInfo.attachmentCount = sizeof(attachments)/sizeof(attachments[0]);
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = vulkanManager::swapChainExtent.width;
        framebufferInfo.height = vulkanManager::swapChainExtent.height;
        framebufferInfo.layers = 1;

        auto framebufferReturn = vulkanManager::device.createFramebuffer(&framebufferInfo, nullptr, &swapChainFramebuffers[i]);
        if (framebufferReturn != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to create Framebuffer. Error:" + std::string(vulkanDebugUtils::to_string(framebufferReturn)) + "\n");
        }
    }
}

void vulkanFramebufferManager :: cleanupFramebuffer() {
    for (auto framebuffer : swapChainFramebuffers) {
        vulkanManager::device.destroyFramebuffer(framebuffer, nullptr);
    }
}