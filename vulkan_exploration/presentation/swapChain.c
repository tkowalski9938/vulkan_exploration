#include "swapChain.h"
#include "../init/queue.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

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
static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const VkSurfaceFormatKHR *availableFormats, const uint32_t numFormats) {
    // pick srgb if possible, otherwise pick first option
    for (int i = 0; i < numFormats; ++i) {
        if (availableFormats[i].format == VK_FORMAT_B8G8R8_SRGB && availableFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormats[i];
        }
    }
    return availableFormats[0];
}

// picks triple buffering if possible, otherwise standard vsync
static VkPresentModeKHR chooseSwapPresentMode(const VkPresentModeKHR *availablePresentModes, const uint32_t numPresentModes) {
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
static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR *capabilities, GLFWwindow *window) {
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

void createSwapChain(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface, GLFWwindow *window, VkSwapchainKHR *swapChain, VkDevice *device) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);
    
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats, swapChainSupport.numFormats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes, swapChainSupport.numPresentModes);
    VkExtent2D extent = chooseSwapExtent(&swapChainSupport.capabilities, window);
    
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    
    // makes sure we do not exceed max imageCount
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    
    VkSwapchainCreateInfoKHR createInfo = {};
    
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = *surface;
    
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    // always 1 unless developing 3D application
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    
    // handles swap chain images potentially across multiple queue families
    QueueFamilyIndices indices = findQueueFamilies(*physicalDevice, *surface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};
    // different queues families needed
    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        // optional
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = NULL;
    }
    
    // specifies no transformation
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    
    createInfo.presentMode = presentMode;
    
    // we don't care about the colour of obscured pixels
    createInfo.clipped = VK_TRUE;
    
    // note that resizing windows needs a recreation of the swapchain, but for simplicity, we assume it is static
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    
    assert((vkCreateSwapchainKHR(*device, &createInfo, NULL, swapChain) == VK_SUCCESS) && "failed to create swap chain");
    
    swapChainSupportDetailsDestory(swapChainSupport);
}
