//
// Created by duplex on 2/27/21.
//

#include "vulkanRenderPassManager.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.hpp>

vk::RenderPass vulkanRenderPassManager :: renderPass;

void vulkanRenderPassManager :: initRenderPass() {
    vk::AttachmentDescription colorAttachment{};
    colorAttachment.format = vulkanManager::swapChainImageFormat;
    colorAttachment.samples = vk::SampleCountFlagBits::e1;
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;


    vk::AttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::SubpassDescription subpass{};
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    vk::SubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

    vk::RenderPassCreateInfo renderPassInfo{};
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    auto renderPassReturn = vulkanManager::device.createRenderPass(&renderPassInfo, nullptr, &renderPass);
    if (renderPassReturn != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create Render Pass. Error: " + std::string(vulkanDebugUtils::to_string(renderPassReturn)) + "\n");
    }

}

void vulkanRenderPassManager :: cleanupRenderPass() {
    vkDestroyRenderPass(vulkanManager::device, renderPass, nullptr);
}