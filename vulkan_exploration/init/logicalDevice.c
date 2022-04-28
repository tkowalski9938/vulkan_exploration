#include "logicalDevice.h"
#include "queue.h"
#include "validation.h"
#include <vulkan/vulkan.h>
#include <assert.h>
#include <stdlib.h>

//static const char *enabledExtensions[] = {"VK_KHR_portability_subset"};

void createLogicalDevice(VkDevice *device, VkPhysicalDevice *physicalDevice, VkQueue *graphicsQueue, VkSurfaceKHR surface, VkQueue *presentQueue) {
    QueueFamilyIndices indices = findQueueFamilies(*physicalDevice, surface);
    
    float queuePriority = 1.0f;
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    
    //my set implementation [assuming 2 required queues]
    VkDeviceQueueCreateInfo *queueCreateInfos = malloc(indices.numFamiliesReq * sizeof(VkDeviceQueueCreateInfo));
    
    if (indices.graphicsFamily == indices.presentFamily) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
    }
    else {
        
        VkDeviceQueueCreateInfo graphicsQueueCreateInfo = {};
        graphicsQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        graphicsQueueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
        graphicsQueueCreateInfo.queueCount = 1;
        graphicsQueueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos[0] = graphicsQueueCreateInfo;
        
        VkDeviceQueueCreateInfo presentQueueCreateInfo = {};
        presentQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        presentQueueCreateInfo.queueFamilyIndex = indices.presentFamily;
        presentQueueCreateInfo.queueCount = 1;
        presentQueueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos[1] = presentQueueCreateInfo;
        
        createInfo.pQueueCreateInfos = queueCreateInfos;
        createInfo.queueCreateInfoCount = indices.numFamiliesReq;
    }
    
    /*
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
    queueCreateInfo.queueCount = 1;
    */
    
    //queueCreateInfo.pQueuePriorities = &queuePriority;
    
    
    VkPhysicalDeviceFeatures deviceFeatures = {};

    vkGetPhysicalDeviceFeatures(*physicalDevice, &deviceFeatures);
    
    /*
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
     */
    
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;
    
    //createInfo.ppEnabledExtensionNames = enabledExtensions;
    
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = numValidationLayers;
        createInfo.ppEnabledLayerNames = validationLayers;
    }
    else {
        createInfo.enabledLayerCount = 0;
    }
    
    assert((vkCreateDevice(*physicalDevice, &createInfo, NULL, device) == VK_SUCCESS)&& "failed to create logical device");
    
    vkGetDeviceQueue(*device, indices.graphicsFamily, 0, graphicsQueue);
    vkGetDeviceQueue(*device, indices.presentFamily, 0, presentQueue);
    
    free(queueCreateInfos);
}
