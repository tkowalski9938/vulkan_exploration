#include "HelloTriangleApplication.h"
#include <vulkan/vulkan.h>
#include "glfwFuncs/window.h"
#include "vulkan/instance.h"
#include "vulkan/physicalDevice.h"

VkInstance instance;
VkPhysicalDevice physicalDevice;

// initializes Vulkan
static void initVulkan(void) {
    createInstance(&instance);
    pickPhysicalDevice(&instance, &physicalDevice);
}

// clears resources allocated
static void cleanup(void) {
    glfwCleanup();
    
    vkDestroyInstance(instance, NULL);
}

void run(void) {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}


