#include "physicalDevice.h"
#include "queue.h"
#include <vulkan/vulkan.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char *deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

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
    
            return supportsExtensions;
}

static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices = findQueueFamilies(device, surface);
    return isComplete(indices) && checkDeviceExtensionSupport(device);
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
