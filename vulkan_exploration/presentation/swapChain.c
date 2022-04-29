#include "swapChain.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <limits.h>

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

// picks a VkSurfaceFormatKHR
VkSurfaceFormatKHR chooseSwapSurfaceFormat(const VkSurfaceFormatKHR *availableFormats, const uint32_t numFormats) {
    // pick srgb if possible, otherwise pick first option
    for (int i = 0; i < numFormats; ++i) {
        if (availableFormats[i].format == VK_FORMAT_B8G8R8_SRGB && availableFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormats[i];
        }
    }
    return availableFormats[0];
}

// picks triple buffering if possible, otherwise standard vsync
VkPresentModeKHR chooseSwapPresentMode(const VkPresentModeKHR *availablePresentModes, const uint32_t numPresentModes) {
    for (int i = 0; i < numPresentModes; ++i) {
        if (availablePresentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentModes[i];
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

static uint32_t myClamp(uint32_t x, uint32_t min, uint32_t max) {
    if ((x >= min) && (x <= max)) {
        return x;
    }
    else if (x < min) {
        return min;
    }
    else {
        return max;
    }
}


// chooses the resolution of the swap chain images
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR *capabilities, GLFWwindow *window) {
    if (capabilities->currentExtent.width != UINT32_MAX) {
        return capabilities->currentExtent;
    }
    // note if set to max, window manager allows us to pick resolution
    else {
        int width;
        int height;
        glfwGetFramebufferSize(window, &width, &height);
        
        uint32_t uWidth = width;
        uint32_t uHeight = height;
        
        VkExtent2D actualExtent;
        actualExtent.width = myClamp(uWidth, capabilities->minImageExtent.width, capabilities->maxImageExtent.width);
        actualExtent.height = myClamp(uHeight, capabilities->minImageExtent.height, capabilities->maxImageExtent.height);
        
        return actualExtent;
    }
}
