/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_glfw.h"
#include "../../lib/imgui/imgui_impl_opengl3.h"

#include "../shaders/shaders.hpp"

namespace visualizer
{
    class Window
    {
    public:
        // Constructor / Destructor
        Window(int width, int height, const char *title);
        ~Window();
        // Operator
        operator GLFWwindow *() { return window; }
        // Getter
        GLFWwindow *GetWindow() { return window; }
        // Method
        bool ShouldClose() { return glfwWindowShouldClose(window); }
        void SwapBuffers() { glfwSwapBuffers(window); }
        void PollEvents() { glfwPollEvents(); }

        void ProcessInput();
        void update();
        // Callback
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
        {
            (void)window;
            glViewport(0, 0, width, height);
        }

    private:
        GLFWwindow *window;
        ImGuiIO *io;
        int width, height;
    };
}
