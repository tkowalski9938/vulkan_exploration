#include "helloTriangleApplication.h"
#include "validation.h"
#include "window.h"

// Activates GLFW preprocessor directive to also load Vulkan header
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

static VkInstance instance;

static VkPhysicalDevice physicalDevice;





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




// checks if devices has queue family that supports VK_QUEUE_GRAPHICS_BIT
struct QueueFamilyIndices{
    uint32_t graphicsFamily;
    bool graphicsFamilyFound;
};
typedef struct QueueFamilyIndices QueueFamilyIndices;

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    indices.graphicsFamilyFound = false;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);
    VkQueueFamilyProperties *queueFamilies = malloc(sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);
    
    for (int i = 0; i < queueFamilyCount; ++i) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
            indices.graphicsFamilyFound = true;
            break;
        }
    }
    assert(indices.graphicsFamilyFound && "missing needed queue family");
    return indices;
}


static bool isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);
    
    return indices.graphicsFamilyFound;
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
