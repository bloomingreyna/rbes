#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

bool GraphicsInitialization() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(
        800, 600,
        "RBES",
        nullptr, nullptr
    );
    glfwMakeContextCurrent(window);

    if (!window) {
        return false;
    }
    return true;
}
