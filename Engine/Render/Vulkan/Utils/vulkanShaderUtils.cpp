//
// Created by duplex on 2/27/21.
//

#include "vulkanShaderUtils.h"
#include "../vulkanManager.h"
#include "vulkanDebugUtils.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>


VkShaderModule vulkanShaderUtils :: getShader(const std::string& filename) {
    auto shaderCode = readFile("Shaders/" + filename + ".spv");

    return createShaderModule(shaderCode);
}

VkPipelineShaderStageCreateInfo vulkanShaderUtils :: createShader(VkShaderModule shaderModule, VkShaderStageFlagBits shaderStage) {
    VkPipelineShaderStageCreateInfo shaderStageInfo{};
    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.stage = shaderStage;
    shaderStageInfo.module = shaderModule;
    shaderStageInfo.pName = "main";

    return shaderStageInfo;
}

VkShaderModule vulkanShaderUtils :: createShaderModule(const std::vector<char>& code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    auto shaderModuleReturn = vkCreateShaderModule(vulkanManager::device, &createInfo, nullptr, &shaderModule);
    if (shaderModuleReturn != VK_SUCCESS) {
        throw std::runtime_error("Failed to Create Shader Module. Error: " + std::string(vulkanDebugUtils::to_string(shaderModuleReturn)) + "\n");
    }

    return shaderModule;
}

std::vector<char> vulkanShaderUtils :: readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open Shader File.\n");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}


