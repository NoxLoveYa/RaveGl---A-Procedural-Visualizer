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
        GLfloat vertices[] = {
            // Positions         // Colors
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Top
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.1f, // Bottom Left
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.1f   // Bottom Right
        };

        Shaders shaders;
        GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
        shaders.createProgram(vertexShader, fragmentShader, "triangle");

        // Set up vertex data and buffers and configure vertex attributes
        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

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
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                Begin("Menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
                Text("Application average: (%.1f FPS)", io->Framerate);
                End();
            }

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // render triangle
            shaders.useProgram("triangle");
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SwapBuffers();
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}