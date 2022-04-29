#include "imageView.h"
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <assert.h>

void createImageViews(VkImageView **swapChainImageViews, VkImage *swapChainImages, uint32_t numSwapChainImages, VkFormat swapChainImageFormat, VkDevice *device) {
    
    *swapChainImageViews = malloc(numSwapChainImages * sizeof(VkImageView));
    for (int i = 0; i < numSwapChainImages; ++ i) {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];
        
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = swapChainImageFormat;
        
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        
        // subresourceRange describes image's purpose and which part should be accessed
        // images used as colour targets
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        
        assert((vkCreateImageView(*device, &createInfo, NULL, &(*swapChainImageViews)[i]) == VK_SUCCESS) && "failed to create image views!");
    }
}

void freeImageView(VkImageView *swapChainImageViews, uint32_t numSwapChainImages, VkDevice *device) {
    for (int i = 0; i < numSwapChainImages; ++i) {
        vkDestroyImageView(*device, swapChainImageViews[i], NULL);
    }
}
