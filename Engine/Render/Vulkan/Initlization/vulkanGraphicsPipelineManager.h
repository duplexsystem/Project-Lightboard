//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANGRAPHICSPIPELINEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANGRAPHICSPIPELINEMANAGER_H

#include <vulkan/vulkan.h>

class vulkanGraphicsPipelineManager {
    public:
        static VkPipelineLayout pipelineLayout;

        static VkPipeline graphicsPipeline;

        static void initGraphicsPipeline();

        static void cleanupGraphicsPipeline();
};


#endif //PROJECT_LIGHTBOARD_VULKANGRAPHICSPIPELINEMANAGER_H
