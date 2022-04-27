#include "physicalDevice.h"
#include "queue.h"
#include <vulkan/vulkan.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);
    return isComplete(indices);
}

void pickPhysicalDevice(VkInstance *instance, VkPhysicalDevice *physicalDevice) {

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(*instance, &deviceCount, NULL);
    
    assert(deviceCount > 0 && "failed to find GPUs with Vulkan support");
    
    VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(*instance, &deviceCount, devices);
    
    bool foundSuitableDevice = false;
    for (int i = 0; i < deviceCount; ++i) {
        if (isDeviceSuitable(devices[i])) {
            *physicalDevice = devices[i];
            foundSuitableDevice = true;
            break;
        }
    }
    free(devices);
    assert(foundSuitableDevice && "failed to find suitable GPU");
}
