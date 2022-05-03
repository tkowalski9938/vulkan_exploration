#include "graphicsPipeline.h"
#include "../shaders/readShader.h"
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <assert.h>


static VkShaderModule createShaderModule(VkDevice *device, shaderData *data) {
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = sizeof(char) * (data->num);
    createInfo.pCode = (const uint32_t *) data->binary;
    
    VkShaderModule shaderModule;
    assert((vkCreateShaderModule(*device, &createInfo, NULL, &shaderModule) == VK_SUCCESS) && "failed to create shader module");
    
    return shaderModule;
}

void createGraphicsPipeline(VkDevice *device) {
    // dynamically allocated, need to free
    shaderData *vertShader = readShader("/Users/tkowalsk/Desktop/CoreAVI/Learning Vulkan/vulkan_exploration/vulkan_exploration/shaders/vert.spv");
    
    // dynamically allocated, need to free
    shaderData *fragShader = readShader("/Users/tkowalsk/Desktop/CoreAVI/Learning Vulkan/vulkan_exploration/vulkan_exploration/shaders/frag.spv");
    
    
    // note these variables are in stack b/c we can destory the shader modules as soon as pipieline creation is finished, since code doesnt compile until graphics pipeline is finished
    VkShaderModule vertShaderModule = createShaderModule(device, vertShader);
    
    VkShaderModule fragShaderModule = createShaderModule(device, fragShader);
    
    vkDestroyShaderModule(*device, vertShaderModule, NULL);
    vkDestroyShaderModule(*device, fragShaderModule, NULL);
    
    freeShaderData(vertShader);
    
    freeShaderData(fragShader);
    
}
