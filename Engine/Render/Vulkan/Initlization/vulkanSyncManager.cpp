//
// Created by duplex on 2/27/21.
//

#include "vulkanSyncManager.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.hpp>

const int vulkanSyncManager :: MAX_FRAMES_IN_FLIGHT = 2;

std::vector<vk::Semaphore> vulkanSyncManager :: imageAvailableSemaphores;

std::vector<vk::Semaphore> vulkanSyncManager :: renderFinishedSemaphores;

std::vector<vk::Fence> vulkanSyncManager :: inFlightFences;

std::vector<vk::Fence> vulkanSyncManager :: imagesInFlight;

size_t vulkanSyncManager :: currentFrame = 0;

void vulkanSyncManager :: initSync() {
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    imagesInFlight.resize(vulkanManager::swapChainImages.size());

    vk::SemaphoreCreateInfo semaphoreInfo{};

    vk::FenceCreateInfo fenceInfo{};
    fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        auto imageAvailableSemaphoreReturn = vulkanManager::device.createSemaphore(&semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
        auto renderFinishedSemaphoreReturn = vulkanManager::device.createSemaphore(&semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
        auto inFlightFencesReturn = vulkanManager::device.createFence(&fenceInfo, nullptr, &inFlightFences[i]);
        if (imageAvailableSemaphoreReturn != vk::Result::eSuccess || renderFinishedSemaphoreReturn != vk::Result::eSuccess || inFlightFencesReturn != vk::Result::eSuccess) {
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