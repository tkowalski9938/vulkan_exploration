#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


// initializes the GLFW window
GLFWwindow *initWindow(void);


// keeps window open until window is closed
void mainLoop(GLFWwindow *window, VkDevice *device, VkFence *inFlightFence, VkSwapchainKHR *swapchain, VkSemaphore *imageAvailableSemaphore, VkCommandBuffer *commandBuffer, VkFramebuffer *swapChainFramebuffers, VkExtent2D *swapChainExtent, VkPipeline *graphicsPipeline, VkSemaphore *renderFinishedSemaphore, VkQueue *graphicsQueue, VkQueue *presentQueue, VkRenderPass *renderPass);

// destroys the Glfw instance
void glfwCleanup(GLFWwindow *window);
