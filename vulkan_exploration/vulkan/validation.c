#include "validation.h"
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// SET FALSE BEFORE DEPLOYMENT
const bool enableValidationLayers = true;

static const char *validationLayers[] = { "VK_LAYER_KHRONOS_validation"
};

static const int numValidationLayers = 1;

bool checkValidationLayerSupport(void) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    
    VkLayerProperties *availableLayers = malloc(layerCount * sizeof(VkLayerProperties));
    
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);
    
    for (int i = 0; i < numValidationLayers; ++i) {
        bool layerFound = false;
        for (int k = 0; k < layerCount; ++k) {
            if (strcmp(validationLayers[i], availableLayers[k].layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            free(availableLayers);
            return false;
        }
    }
    free(availableLayers);
    return true;
}
