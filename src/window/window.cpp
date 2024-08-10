/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window
*/

#include "window.hpp"
#include "window_style.hpp"

ImGuiIO *setupImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    StyleColorsCustom();
    return &io;
}

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
        glfwWindowHint(GLFW_ALPHA_BITS, 8);  // For GLFW transparent window
        // Create window
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(84);
        }
        // Set window to current context
        glfwMakeContextCurrent(window);

        // Initialize ImGui
        io = setupImGui();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        // Set framebuffer size callback
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Load OpenGL functions
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            exit(84);
        }

        // Enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set viewport
        glViewport(0, 0, width, height);
    }

    Window::~Window()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}
