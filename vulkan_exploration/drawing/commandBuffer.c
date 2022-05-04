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

void recordCommandBuffer(VkCommandBuffer *commandBuffer, uint32_t imageIndex, VkFramebuffer *swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline *graphicsPipeline) {
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // optional
    beginInfo.pInheritanceInfo = NULL; // optional
    
    assert((vkBeginCommandBuffer(*commandBuffer, &beginInfo) == VK_SUCCESS) && "failed to begin recording command buffer");
    
    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
    
    renderPassInfo.renderArea.offset = (VkOffset2D){0,0};
    renderPassInfo.renderArea.extent = swapChainExtent;
    
    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    
    // starts the render pass
    vkCmdBeginRenderPass(*commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    
    //binds the graphics pipeline
    vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *graphicsPipeline);
    
    // draws the triangle
    vkCmdDraw(*commandBuffer, 3, 1, 0, 0);
    
    vkCmdEndRenderPass(*commandBuffer);
    
    assert((vkEndCommandBuffer(*commandBuffer) == VK_SUCCESS) && "failed to record command buffer");
}
