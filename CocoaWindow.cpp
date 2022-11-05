#include "CocoaWindow.hpp"
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

namespace GLFW::Private {
void *getCocoaWindow(GLFWwindow *window) { return glfwGetCocoaWindow(window); }
} // namespace GLFW::Private