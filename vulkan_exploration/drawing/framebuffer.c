#include "framebuffer.h"
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <assert.h>
    

void destroyFramebuffers(VkDevice *device, VkFramebuffer *swapChainFrameBuffers, uint32_t numSwapChainImages) {
    for (int i = 0; i < numSwapChainImages; ++i) {
        vkDestroyFramebuffer(*device, swapChainFrameBuffers[i], NULL);
    }
    free(swapChainFrameBuffers);
}



// framebuffers is dynamically allocated and needs to be freed by the client
void createFramebuffers(VkDevice *device, VkFramebuffer **swapChainFramebuffers, uint32_t numSwapChainImages, VkImageView *swapChainImageViews, VkRenderPass *renderPass, VkExtent2D swapChainExtent) {
    *swapChainFramebuffers = malloc(numSwapChainImages * sizeof(VkFramebuffer));
    
    for (int i = 0; i < numSwapChainImages; ++i) {
        VkImageView attachments[] = {swapChainImageViews[i]};
        
        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = *renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;
        
        assert((vkCreateFramebuffer(*device, &framebufferInfo, NULL, &((*swapChainFramebuffers)[i])) == VK_SUCCESS) && "failed to create framebuffer");
    }
}
