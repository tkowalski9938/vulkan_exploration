#include "helloTriangleApplication.h"

// Activates GLFW preprocessor directive to also load Vulkan header
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

static GLFWwindow* window;
static VkInstance instance;
static VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;


static const uint32_t WIDTH = 800;
static const uint32_t HEIGHT = 600;

const char *validationLayers[] = {"VK_LAYER_KHRONOS_validation"};
const int numValidationLayers = 1;

// DISABLE during deployment
const bool enableValidationLayers = true;

// checks if all the requested layers are avaiable
static bool checkValidationLayerSupport(void) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    
    VkLayerProperties *availableLayers = malloc(sizeof(VkLayerProperties) *
                                                layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);
    
    
    for (int i = 0; i < numValidationLayers; ++i) {
        bool layerFound = false;
        for (int k = 0; k < layerCount; ++k) {
            if (strcmp(validationLayers[i], availableLayers[k].layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            free(availableLayers);
            return false;
        }
    }
    free(availableLayers);
    return true;
}

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
    // checks for extension support
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
    
    VkExtensionProperties *pExtensions = malloc(extensionCount * sizeof(VkExtensionProperties));
    
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, pExtensions);
    
    printf("avaible extensions:\n");
    for (int i = 0; i < extensionCount; ++i) {
        printf("\t%s\n", pExtensions[i * sizeof(VkExtensionProperties)].extensionName);
    }
    free(pExtensions);
    
    // checks if all validationLayers exist in availableLayers
    assert((!enableValidationLayers || checkValidationLayerSupport()) &&
           "validation layers requested, but not available");
    
    
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
    
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = numValidationLayers;
        createInfo.ppEnabledLayerNames = validationLayers;
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    // creates the instance, stored outside of stack frame. checks if successful
    assert((vkCreateInstance(&createInfo, NULL, &instance) == VK_SUCCESS) &&
           "failed to create instance");
}

static bool isDeviceSuitable(VkPhysicalDevice device) {
    return true;
}

static void getPhysicalDeviceProperties(void) {
    VkPhysicalDeviceProperties *properties = malloc(sizeof(VkPhysicalDeviceProperties));
    
    vkGetPhysicalDeviceProperties(physicalDevice, properties);
    
    printf("\n%s\n", properties->deviceName);
    free(properties);
}
static void pickPhysicalDevice(void) {
    
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
    
    assert(deviceCount > 0 && "failed to find GPUs with Vulkan support");
    
    VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
    
    for (int i = 0; i < deviceCount; ++i) {
        if (isDeviceSuitable(devices[i])) {
            physicalDevice = devices[i];
            break;
        }
    }
    free(devices);
    assert(physicalDevice != VK_NULL_HANDLE && "failed to find suitable GPU");
}

static void initVulkan(void) {
    createInstance();
    pickPhysicalDevice();
    getPhysicalDeviceProperties();
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
