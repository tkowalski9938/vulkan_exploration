#include "validation.h"
#include <vulkan/vulkan.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const char *validationLayers[] = {"VK_LAYER_KHRONOS_validation"};

const int numValidationLayers = 1;

// DISABLE during deployment
const bool enableValidationLayers = true;

// checks if all the requested layers are avaiable
bool checkValidationLayerSupport(void) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    
    VkLayerProperties *availableLayers = malloc(sizeof(VkLayerProperties) *
                                                layerCount);
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
