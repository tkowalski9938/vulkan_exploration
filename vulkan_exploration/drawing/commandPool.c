#include "commandPool.h"
#include <vulkan/vulkan.h>
#include "../init/queue.h"
#include <assert.h>

void createCommandPool(VkDevice *device, VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface, VkCommandPool *commandPool) {
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(*physicalDevice, *surface);
    
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
    
    assert((vkCreateCommandPool(*device, &poolInfo, NULL, commandPool) == VK_SUCCESS) && "failed to create command pool");
}
