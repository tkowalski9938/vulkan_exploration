#include <vulkan/vulkan.h>
#include <stdbool.h>
#include <stdint.h>

struct QueueFamilyIndices {
    uint32_t graphicsFamily;
    bool graphicsFamilyFound;
    uint32_t presentFamily;
    bool presentFamilyFound;
};

typedef struct QueueFamilyIndices QueueFamilyIndices;

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

bool isComplete(struct QueueFamilyIndices indices);
