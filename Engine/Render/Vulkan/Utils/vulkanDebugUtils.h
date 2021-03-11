//
// Created by duplex on 2/23/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANDEBUGUTILS_H
#define PROJECT_LIGHTBOARD_VULKANDEBUGUTILS_H


#include "../vulkanManager.h"

class vulkanDebugUtils {
    public:
        static const std::vector<const char*> validationLayers;

        static vk::DebugUtilsMessengerEXT debugMessenger;

        static const char* to_string( vk::Result r );

        static const char* to_string( vk::DebugReportObjectTypeEXT o);
};


#endif //PROJECT_LIGHTBOARD_VULKANDEBUGUTILS_H
