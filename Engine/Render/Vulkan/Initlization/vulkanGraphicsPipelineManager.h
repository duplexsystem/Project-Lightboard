//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANGRAPHICSPIPELINEMANAGER_H
#define PROJECT_LIGHTBOARD_VULKANGRAPHICSPIPELINEMANAGER_H

#include <vulkan/vulkan.hpp>
#include "../Shader/vulkanShader.h"
#include "vulkanRenderPassManager.h"
#include "../../windowManager.h"

class vulkanGraphicsPipelineManager {
    public:
        static vk::PipelineCache pipelineCache;

        static vk::PipelineLayout pipelineLayout;

        static vk::Pipeline graphicsPipeline;

        static void initGraphicsPipeline(std::vector<vulkanShader> shaderVector);

        static void cleanupGraphicsPipeline();
};


#endif //PROJECT_LIGHTBOARD_VULKANGRAPHICSPIPELINEMANAGER_H
