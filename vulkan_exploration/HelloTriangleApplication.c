#include "HelloTriangleApplication.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "presentation/presentSetup.h"
#include "init/instance.h"
#include "init/physicalDevice.h"
#include "init/logicalDevice.h"

GLFWwindow *window;

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
    glfwCleanup(window);
    
    vkDestroyDevice(device, NULL);
    
    vkDestroyInstance(instance, NULL);
}

void run(void) {
    GLFWwindow *window = initWindow();
    initVulkan();
    mainLoop(window);
    cleanup();
}


