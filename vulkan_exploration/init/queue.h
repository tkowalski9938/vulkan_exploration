#include <vulkan/vulkan.h>
#include <stdbool.h>
#include <stdint.h>

struct QueueFamilyIndices {
    uint32_t graphicsFamily;
    bool graphicsFamilyFound;
};

typedef struct QueueFamilyIndices QueueFamilyIndices;

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

bool isComplete(struct QueueFamilyIndices indices);
