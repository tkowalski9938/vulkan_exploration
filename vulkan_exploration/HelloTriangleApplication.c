#include "HelloTriangleApplication.h"
#include <vulkan/vulkan.h>
#include "init/window.h"
#include "init/instance.h"
#include "init/physicalDevice.h"

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


