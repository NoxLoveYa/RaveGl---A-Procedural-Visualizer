/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window
*/

#include "window.hpp"

namespace visualizer
{
    Window::Window(int width, int height, const char *title)
        : width(width), height(height)
    {
        // Initialize GLFW
        if (!glfwInit())
            exit(84);

        // Set OpenGL version to 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        // Set OpenGL profile to core
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Create window
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(84);
        }
        // Set window to current context
        glfwMakeContextCurrent(window);

        // Set framebuffer size callback
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Load OpenGL functions
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            exit(84);
        }

        // Set viewport
        glViewport(0, 0, width, height);
    }

    Window::~Window()
    {
        glfwTerminate();
    }
}
