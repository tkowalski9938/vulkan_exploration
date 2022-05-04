#include "commandBuffer.h"
#include <vulkan/vulkan.h>
#include <assert.h>


void createCommandBuffer(VkCommandPool *commandPool, VkDevice *device, VkCommandBuffer *commandBuffer) {
    
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = *commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;
    
    assert((vkAllocateCommandBuffers(*device, &allocInfo, commandBuffer) == VK_SUCCESS) && "failed to allocate command buffers");
}
