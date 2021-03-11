//
// Created by duplex on 2/27/21.
//

#include "vulkanCommandBufferManager.h"
#include "../vulkanManager.h"
#include "vulkanFramebufferManager.h"
#include "vulkanCommandPoolManager.h"
#include "../Utils/vulkanDebugUtils.h"
#include "vulkanRenderPassManager.h"
#include "vulkanGraphicsPipelineManager.h"

#include <vulkan/vulkan.hpp>
#include <vector>

std::vector<vk::CommandBuffer> vulkanCommandBufferManager :: commandBuffers;

void vulkanCommandBufferManager :: initCommandBuffer() {
    commandBuffers.resize(vulkanFramebufferManager::swapChainFramebuffers.size());

    vk::CommandBufferAllocateInfo allocInfo{};
    allocInfo.commandPool = vulkanCommandPoolManager::commandPool;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

    auto commandPoolReturn = vulkanManager::device.allocateCommandBuffers(&allocInfo, commandBuffers.data());
    if (commandPoolReturn != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create Command Pool. Error: " + std::string(vulkanDebugUtils::to_string(commandPoolReturn)) + "\n");
    }

    for (size_t i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        auto commandPoolRecordReturn = vkBeginCommandBuffer(commandBuffers[i], &beginInfo);
        if (static_cast<vk::Result>(commandPoolRecordReturn) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to Being Recording Command Buffer. Error:" + std::string(vulkanDebugUtils::to_string(
                    static_cast<vk::DebugReportObjectTypeEXT>(commandPoolRecordReturn))) + "\n");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = vulkanRenderPassManager::renderPass;
        renderPassInfo.framebuffer = vulkanFramebufferManager::swapChainFramebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = vulkanManager::swapChainExtent;
        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vulkanGraphicsPipelineManager::graphicsPipeline);

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        auto endCommandBufferReturn = vkEndCommandBuffer(commandBuffers[i]) ;
        if (static_cast<vk::Result>(endCommandBufferReturn) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to end Command Buffer. Error: " + std::string(vulkanDebugUtils::to_string(
                    static_cast<vk::DebugReportObjectTypeEXT>(endCommandBufferReturn))) + "\n");
        }

    }
}

void vulkanCommandBufferManager :: cleanupCommandBuffer() {
    vulkanManager::device.freeCommandBuffers(vulkanCommandPoolManager::commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
}