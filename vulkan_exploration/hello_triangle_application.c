#include "hello_triangle_application.h"

// Activates GLFW preprocessor directive to also load Vulkan header
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdlib.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

static GLFWwindow* initWindow(void) {
    // initializes the GLFW library
    glfwInit();
    
    // tells GLFW not to create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    // disables resizing windows
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    // create the window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
    
    return window;
}

static void initVulkan(void) {
    
}

static void mainLoop(GLFWwindow *window) {
    // keeps the application running until window closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

static void cleanup(GLFWwindow *window) {
    // deallocates window memory
    glfwDestroyWindow(window);
    
    // terminates glfw
    glfwTerminate();
}

void run(void) {
    GLFWwindow* window = initWindow();
    initVulkan();
    mainLoop(window);
    cleanup(window);
}
