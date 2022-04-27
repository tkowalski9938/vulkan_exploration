#include "logicalDevice.h"
#include "queue.h"
#include "validation.h"
#include <vulkan/vulkan.h>
#include <assert.h>

void createLogicalDevice(VkDevice *device, VkPhysicalDevice *physicalDevice, VkQueue *graphicsQueue) {
    QueueFamilyIndices indices = findQueueFamilies(*physicalDevice);
    
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
    queueCreateInfo.queueCount = 1;
    
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    
    // not sure how to efficiently initialize this to all VK_FALSE
    VkPhysicalDeviceFeatures deviceFeatures = {};
    vkGetPhysicalDeviceFeatures(*physicalDevice, &deviceFeatures);
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    
    createInfo.pEnabledFeatures = &deviceFeatures;
    
    createInfo.enabledExtensionCount = 0;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = numValidationLayers;
        createInfo.ppEnabledLayerNames = validationLayers;
    }
    else {
        createInfo.enabledLayerCount = 0;
    }
    
    assert((vkCreateDevice(*physicalDevice, &createInfo, NULL, device) == VK_SUCCESS)&& "failed to create logical device");
    
    vkGetDeviceQueue(*device, indices.graphicsFamily, 0, graphicsQueue);
}
