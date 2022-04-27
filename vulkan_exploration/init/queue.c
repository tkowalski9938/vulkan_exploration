#include <vulkan/vulkan.h>
#include "queue.h"
#include <stdlib.h>

bool isComplete(struct QueueFamilyIndices indices) {
    if (indices.graphicsFamilyFound && indices.presentFamilyFound) {
        return true;
    }
    else {
        return false;
    }
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices = {};
    indices.graphicsFamilyFound = false;
    indices.presentFamilyFound = false;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);
    VkQueueFamilyProperties *queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);
    
    for (int i = 0; i < queueFamilyCount; ++i) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
            indices.graphicsFamilyFound = true;
        }
        if(presentSupport) {
            indices.presentFamily = i;
            indices.presentFamilyFound = true;
        }
        if (isComplete(indices)) {
            break;
        }
    }
    free(queueFamilies);
    return indices;
}
