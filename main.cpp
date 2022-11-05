// Metal
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "Metal.hpp"
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

int gl_init(int argc, char *argv[], const char *title, int width, int height,
            bool fullScreen, GLFWwindow **outWindow) {
  (*outWindow) = NULL;
  if (!glfwInit())
    return -1;
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  // create window
  GLFWwindow *window = NULL;
  if (fullScreen) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
  } else {
    glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
  }
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetTime(0.0);
  glfwSwapInterval(1);
  (*outWindow) = window;
  return 0;
}

int main(int argc, char *argv[]) {
  GLFWwindow *window;
  int status = gl_init(argc, argv, "Sample", 1280, 720, false, &window);
  if (status != 0) {
    return status;
  }

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}