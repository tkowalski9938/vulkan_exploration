#include "HelloTriangleApplication.h"
#include <vulkan/vulkan.h>
#include "init/window.h"
#include "init/instance.h"
#include "init/physicalDevice.h"
#include "init/logicalDevice.h"

VkInstance instance;
VkPhysicalDevice physicalDevice;
VkDevice device;
VkQueue graphicsQueue;

// initializes Vulkan
static void initVulkan(void) {
    createInstance(&instance);
    pickPhysicalDevice(&instance, &physicalDevice);
    createLogicalDevice(&device, &physicalDevice, &graphicsQueue);
}

// clears resources allocated
static void cleanup(void) {
    glfwCleanup();
    
    vkDestroyDevice(device, NULL);
    
    vkDestroyInstance(instance, NULL);
}

void run(void) {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}


