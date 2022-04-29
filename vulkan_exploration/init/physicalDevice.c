#include "physicalDevice.h"
#include "queue.h"
#include "../presentation/swapChain.h"
#include <vulkan/vulkan.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


const char *deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const uint32_t numDeviceExtensions = 1;

static bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    bool supportsExtensions = false;
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);
    
    VkExtensionProperties *availableExtensions = malloc(extensionCount * sizeof(VkExtensionProperties));
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions);
    
    // note this assumes only one extension is required
    for (int i = 0; i < extensionCount; ++i) {
        if (strcmp(availableExtensions[i].extensionName, deviceExtensions)) {
            supportsExtensions = true;
            break;
        }
    }
    free(availableExtensions);
            return supportsExtensions;
}

static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices = findQueueFamilies(device, surface);
    
    // checks for swapchain support
    bool swapChainAdequate = false;
    if (checkDeviceExtensionSupport(device)) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(&device, &surface);
        swapChainAdequate = (swapChainSupport.numFormats != 0) && (swapChainSupport.numPresentModes != 0);
    }
    
    return isComplete(indices) && checkDeviceExtensionSupport(device) && swapChainAdequate;
}

void pickPhysicalDevice(VkInstance *instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR surface) {

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(*instance, &deviceCount, NULL);
    
    assert(deviceCount > 0 && "failed to find GPUs with Vulkan support");
    
    VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(*instance, &deviceCount, devices);
    
    bool foundSuitableDevice = false;
    for (int i = 0; i < deviceCount; ++i) {
        if (isDeviceSuitable(devices[i], surface)) {
            *physicalDevice = devices[i];
            foundSuitableDevice = true;
            break;
        }
    }
    free(devices);
    assert(foundSuitableDevice && "failed to find suitable GPU");
}
