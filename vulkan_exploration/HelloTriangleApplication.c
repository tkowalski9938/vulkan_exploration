#include "HelloTriangleApplication.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "presentation/presentSetup.h"
#include "presentation/surface.h"
#include "init/instance.h"
#include "init/physicalDevice.h"
#include "init/logicalDevice.h"
#include "presentation/swapChain.h"
#include "presentation/imageView.h"
#include "graphicsPipeline/graphicsPipeline.h"

GLFWwindow *window;

VkInstance instance;
VkPhysicalDevice physicalDevice;
VkDevice device;
VkQueue graphicsQueue;
VkSurfaceKHR surface;
VkQueue presentQueue;
VkSwapchainKHR swapChain;

// dynamically allocated, must be freed
VkImage *swapChainImages;
uint32_t numSwapChainImages;

VkFormat swapChainImageFormat;
VkExtent2D swapChainExtent;

// dynamically allocated, must be freed
VkImageView *swapChainImageViews;

VkPipelineLayout pipelineLayout;


// initializes Vulkan
static void initVulkan(GLFWwindow *window) {
    createInstance(&instance);
    createSurface(&instance, window, &surface);
    pickPhysicalDevice(&instance, &physicalDevice, surface);
    createLogicalDevice(&device, &physicalDevice, &graphicsQueue, surface, &presentQueue);
    createSwapChain(&physicalDevice, &surface, window, &swapChain, &device, &swapChainImages, &numSwapChainImages, &swapChainImageFormat, &swapChainExtent);
    createImageViews(&swapChainImageViews, swapChainImages, numSwapChainImages, swapChainImageFormat, &device);
    createGraphicsPipeline(&device, &swapChainExtent, &pipelineLayout);
}

// clears resources allocated
static void cleanup(GLFWwindow *window) {
    vkDestroyPipelineLayout(device, pipelineLayout, NULL);
    
    glfwCleanup(window);
    
    // destorys the individual VkImageViews
    freeImageView(swapChainImageViews, numSwapChainImages, &device);
    
    free(swapChainImages);
    
    
    free(swapChainImageViews);
    
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


