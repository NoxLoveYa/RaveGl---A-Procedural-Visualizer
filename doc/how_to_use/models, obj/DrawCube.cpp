/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** DrawCube.cpp
*/

//drawing 10 cubes at random positions using vertices
//#include "cube.hpp"

/* Window::update() {
        Shaders shaders;
        GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
        shaders.createProgram(vertexShader, fragmentShader, "cube");
        //cube_vertices is in include/primitives/cube.hpp
        VertexArray cubeVAO(cube_vertices, sizeof(cube_vertices));
        cubeVAO.bindAndUnbind();

        while (!Close) {
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            shaders.useProgram("cube");

            // set up view and projection matrices
            shaders.setMat4("projection", projection);
            shaders.setMat4("view", view);

            // // render container
            cubeVAO.bind();
            glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, modelPosition);
            shaders.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            for (unsigned int i = 0; i < 10; i++) {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shaders.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            // }
        }
        cubeVAO.deleteBuffers(); // acts like the destructor
    }
*/