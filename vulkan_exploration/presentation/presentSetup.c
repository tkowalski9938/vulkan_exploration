#include "presentSetup.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


static const uint32_t WIDTH = 800;
static const uint32_t HEIGHT = 600;

GLFWwindow *initWindow(void) {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
    
    return window;
}
 

void mainLoop(GLFWwindow *window) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void glfwCleanup(GLFWwindow *window) {
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

