#include <vulkan/vulkan.h>

void createCommandBuffer(VkCommandPool *commandPool, VkDevice *device, VkCommandBuffer *commandBuffer);

void recordCommandBuffer(VkCommandBuffer *commandBuffer, uint32_t imageIndex, VkFramebuffer *swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline *graphicsPipeline);
