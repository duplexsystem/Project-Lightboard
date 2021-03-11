//
// Created by duplex on 3/10/21.
//

#include "vulkanShader.h"
#include "../vulkanManager.h"
#include "../Utils/vulkanDebugUtils.h"

#include <vulkan/vulkan.hpp>
#include <string>



vulkanShader :: vulkanShader(std::string name) {
    shaderName = name + ".spv";

    if (name.ends_with(".vert")) {
        shaderType = vk::ShaderStageFlagBits::eVertex;
    } else if (name.ends_with(".frag")) {
        shaderType = vk::ShaderStageFlagBits::eFragment;
    } else {
        throw std::runtime_error("Shader " + name + "has an invalid extension");
    }

    shader = createShader(getShader(shaderName), shaderType);
}

vk::ShaderModule vulkanShader :: getShader(const std::string& filename) {
    auto shaderCode = readFile("Shaders/" + filename);

    return createShaderModule(shaderCode);
}

vk::PipelineShaderStageCreateInfo vulkanShader :: createShader(vk::ShaderModule shaderModule, vk::ShaderStageFlagBits shaderStage) {
    vk::PipelineShaderStageCreateInfo shaderStageInfo{};
    shaderStageInfo.stage = shaderStage;
    shaderStageInfo.module = shaderModule;
    shaderStageInfo.pName = "main";

    return shaderStageInfo;
}

vk::ShaderModule vulkanShader :: createShaderModule(const std::vector<char>& code) {
    vk::ShaderModuleCreateInfo createInfo{};
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    vk::ShaderModule shaderModule;
    auto shaderModuleReturn = vulkanManager::device.createShaderModule(&createInfo, nullptr, &shaderModule);
    if (shaderModuleReturn != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to Create Shader Module. Error: " + std::string(vulkanDebugUtils::to_string(shaderModuleReturn)) + "\n");
    }

    return shaderModule;
}

std::vector<char> vulkanShader :: readFile(const std::string& filename) {
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
