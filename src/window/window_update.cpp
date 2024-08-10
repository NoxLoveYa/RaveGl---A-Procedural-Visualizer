/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window_update
*/

#include "window.hpp"
#include "../src/primitives/cube.hpp"

namespace visualizer
{
    void Window::ProcessInput(GLFWwindow *window, MouseState &mouseState, Camera &camera)
    {
        //float cameraSpeed = 2.5f * deltaTime; use deltaTime for camera speed (UNCOMMENT)
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            camera.ProcessMouseScroll(1.0f); // Scroll up
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.ProcessMouseScroll(-1.0f); // Scroll down
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // W = move forward
            camera.ProcessKeyboard(FORWARD, _deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // S = move backward
            camera.ProcessKeyboard(BACKWARD, _deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // A = move left
            camera.ProcessKeyboard(LEFT, _deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // D = move right
            camera.ProcessKeyboard(RIGHT, _deltaTime);
        handleMouseDragging(window, mouseState, camera); // Handle mouse dragging
    }

    void Window::update()
    {
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
        MouseState mouseState;

        //cube coordinates are in /src/primitives/cube.hpp (TEMPORARY)

        Shaders shaders;
        GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
        shaders.createProgram(vertexShader, fragmentShader, "cube");

        // Set up vertex data and buffers and configure vertex attributes
        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        while (!ShouldClose())
        {
            _deltaTime = CalculateDeltaTime();
            // Poll and handle events (inputs, window resize, etc.)
            PollEvents();
            ProcessInput(window, mouseState, camera);

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // render primitives (Cubes in this case)
            shaders.useProgram("cube");

            // set up view and projection matrices
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
            shaders.setMat4("projection", projection);
            // camera/view transformation
            glm::mat4 view = camera.GetViewMatrix();
            shaders.setMat4("view", view);

            // render container
            glBindVertexArray(VAO);
            for (unsigned int i = 0; i < 10; i++) {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shaders.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            // Rendering ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SwapBuffers();
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}
