#include <vulkan/vulkan.h>

void drawFrame(VkDevice *device, VkFence *inFlightFence, VkSwapchainKHR *swapchain, VkSemaphore *imageAvailableSemaphore, VkCommandBuffer *commandBuffer, VkFramebuffer *swapChainFramebuffers, VkExtent2D *swapChainExtent, VkPipeline *graphicsPipeline, VkSemaphore *renderFinishedSemaphore, VkQueue *graphicsQueue, VkQueue *presentQueue, VkRenderPass *renderPass);
