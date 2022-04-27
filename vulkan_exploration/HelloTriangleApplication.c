#include "HelloTriangleApplication.h"
#include <vulkan/vulkan.h>
#include "glfwFuncs/window.h"
#include "vulkan/instance.h"

VkInstance instance;

// initializes Vulkan
static void initVulkan(void) {
    createInstance(&instance);
}

// clears resources allocated
static void cleanup(void) {
    glfwCleanup();
}

void run(void) {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}


