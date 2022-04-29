#include <vulkan/vulkan.h>

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

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice *device, VkSurfaceKHR *surface);


