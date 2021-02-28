//
// Created by duplex on 2/28/21.
//

#include "vulkanRender.h"
#include "../vulkanManager.h"
#include "../Initlization/vulkanBoilerplateManager.h"
#include "../Initlization/vulkanCommandBufferManager.h"
#include "../Initlization/vulkanSyncManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.h>
#include <VkBootstrap.h>

void vulkanRender :: pollRender() {
    vkWaitForFences(vulkanManager::device, 1, &vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    auto acquireNextImageReturn = vkAcquireNextImageKHR(vulkanManager::device, vulkanManager::swapChain, UINT64_MAX, vulkanSyncManager::imageAvailableSemaphores[vulkanSyncManager::currentFrame], VK_NULL_HANDLE, &imageIndex);
    if (acquireNextImageReturn == VK_ERROR_OUT_OF_DATE_KHR) {
        vulkanBoilerplateManager::reinitSwapChain();
        return;
    } else if (acquireNextImageReturn != VK_SUCCESS && acquireNextImageReturn != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to Acquire Swap Chain Image. Error:" + std::string(vulkanDebugUtils::to_string(acquireNextImageReturn)) + "\n");
    }

    if (vulkanSyncManager::imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(vulkanManager::device, 1, &vulkanSyncManager::imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    vulkanSyncManager::imagesInFlight[imageIndex] = vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {vulkanSyncManager::imageAvailableSemaphores[vulkanSyncManager::currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vulkanCommandBufferManager::commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {vulkanSyncManager::renderFinishedSemaphores[vulkanSyncManager::currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(vulkanManager::device, 1, &vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame]);

    auto queueSubmitReturn = vkQueueSubmit(vulkanManager::graphicsQueue, 1, &submitInfo, vulkanSyncManager::inFlightFences[vulkanSyncManager::currentFrame]);
    if (queueSubmitReturn != VK_SUCCESS) {
        throw std::runtime_error("Failed to Draw Command Buffer. Error:" + std::string(vulkanDebugUtils::to_string(queueSubmitReturn)) + "\n");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {vulkanManager::swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    auto queuePresentRetrun = vkQueuePresentKHR(vulkanManager::presentQueue, &presentInfo);
    if (queuePresentRetrun == VK_ERROR_OUT_OF_DATE_KHR || queuePresentRetrun == VK_SUBOPTIMAL_KHR) {
        vulkanBoilerplateManager::reinitSwapChain();
    } else if (queuePresentRetrun != VK_SUCCESS) {
        throw std::runtime_error("Failed to Present Swap Chain Image. Error:" + std::string(vulkanDebugUtils::to_string(queuePresentRetrun)) + "\n");
    }

    vulkanSyncManager::currentFrame = (vulkanSyncManager::currentFrame + 1) % vulkanSyncManager::MAX_FRAMES_IN_FLIGHT;
}