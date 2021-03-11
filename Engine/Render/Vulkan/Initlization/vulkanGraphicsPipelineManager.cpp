//
// Created by duplex on 2/27/21.
//

#include "vulkanGraphicsPipelineManager.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"
#include "vulkanRenderPassManager.h"

#include <vulkan/vulkan.hpp>

vk::PipelineCache vulkanGraphicsPipelineManager :: pipelineCache;

vk::PipelineLayout vulkanGraphicsPipelineManager :: pipelineLayout;

vk::Pipeline vulkanGraphicsPipelineManager :: graphicsPipeline;

void vulkanGraphicsPipelineManager :: initGraphicsPipeline(std::vector<vulkanShader> shaderVector) {
        std::vector<vk::PipelineShaderStageCreateInfo> shaderVectorShaders;
        for (vulkanShader shader : shaderVector) {
            shaderVectorShaders.push_back(shader.shader);
        }
        vk::PipelineShaderStageCreateInfo* shaderStages = shaderVectorShaders.data();


        vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.vertexBindingDescriptionCount = 0;
        vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
        vertexInputInfo.vertexAttributeDescriptionCount = 0;
        vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

        vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        vk::Viewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) vulkanManager::swapChainExtent.width;
        viewport.height = (float) vulkanManager::swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        vk::Rect2D scissor{};
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent = vulkanManager::swapChainExtent;

        vk::PipelineViewportStateCreateInfo viewportState{};
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        vk::PipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = vk::PolygonMode::eFill;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = vk::CullModeFlagBits::eBack;
        rasterizer.frontFace = vk::FrontFace::eClockwise;
        rasterizer.depthBiasEnable = VK_FALSE;
        rasterizer.depthBiasConstantFactor = 0.0f; // Optional
        rasterizer.depthBiasClamp = 0.0f; // Optional
        rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

        vk::PipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
        multisampling.minSampleShading = 1.0f; // Optional
        multisampling.pSampleMask = nullptr; // Optional
        multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
        multisampling.alphaToOneEnable = VK_FALSE; // Optional

        vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.blendEnable = VK_TRUE;
        colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
        colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
        colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
        colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
        colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
        colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

        vk::PipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f; // Optional
        colorBlending.blendConstants[1] = 0.0f; // Optional
        colorBlending.blendConstants[2] = 0.0f; // Optional
        colorBlending.blendConstants[3] = 0.0f; // Optional

        vk::PipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.setLayoutCount = 0; // Optional
        pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

        auto graphicsPipelineLayoutRetrun = vulkanManager::device.createPipelineLayout(&pipelineLayoutInfo, nullptr, &pipelineLayout);
        if (graphicsPipelineLayoutRetrun != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to create Graphics Pipeline Layout. Error: " + std::string(vulkanDebugUtils::to_string(graphicsPipelineLayoutRetrun)) + "\n");
        }

        vk::GraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = nullptr; // Optional
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = vulkanRenderPassManager::renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = nullptr; // Optional
        pipelineInfo.basePipelineIndex = -1; // Optional

        auto graphicsPipelineReturn = vulkanManager::device.createGraphicsPipelines(pipelineCache, 1, &pipelineInfo, nullptr, &graphicsPipeline);
        if (graphicsPipelineReturn != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to create Graphics Pipeline Layout. Error: " + std::string(vulkanDebugUtils::to_string(graphicsPipelineReturn)) + "\n");
        }
    }


void vulkanGraphicsPipelineManager :: cleanupGraphicsPipeline() {
    vkDestroyPipeline(vulkanManager::device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(vulkanManager::device, pipelineLayout, nullptr);
}