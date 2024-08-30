/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window
*/

#pragma once

#include <cstdlib>
#include <iostream>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_glfw.h"
#include "../../lib/imgui/imgui_impl_opengl3.h"

#include "../shaders/shaders.hpp"
#include "../camera/camera.hpp"
#include "../render/VertexArray.hpp"

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

        void ProcessInput(GLFWwindow *window, MouseState &mouseState, Camera &camera);
        void update();
        // Callback
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
        {
            (void)window;
            glViewport(0, 0, width, height);
        }
        //deltaTime
        float CalculateDeltaTime() {
            float currentFrame = static_cast<float>(glfwGetTime());
            _deltaTime = currentFrame - _lastFrame;
            _lastFrame = currentFrame;
            return _deltaTime;
        }
        float GetDeltaTime() { return _deltaTime; }

    private:
        GLFWwindow *window;
        ImGuiIO *io;
        int width, height;
        float _deltaTime = 0.0f;
        float _lastFrame = 0.0f;
    };
}
