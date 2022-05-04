#include <vulkan/vulkan.h>

void destroyFramebuffers(VkDevice *device, VkFramebuffer *swapChainFrameBuffers, uint32_t numSwapChainImages);

void createFramebuffers(VkDevice *device, VkFramebuffer **swapChainFramebuffers, uint32_t numSwapChainImages, VkImageView *swapChainImageViews, VkRenderPass *renderPass, VkExtent2D swapChainExtent);
