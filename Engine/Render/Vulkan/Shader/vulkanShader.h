//
// Created by duplex on 3/10/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANSHADER_H
#define PROJECT_LIGHTBOARD_VULKANSHADER_H

#include <vulkan/vulkan.hpp>
#include <string>
#include <vector>
#include <fstream>

class vulkanShader {
    public:
        std::string shaderName;

        vk::ShaderStageFlagBits shaderType;

        vk::PipelineShaderStageCreateInfo shader;

        vk::ShaderModule shaderModule;

        vulkanShader(std::string name);

        ~vulkanShader();

        void markForCleanup();

    private:
        bool cleanup = false;

        vk::ShaderModule getShader(const std::string& filename);

        static vk::PipelineShaderStageCreateInfo createShader(vk::ShaderModule shaderModule, vk::ShaderStageFlagBits shaderStage);


        static vk::ShaderModule createShaderModule(const std::vector<char>& code);

        static std::vector<char> readFile(const std::string& filepath);
};


#endif //PROJECT_LIGHTBOARD_VULKANSHADER_H
