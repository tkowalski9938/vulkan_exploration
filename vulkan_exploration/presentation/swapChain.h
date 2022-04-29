#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    VkSurfaceFormatKHR *formats;
    uint32_t numFormats;
    VkPresentModeKHR *presentModes;
    uint32_t numPresentModes;
};

typedef struct SwapChainSupportDetails SwapChainSupportDetails;

// clears memory from dynamically allocated arrays in struct
void swapChainSupportDetailsDestory(SwapChainSupportDetails details);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface);

void createSwapChain(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface, GLFWwindow *window, VkSwapchainKHR *swapChain, VkDevice *device, VkImage **swapChainImages, uint32_t *numSwapChainImages, VkFormat *swapChainImageFormat, VkExtent2D *swapChainExtent);
