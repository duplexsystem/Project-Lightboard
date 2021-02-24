//
// Created by duplex on 2/22/21.
//

#include "vulkanManager.h"
#include "vulkanDebugManager.h"
#include "vulkanPhysicalDeviceManager.h"
#include "vulkanLogicalDeviceManager.h"

#include <vulkan/vulkan.h>
#include <stdexcept>

VkInstance vulkanManager :: instance;

void vulkanManager :: initVulkan() {
    createInstance();
    vulkanDebugManager::initDebugMessenger();
    vulkanPhysicalDeviceManager::initPhysicalDevice();
    vulkanLogicalDeviceManager::initLogicalDevice();
}

void vulkanManager :: cleanupVulkan() {
    vulkanLogicalDeviceManager::cleanupLogicalDevice();

    vulkanDebugManager::cleanupDebugMessenger();

    vkDestroyInstance(instance, nullptr);
}


void vulkanManager :: createInstance() {
        if (vulkanDebugManager::enableValidationLayers && !vulkanPhysicalDeviceManager::checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Project Lightboard";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Lightboard";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;


        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (vulkanDebugManager::enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanDebugManager::validationLayers.size());
            createInfo.ppEnabledLayerNames = vulkanDebugManager::validationLayers.data();

            vulkanDebugManager::populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        auto extensions = vulkanPhysicalDeviceManager::getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
}