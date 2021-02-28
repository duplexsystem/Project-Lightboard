//
// Created by duplex on 2/27/21.
//

#include "vulkanFramebufferManager.h"
#include "../vulkanManager.h"
#include "vulkanRenderPassManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.h>
#include <vector>

std::vector<VkFramebuffer> vulkanFramebufferManager :: swapChainFramebuffers;

void vulkanFramebufferManager :: initFramebuffer() {
    swapChainFramebuffers.resize(vulkanManager::swapChainImageViews.size());

    for (size_t i = 0; i < vulkanManager::swapChainImageViews.size(); i++) {
        VkImageView attachments[] = {
                vulkanManager::swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = vulkanRenderPassManager::renderPass;
        framebufferInfo.attachmentCount = sizeof(attachments)/sizeof(attachments[0]);
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = vulkanManager::swapChainExtent.width;
        framebufferInfo.height = vulkanManager::swapChainExtent.height;
        framebufferInfo.layers = 1;

        auto framebufferReturn = vkCreateFramebuffer(vulkanManager::device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]);
        if (framebufferReturn != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Framebuffer. Error:" + std::string(vulkanDebugUtils::to_string(framebufferReturn)) + "\n");
        }
    }
}

void vulkanFramebufferManager :: cleanupFramebuffer() {
    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(vulkanManager::device, framebuffer, nullptr);
    }
}