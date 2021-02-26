//
// Created by duplex on 2/25/21.
//

#include "vulkanBoilerplateManager.h"
#include "vulkanDebugUtils.h"
#include "../windowManager.h"

#include <vulkan/vulkan.h>
#include <VkBootstrap.h>

vkb::Instance vulkanBoilerplateManager :: vkbInstance;

const std::vector<const char*> vulkanBoilerplateManager :: neededDeviceExtensions{
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const std::vector<const char*> vulkanBoilerplateManager :: desiredDeviceExtensions{
        VK_EXT_MEMORY_BUDGET_EXTENSION_NAME,
        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
        VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME,
        VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME,
        VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME,
        VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
        VK_EXT_MEMORY_BUDGET_EXTENSION_NAME,
        VK_KHR_BIND_MEMORY_2_EXTENSION_NAME
};

vkb::PhysicalDevice vulkanBoilerplateManager :: vkbPhysicalDevice;

vkb::Device vulkanBoilerplateManager :: vkbDevice;

vkb::Swapchain vulkanBoilerplateManager :: vkbSwapChain;

void vulkanBoilerplateManager :: initBoilerplate() {
    vkb::InstanceBuilder instanceBuilder;

#ifdef NDEBUG
    // Nothing to do if no debug
#else
    instanceBuilder.request_validation_layers();
    for (auto layer : vulkanDebugUtils::validationLayers) {
        instanceBuilder.enable_layer(layer);
    }
    instanceBuilder
            .add_debug_messenger_severity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            .add_debug_messenger_severity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
            .add_debug_messenger_severity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
            .use_default_debug_messenger();
#endif
    instanceBuilder.set_app_name("Project Lightboard")
            .set_engine_name("Project Lightboard")
            .require_api_version(1,0,0)
            .desire_api_version(1,1,0);
    auto instanceBuilderReturn = instanceBuilder.build();
    if (!instanceBuilderReturn) {
        throw std::runtime_error("Failed to create Vulkan instance. Error: " + instanceBuilderReturn.error().message() + "\n");
    }
    vkbInstance = instanceBuilderReturn.value();
    vulkanManager::instance = vkbInstance.instance;
    vulkanDebugUtils::debugMessenger = vkbInstance.debug_messenger;
    vulkanDebugUtils::allocationCallbacks = vkbInstance.allocation_callbacks;

    VkResult surfaceReturn = windowManager::initWindowSurface(vulkanManager::instance, vulkanManager::surface);
    if (surfaceReturn != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Surface. Error: " + std::string(vulkanDebugUtils::to_string(surfaceReturn)) + "\n");
    }

    vkb::PhysicalDeviceSelector physicalDeviceSelector (vkbInstance);
    auto physicalDeviceSelectorReturn = physicalDeviceSelector.set_surface(vulkanManager::surface)
            .add_required_extensions(neededDeviceExtensions)
            .add_desired_extensions(desiredDeviceExtensions)
            .select();
    if (!physicalDeviceSelectorReturn) {
        throw std::runtime_error("Failed to select Device. Error: " + std::string(physicalDeviceSelectorReturn.error().message()) + "\n");
    }
    vkbPhysicalDevice = physicalDeviceSelectorReturn.value();
    vulkanManager::physicalDevice = vkbPhysicalDevice.physical_device;

    std::vector<vkb::CustomQueueDescription> queueDescriptions;
    std::vector<VkQueueFamilyProperties> queueFamilies = vkbPhysicalDevice.get_queue_families();
    for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilies.size ()); i++) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(vkbPhysicalDevice.physical_device, i, vulkanManager::surface, &presentSupport);
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT || presentSupport) {
            // Find the first queue family with graphics operations supported
            queueDescriptions.emplace_back(
                    i, queueFamilies[i].queueCount,
                    std::vector<float> (queueFamilies[i].queueCount, 1.0f));
        }
    }

    vkb::DeviceBuilder deviceBuilder{vkbPhysicalDevice};
    auto deviceReturn = deviceBuilder
            .custom_queue_setup(queueDescriptions)
            .build();
    if (!deviceReturn) {
        throw std::runtime_error("Failed to create Device. Error: " + std::string(deviceReturn.error().message()) + "\n");
    }
    vkbDevice = deviceReturn.value();
    vulkanManager::device = vkbDevice.device;

    auto graphicsQueueReturn = vkbDevice.get_queue (vkb::QueueType::graphics);
    if (!graphicsQueueReturn) {
        throw std::runtime_error("Failed to create Graphics queue. Error: " + std::string(graphicsQueueReturn.error().message()) + "\n");
    }
    vulkanManager::graphicsQueue = graphicsQueueReturn.value();

    auto presentQueueReturn = vkbDevice.get_queue (vkb::QueueType::present);
    if (!presentQueueReturn) {
        throw std::runtime_error("Failed to create Present queue. Error: " + std::string(presentQueueReturn.error().message()) + "\n");
    }
    vulkanManager::presentQueue = presentQueueReturn.value();

    vkb::SwapchainBuilder swapChainBuilder{vkbDevice};
    auto swapChainReturn = swapChainBuilder.build();
    if (!swapChainReturn){
        throw std::runtime_error("Failed to create Swap Chain. Error: " + std::string(swapChainReturn.error().message() + "\n"));
    }
    vkbSwapChain = swapChainReturn.value();
    vulkanManager::swapChain = vkbSwapChain.swapchain;
    vulkanManager::swapChainImages = vkbSwapChain.get_images().value();
    vulkanManager::swapChainImageFormat = vkbSwapChain.image_format;
    vulkanManager::swapChainExtent = vkbSwapChain.extent;
    vulkanManager::swapChainImageViews = vkbSwapChain.get_image_views().value();
}

void vulkanBoilerplateManager :: cleanupBoilerplate() {
    vkbSwapChain.destroy_image_views(vulkanManager::swapChainImageViews);

    vkb::destroy_swapchain(vkbSwapChain);

    vkb::destroy_device(vkbDevice);

    vkDestroySurfaceKHR(vulkanManager::instance, vulkanManager::surface, nullptr);

    vkb::destroy_debug_utils_messenger(vulkanManager::instance, vulkanDebugUtils::debugMessenger, vulkanDebugUtils::allocationCallbacks);

    vkb::destroy_instance(vkbInstance);
}
