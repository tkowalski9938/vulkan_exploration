#include "surface.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <assert.h>

void createSurface(VkInstance *instance, GLFWwindow *window, VkSurfaceKHR *surface) {
    assert((glfwCreateWindowSurface(*instance, window, NULL, surface) == VK_SUCCESS) && "failed to create window surface");
}
