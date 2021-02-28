//
// Created by duplex on 2/27/21.
//

#include "vulkanSyncManager.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.h>

const int vulkanSyncManager :: MAX_FRAMES_IN_FLIGHT = 2;

std::vector<VkSemaphore> vulkanSyncManager :: imageAvailableSemaphores;

std::vector<VkSemaphore> vulkanSyncManager :: renderFinishedSemaphores;

std::vector<VkFence> vulkanSyncManager :: inFlightFences;

std::vector<VkFence> vulkanSyncManager :: imagesInFlight;

size_t vulkanSyncManager :: currentFrame = 0;

void vulkanSyncManager :: initSync() {
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    imagesInFlight.resize(vulkanManager::swapChainImages.size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        auto imageAvailableSemaphoreReturn = vkCreateSemaphore(vulkanManager::device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
        auto renderFinishedSemaphoreReturn = vkCreateSemaphore(vulkanManager::device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
        auto inFlightFencesReturn = vkCreateFence(vulkanManager::device, &fenceInfo, nullptr, &inFlightFences[i]);
        if (imageAvailableSemaphoreReturn != VK_SUCCESS || renderFinishedSemaphoreReturn != VK_SUCCESS || inFlightFencesReturn != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Image Available Semaphore and/or Render Finished Semaphore and/or In Flight Fences Return. "
                                     "Image Available Semaphore Return: " + std::string(vulkanDebugUtils::to_string(imageAvailableSemaphoreReturn)) +
                                     ". Render Finished Semaphore Return: " + std::string(vulkanDebugUtils::to_string(renderFinishedSemaphoreReturn)) +
                                     ". In Flight Fences Return: " + std::string(vulkanDebugUtils::to_string(inFlightFencesReturn)) + "\n");
        }
    }

}

void vulkanSyncManager :: cleanupSync() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(vulkanManager::device, renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(vulkanManager::device, imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(vulkanManager::device, inFlightFences[i], nullptr);
    }
}