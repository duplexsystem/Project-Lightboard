//
// Created by duplex on 2/28/21.
//

#include "vulkanRender.h"
#include "../vulkanManager.h"
#include "../Initlization/vulkanBoilerplateManager.h"
#include "../Initlization/vulkanCommandBufferManager.h"
#include "../Initlization/vulkanSyncManager.h"
#include "../Utils/vulkanDebugUtils.h"
#include "../../windowManager.h"

#include <vulkan/vulkan.hpp>
#include <VkBootstrap.h>
#include <iostream>

void vulkanRender :: pollRender() {
    vulkanManager::device.waitForFences(1, &vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    auto acquireNextImageReturn = vulkanManager::device.acquireNextImageKHR(vulkanManager::swapChain, UINT64_MAX, vulkanSyncManager::imageAvailableSemaphores[vulkanSyncManager::currentFrame], nullptr, &imageIndex);
    if (acquireNextImageReturn == vk::Result::eErrorOutOfDateKHR) {
        vulkanBoilerplateManager::reinitSwapChain();
        return;
    } else if (acquireNextImageReturn != vk::Result::eSuccess && acquireNextImageReturn != vk::Result::eSuboptimalKHR) {
        throw std::runtime_error("Failed to Acquire Swap Chain Image. Error:" + std::string(vulkanDebugUtils::to_string(acquireNextImageReturn)) + "\n");
    }

    if (vulkanSyncManager::imagesInFlight[imageIndex].operator=(nullptr)) {
        vulkanManager::device.waitForFences(1, &vulkanSyncManager::imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    vulkanSyncManager::imagesInFlight[imageIndex] = vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame];

    vk::SubmitInfo submitInfo{};

    vk::Semaphore waitSemaphores[] = {vulkanSyncManager::imageAvailableSemaphores[vulkanSyncManager::currentFrame]};
    vk::PipelineStageFlags waitStages[] = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vulkanCommandBufferManager::commandBuffers[imageIndex];

    vk::Semaphore signalSemaphores[] = {vulkanSyncManager::renderFinishedSemaphores[vulkanSyncManager::currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vulkanManager::device.resetFences(1, &vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame]);

    auto queueSubmitReturn = vulkanManager::graphicsQueue.submit(1, &submitInfo, vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame]);
    if (queueSubmitReturn != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to Draw Command Buffer. Error:" + std::string(vulkanDebugUtils::to_string(queueSubmitReturn)) + "\n");
    }

    vk::PresentInfoKHR presentInfo{};

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    vk::SwapchainKHR swapChains[] = {vulkanManager::swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    auto queuePresentRetrun = vulkanManager::presentQueue.presentKHR(&presentInfo);
    if (queuePresentRetrun == vk::Result::eSuboptimalKHR || queuePresentRetrun == vk::Result::eErrorOutOfDateKHR || windowManager::framebufferResized) {
        windowManager::framebufferResized = false;
        vulkanBoilerplateManager::reinitSwapChain();
    } else if (queuePresentRetrun != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to Present Swap Chain Image. Error:" + std::string(vulkanDebugUtils::to_string(queuePresentRetrun)) + "\n");
    }

    vulkanSyncManager::currentFrame = (vulkanSyncManager::currentFrame + 1) % vulkanSyncManager::MAX_FRAMES_IN_FLIGHT;
}