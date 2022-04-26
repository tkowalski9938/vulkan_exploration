#include "window.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

void initWindow(void) {
    // initializes the GLFW library
    glfwInit();
    
    // tells GLFW not to create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    // disables resizing windows
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    // create the window
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

void mainLoop(void) {
    // keeps the application running until window closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}
