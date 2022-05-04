#include "presentSetup.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../drawing/drawFrame.h"


static const uint32_t WIDTH = 800;
static const uint32_t HEIGHT = 600;

GLFWwindow *initWindow(void) {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tyler's Hello Triangle in Vulkan", NULL, NULL);
    
    return window;
}
 

void mainLoop(GLFWwindow *window, VkDevice *device, VkFence *inFlightFence, VkSwapchainKHR *swapchain, VkSemaphore *imageAvailableSemaphore, VkCommandBuffer *commandBuffer, VkFramebuffer *swapChainFramebuffers, VkExtent2D *swapChainExtent, VkPipeline *graphicsPipeline, VkSemaphore *renderFinishedSemaphore, VkQueue *graphicsQueue, VkQueue *presentQueue, VkRenderPass *renderPass) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame(device, inFlightFence, swapchain, imageAvailableSemaphore, commandBuffer, swapChainFramebuffers, swapChainExtent, graphicsPipeline, renderFinishedSemaphore, graphicsQueue, presentQueue, renderPass);
    }
    
    vkDeviceWaitIdle(*device);
}

void glfwCleanup(GLFWwindow *window) {
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

