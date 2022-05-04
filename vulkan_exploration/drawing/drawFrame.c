#include "drawFrame.h"
#include <vulkan/vulkan.h>
#include "commandBuffer.h"
#include <assert.h>

void drawFrame(VkDevice *device, VkFence *inFlightFence, VkSwapchainKHR *swapchain, VkSemaphore *imageAvailableSemaphore, VkCommandBuffer *commandBuffer, VkFramebuffer *swapChainFramebuffers, VkExtent2D *swapChainExtent, VkPipeline *graphicsPipeline, VkSemaphore *renderFinishedSemaphore, VkQueue *graphicsQueue, VkQueue *presentQueue, VkRenderPass *renderPass) {
    
    // CPU execution waits for previous frame to finish
    vkWaitForFences(*device, 1, inFlightFence, VK_TRUE, UINT64_MAX);
    
    // fence needs to be manually reset to the unsignaled state
    vkResetFences(*device, 1, inFlightFence);
    
    //acquire an image from the swap chain
    uint32_t imageIndex;
    vkAcquireNextImageKHR(*device, *swapchain, UINT64_MAX, *imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
    
    // records the command buffer
    vkResetCommandBuffer(*commandBuffer, 0);
    
    recordCommandBuffer(commandBuffer, imageIndex, swapChainFramebuffers, *swapChainExtent, graphicsPipeline, renderPass);
    
    // submitting the command buffer
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    
    VkSemaphore waitSemaphores[] = {*imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = commandBuffer;
    
    VkSemaphore signalSemaphores[] = {*renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;
    
    assert((vkQueueSubmit(*graphicsQueue, 1, &submitInfo, *inFlightFence) == VK_SUCCESS) && "failed to submit draw command buffer");
    
    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    
    VkSwapchainKHR swapChains[] = {*swapchain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    
    vkQueuePresentKHR(*presentQueue, &presentInfo);
}
