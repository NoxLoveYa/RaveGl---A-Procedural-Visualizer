/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window_update
*/

#include "window.hpp"

namespace visualizer
{
    void Window::ProcessInput()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void Window::update()
    {
        while (!ShouldClose())
        {
            // Poll and handle events (inputs, window resize, etc.)
            PollEvents();
            ProcessInput();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Show menu etc
            {
                using namespace ImGui;
                Begin("Menu");
                Text("Hello, world! Application average: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
                End();
            }

            // Rendering
            ImGui::Render();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SwapBuffers();
        }
    }
}