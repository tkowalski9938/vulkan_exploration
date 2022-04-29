#include "HelloTriangleApplication.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "presentation/presentSetup.h"
#include "presentation/surface.h"
#include "init/instance.h"
#include "init/physicalDevice.h"
#include "init/logicalDevice.h"
#include "presentation/swapChain.h"

GLFWwindow *window;

VkInstance instance;
VkPhysicalDevice physicalDevice;
VkDevice device;
VkQueue graphicsQueue;
VkSurfaceKHR surface;
VkQueue presentQueue;
VkSwapchainKHR swapChain;

// initializes Vulkan
static void initVulkan(GLFWwindow *window) {
    createInstance(&instance);
    createSurface(&instance, window, &surface);
    pickPhysicalDevice(&instance, &physicalDevice, surface);
    createLogicalDevice(&device, &physicalDevice, &graphicsQueue, surface, &presentQueue);
    createSwapChain(&physicalDevice, &surface, window, &swapChain, &device);
}

// clears resources allocated
static void cleanup(GLFWwindow *window) {
    glfwCleanup(window);
    
    
    vkDestroySwapchainKHR(device, swapChain, NULL);
    
    vkDestroySurfaceKHR(instance, surface, NULL);
    
    vkDestroyDevice(device, NULL);
    
    vkDestroyInstance(instance, NULL);
}

void run(void) {
    // note the pointer only has a defined value in the stack frame, so it must be passed as a parameter
    GLFWwindow *window = initWindow();
    
    initVulkan(window);
    mainLoop(window);
    cleanup(window);
}


