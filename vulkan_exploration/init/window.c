#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

static GLFWwindow *window;

static const uint32_t WIDTH = 800;
static const uint32_t HEIGHT = 600;

void initWindow(void) {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

void mainLoop(void) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void glfwCleanup(void) {
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

