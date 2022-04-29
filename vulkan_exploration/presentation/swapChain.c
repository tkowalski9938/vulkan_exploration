#include "swapChain.h"
#include <vulkan/vulkan.h>
#include <stdlib.h>

// clears memory from dynamically allocated arrays in struct
void swapChainSupportDetailsDestory(SwapChainSupportDetails details) {
    free(details.formats);
    free(details.presentModes);
}

// returns struct SwapChainSupportDetails
// requires: client must call swapChainSupportDetails destory
SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice *device, VkSurfaceKHR *surface) {
    SwapChainSupportDetails details;
    
    // adds capabilities details
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*device, *surface, &details.capabilities);
    
    // adds supported format details
    vkGetPhysicalDeviceSurfaceFormatsKHR(*device, *surface, &details.numFormats, NULL);
    details.formats = malloc(details.numFormats * sizeof(VkSurfaceFormatKHR));
    vkGetPhysicalDeviceSurfaceFormatsKHR(*device, *surface, &details.numFormats, details.formats);
    
    // adds supported present modes details
    vkGetPhysicalDeviceSurfacePresentModesKHR(*device, *surface, &details.numPresentModes, NULL);
    details.presentModes = malloc(details.numPresentModes * sizeof(VkPresentModeKHR));
    vkGetPhysicalDeviceSurfacePresentModesKHR(*device, *surface, &details.numPresentModes, details.presentModes);
    
    return details;
}


