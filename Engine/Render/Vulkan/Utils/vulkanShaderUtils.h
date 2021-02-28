//
// Created by duplex on 2/27/21.
//

#ifndef PROJECT_LIGHTBOARD_VULKANSHADERUTILS_H
#define PROJECT_LIGHTBOARD_VULKANSHADERUTILS_H

#include <vulkan/vulkan.h>
#include <vector>
#include <fstream>

class vulkanShaderUtils {
    public:
        static VkShaderModule getShader(const std::string& filename);

        static VkPipelineShaderStageCreateInfo createShader(VkShaderModule shaderModule, VkShaderStageFlagBits shaderStage);

    private:
        static VkShaderModule createShaderModule(const std::vector<char>& code);

        static std::vector<char> readFile(const std::string& filepath);
};


#endif //PROJECT_LIGHTBOARD_VULKANSHADERUTILS_H
