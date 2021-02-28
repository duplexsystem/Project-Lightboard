//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANDEBUGUTILS_H
#define PROJECT_LIGHTBOARD_VULKANDEBUGUTILS_H


#include "../vulkanManager.h"

class vulkanDebugUtils {
    public:
        static const std::vector<const char*> validationLayers;

        static VkDebugUtilsMessengerEXT debugMessenger;

        static const char* to_string( VkResult r );

        static const char* to_string( VkDebugReportObjectTypeEXT o);
};


#endif //PROJECT_LIGHTBOARD_VULKANDEBUGUTILS_H
