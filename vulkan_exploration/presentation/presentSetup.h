#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// initializes the GLFW window
GLFWwindow *initWindow(void);

// keeps window open until window is closed
void mainLoop(GLFWwindow *window);

// destroys the Glfw instance
void glfwCleanup(GLFWwindow *window);
