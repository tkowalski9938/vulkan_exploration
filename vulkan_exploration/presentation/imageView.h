#include <vulkan/vulkan.h>

void createImageViews(VkImageView **swapChainImageViews, VkImage *swapChainImages, uint32_t numSwapChainImages, VkFormat swapChainImageFormat, VkDevice *device);

void freeImageView(VkImageView *imageView, uint32_t numSwapChainImages, VkDevice *device);
