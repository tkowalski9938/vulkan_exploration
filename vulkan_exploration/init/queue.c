#include <vulkan/vulkan.h>
#include "queue.h"
#include <stdlib.h>

bool isComplete(struct QueueFamilyIndices indices) {
    if (indices.graphicsFamilyFound) {
        return true;
    }
    else {
        return false;
    }
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices = {};
    indices.graphicsFamilyFound = false;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);
    VkQueueFamilyProperties *queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);
    
    for (int i = 0; i < queueFamilyCount; ++i) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
            indices.graphicsFamilyFound = true;
        }
        if (isComplete(indices)) {
            break;
        }
    }
    free(queueFamilies);
    return indices;
}
