#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GLFW::Private {
void *getCocoaWindow(GLFWwindow *window);
}