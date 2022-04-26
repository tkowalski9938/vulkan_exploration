#include "helloTriangleApplication.h"

// Activates GLFW preprocessor directive to also load Vulkan header
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

static GLFWwindow* window;
static VkInstance instance;

static const uint32_t WIDTH = 800;
static const uint32_t HEIGHT = 600;

static void initWindow(void) {
    // initializes the GLFW library
    glfwInit();
    
    // tells GLFW not to create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    // disables resizing windows
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    // create the window
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

static void createInstance(void) {
    // optional data that may provide useful information to the driver
    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    
    // mandatory data that tells Vulkan driver what global extensions and
    //      validation layers to use
    VkInstanceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    // Vulkan is platform agnostic, so need extension to interface with window
    //      system. Uses GLFW's built-in required extension finder.
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    createInfo.enabledLayerCount = 0;
    
    // creates the instance, stored outside of stack frame. checks if successful
    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        fprintf(stderr, "failed to create instance");
    }
}

static void initVulkan(void) {
    createInstance();
    
    // checks for extension support
    
}

static void mainLoop(void) {
    // keeps the application running until window closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

static void cleanup(void) {
    // destroys the Vulkan instance
    vkDestroyInstance(instance, NULL);
    
    // deallocates window memory
    glfwDestroyWindow(window);
    
    // terminates glfw
    glfwTerminate();
}

void run(void) {
    initVulkan();
    initWindow();
    mainLoop();
    cleanup();
}
