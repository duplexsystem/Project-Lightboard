//
// Created by duplex on 2/23/21.
//

#include "vulkanDebugUtils.h"

#include <vulkan/vulkan.hpp>

const std::vector<const char*>  vulkanDebugUtils :: validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

vk::DebugUtilsMessengerEXT vulkanDebugUtils :: debugMessenger = nullptr;

const char* vulkanDebugUtils :: to_string(vk::Result r ){
    switch( r ){
        case vk::Result::eSuccess: return "vk::Result::eSuccess";
        case vk::Result::eNotReady: return "VK_NOT_READY";
        case vk::Result::eTimeout: return "VK_TIMEOUT";
        case vk::Result::eEventSet: return "VK_EVENT_SET";
        case vk::Result::eEventReset: return "VK_EVENT_RESET";
        case vk::Result::eIncomplete: return "VK_INCOMPLETE";
        case vk::Result::eErrorOutOfHostMemory: return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case vk::Result::eErrorOutOfDeviceMemory: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case vk::Result::eErrorInitializationFailed: return "VK_ERROR_INITIALIZATION_FAILED";
        case vk::Result::eErrorDeviceLost: return "VK_ERROR_DEVICE_LOST";
        case vk::Result::eErrorMemoryMapFailed: return "VK_ERROR_MEMORY_MAP_FAILED";
        case vk::Result::eErrorLayerNotPresent: return "VK_ERROR_LAYER_NOT_PRESENT";
        case vk::Result::eErrorExtensionNotPresent: return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case vk::Result::eErrorFeatureNotPresent: return "VK_ERROR_FEATURE_NOT_PRESENT";
        case vk::Result::eErrorIncompatibleDriver: return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case vk::Result::eErrorTooManyObjects: return "VK_ERROR_TOO_MANY_OBJECTS";
        case vk::Result::eErrorFormatNotSupported: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case vk::Result::eErrorSurfaceLostKHR: return "VK_ERROR_SURFACE_LOST_KHR";
        case vk::Result::eErrorNativeWindowInUseKHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        case vk::Result::eSuboptimalKHR: return "VK_SUBOPTIMAL_KHR";
        case vk::Result::eErrorOutOfDateKHR: return "VK_ERROR_OUT_OF_DATE_KHR";
        case vk::Result::eErrorIncompatibleDisplayKHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        case vk::Result::eErrorValidationFailedEXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
        case vk::Result::eErrorInvalidShaderNV: return "VK_ERROR_INVALID_SHADER_NV";
        default: return "unrecognized vk::Result code";
    }
}

const char* vulkanDebugUtils :: to_string(vk::DebugReportObjectTypeEXT o ){
    switch( o ){
        case vk::DebugReportObjectTypeEXT::eUnknown: return "Unknown";
        case vk::DebugReportObjectTypeEXT::eInstance: return "Instance";
        case vk::DebugReportObjectTypeEXT::ePhysicalDevice: return "PhysicalDevice";
        case vk::DebugReportObjectTypeEXT::eDevice: return "Device";
        case vk::DebugReportObjectTypeEXT::eQueue: return "Queue";
        case vk::DebugReportObjectTypeEXT::eSemaphore: return "Semaphore";
        case vk::DebugReportObjectTypeEXT::eCommandBuffer: return "CommandBuffer";
        case vk::DebugReportObjectTypeEXT::eFence: return "Fence";
        case vk::DebugReportObjectTypeEXT::eDeviceMemory: return "DeviceMemory";
        case vk::DebugReportObjectTypeEXT::eBuffer: return "Buffer";
        case vk::DebugReportObjectTypeEXT::eImage: return "Image";
        case vk::DebugReportObjectTypeEXT::eEvent: return "Event";
        case vk::DebugReportObjectTypeEXT::eQueryPool: return "QueryPool";
        case vk::DebugReportObjectTypeEXT::eBufferView: return "BufferView";
        case vk::DebugReportObjectTypeEXT::eImageView: return "ImageView";
        case vk::DebugReportObjectTypeEXT::eShaderModule: return "ShaderModule";
        case vk::DebugReportObjectTypeEXT::ePipelineCache: return "PipelineCache";
        case vk::DebugReportObjectTypeEXT::ePipelineLayout: return "PipelineLayout";
        case vk::DebugReportObjectTypeEXT::eRenderPass: return "RenderPass";
        case vk::DebugReportObjectTypeEXT::ePipeline: return "Pipeline";
        case vk::DebugReportObjectTypeEXT::eDescriptorSetLayout: return "DescriptorSetLayout";
        case vk::DebugReportObjectTypeEXT::eSampler: return "Sampler";
        case vk::DebugReportObjectTypeEXT::eDescriptorPool: return "DescriptorPool";
        case vk::DebugReportObjectTypeEXT::eDescriptorSet: return "DescriptorSet";
        case vk::DebugReportObjectTypeEXT::eFramebuffer: return "Framebuffer";
        case vk::DebugReportObjectTypeEXT::eCommandPool: return "Command pool";
        case vk::DebugReportObjectTypeEXT::eSurfaceKHR: return "SurfaceKHR";
        case vk::DebugReportObjectTypeEXT::eSwapchainKHR: return "SwapchainKHR";
        case vk::DebugReportObjectTypeEXT::eDebugReport: return "DebugReport";
        default: return "unrecognized";
    }
}