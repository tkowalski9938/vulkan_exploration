#include "HelloTriangleApplication.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <assert.h>
#include "presentation/presentSetup.h"
#include "presentation/surface.h"
#include "init/instance.h"
#include "init/physicalDevice.h"
#include "init/logicalDevice.h"
#include "presentation/swapChain.h"
#include "presentation/imageView.h"
#include "graphicsPipeline/graphicsPipeline.h"
#include "graphicsPipeline/renderPass.h"
#include "drawing/framebuffer.h"
#include "drawing/commandPool.h"
#include "drawing/commandBuffer.h"

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

VkRenderPass renderPass;
VkPipelineLayout pipelineLayout;

VkPipeline graphicsPipeline;

// dynamically allocated, needs to be freed
VkFramebuffer *swapChainFramebuffers;
// the num of elements is the number of images in the swapchain

VkCommandPool commandPool;

VkCommandBuffer commandBuffer;

VkSemaphore imageAvailableSemaphore;
VkSemaphore renderFinishedSemaphore;
VkFence inFlightFence;

// creates the sync objects
static void createSyncObjects(void) {
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    
    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    // fence starts off in signaled state
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    
    assert((vkCreateSemaphore(device, &semaphoreInfo, NULL, &imageAvailableSemaphore) == VK_SUCCESS) && "failed to create imageAvailableSemaphore");
    assert((vkCreateSemaphore(device, &semaphoreInfo, NULL, &renderFinishedSemaphore) == VK_SUCCESS) && "failed to create renderFinishedSemaphore");
    assert((vkCreateFence(device, &fenceInfo, NULL, &inFlightFence) == VK_SUCCESS) && "failed to create inFlightFence");
}

// initializes Vulkan
static void initVulkan(GLFWwindow *window) {
    createInstance(&instance);
    createSurface(&instance, window, &surface);
    pickPhysicalDevice(&instance, &physicalDevice, surface);
    createLogicalDevice(&device, &physicalDevice, &graphicsQueue, surface, &presentQueue);
    createSwapChain(&physicalDevice, &surface, window, &swapChain, &device, &swapChainImages, &numSwapChainImages, &swapChainImageFormat, &swapChainExtent);
    createImageViews(&swapChainImageViews, swapChainImages, numSwapChainImages, swapChainImageFormat, &device);
    createRenderPass(&swapChainImageFormat, &renderPass, &device);
    createGraphicsPipeline(&device, &swapChainExtent, &pipelineLayout, &renderPass, &graphicsPipeline);
    createFramebuffers(&device, &swapChainFramebuffers, numSwapChainImages, swapChainImageViews, &renderPass, swapChainExtent);
    createCommandPool(&device, &physicalDevice, &surface, &commandPool);
    createCommandBuffer(&commandPool, &device, &commandBuffer);
    createSyncObjects();
}

// clears resources allocated
static void cleanup(GLFWwindow *window) {
    vkDestroySemaphore(device, imageAvailableSemaphore, NULL);
    vkDestroySemaphore(device, renderFinishedSemaphore, NULL);
    vkDestroyFence(device, inFlightFence, NULL);
    
    vkDestroyCommandPool(device, commandPool, NULL);
    
    destroyFramebuffers(&device, swapChainFramebuffers, numSwapChainImages);
    
    vkDestroyPipeline(device, graphicsPipeline, NULL);
    
    vkDestroyPipelineLayout(device, pipelineLayout, NULL);
    
    vkDestroyRenderPass(device, renderPass, NULL);
    
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
    mainLoop(window, &device, &inFlightFence, &swapChain, &imageAvailableSemaphore, &commandBuffer, swapChainFramebuffers, &swapChainExtent, &graphicsPipeline, &renderFinishedSemaphore, &graphicsQueue, &presentQueue, &renderPass);
    cleanup(window);
}


