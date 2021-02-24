//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANDEBUGMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANDEBUGMANAGER_H


#include "vulkanManager.h"

class vulkanDebugManager {
    public:
        static VkDebugUtilsMessengerEXT debugMessenger;

        static const std::vector<const char*> validationLayers;

#ifdef NDEBUG
        static const bool enableValidationLayers = false;
#else
        static const bool enableValidationLayers = true;
#endif
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);

        static void initDebugMessenger();

        static void cleanupDebugMessenger();

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);

        static VkResult CreateDebugUtilsMessengerEXT(VkInstance, const VkDebugUtilsMessengerCreateInfoEXT*, const VkAllocationCallbacks*, VkDebugUtilsMessengerEXT*);

        static void DestroyDebugUtilsMessengerEXT(VkInstance, VkDebugUtilsMessengerEXT, const VkAllocationCallbacks*);
};


#endif //PROJECT_LIGHTBOARD_VULKANDEBUGMANAGER_H
