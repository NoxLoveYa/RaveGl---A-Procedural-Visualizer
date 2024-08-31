/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window_update
*/

#include "window.hpp"
#include "cube.hpp"
#include "primitive_generator.hpp"
#include "random_primitive.hpp"
#include "Model.hpp"

std::unordered_map<std::string, std::shared_ptr<Model>> processAllModels(const std::string& directoryPath)
{
    std::unordered_map<std::string, std::shared_ptr<Model>> models;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".obj") {
            std::string objPath = entry.path().string();
            std::filesystem::path binPath = entry.path();
            binPath.replace_extension(".bin");
            std::string modelName = entry.path().stem().string(); // Get the file name without extension

            auto model = std::make_shared<Model>();
            if (std::filesystem::exists(binPath)) {
                if (model->loadProcessedData(binPath.string())) {
                    std::cout << "Loaded processed model: " << modelName << std::endl;
                    std::cout << "Number of vertices: " << model->getNumVertices() << std::endl;
                    std::cout << "Number of faces: " << model->getNumFaces() << std::endl;
                } else {
                    std::cerr << "Failed to load processed model: " << modelName << std::endl;
                }
            } else {
                model->parseModel(objPath);
                model->saveProcessedData(binPath.string());
                std::cout << "Processed and saved model: " << modelName << std::endl;
            }

            models[modelName] = model;

            std::cout << "Processed model: " << modelName << std::endl;
        }
    }
    return models;
}

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
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)// W = move forward
            camera.ProcessKeyboard(FORWARD, _deltaTime * 10);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // S = move backward
            camera.ProcessKeyboard(BACKWARD, _deltaTime * 10);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // A = move left
            camera.ProcessKeyboard(LEFT, _deltaTime * 5);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // D = move right
            camera.ProcessKeyboard(RIGHT, _deltaTime * 5);
        handleMouseDragging(window, mouseState, camera); // Handle mouse dragging
    }

    void Window::update()
    {
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
        MouseState mouseState;
        int numVertices = 128;
        int numPositions = 10;
        PrimitiveGenerator theShapes("", numVertices, numPositions, "src/primitives/random_primitive.hpp");
        std::vector<float> vertices = theShapes.getVertices();
        std::vector<glm::vec3> randomPositions = theShapes.getPositions();
        //cube coordinates are in /src/primitives/cube.hpp (TEMPORARY)

        std::shared_ptr<Shaders> shaders = std::make_shared<Shaders>();
        GLuint vertexShader = shaders->compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint fragmentShader = shaders->compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
        //shaders->createProgram(vertexShader, fragmentShader, "cube");
        //shaders.createProgram(vertexShader, fragmentShader, theShapes.getPrimitiveName().c_str());

        // spawn at will

        GLuint torusVertexShader = shaders->compileShaderFromFile("src/shaders/glsl/torus_vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint torusFragmentShader = shaders->compileShaderFromFile("src/shaders/glsl/torus_fragment_shader.glsl", GL_FRAGMENT_SHADER);
        shaders->createProgram(vertexShader, fragmentShader, "generic_complex_obj");

        std::unordered_map<std::string, std::shared_ptr<Model>> models = processAllModels("src/primitives/obj");
        // for (auto& [modelName, model] : models) {
        //     shaders->createProgram(vertexShader, fragmentShader, modelName.c_str());
        //     std::cout << "Using model: " << modelName << std::endl;
        //     std::cout << "gimme that !" << model->getNumVertices() << std::endl;
        // }


        //load object Model
        //Model complexTorus("src/primitives/obj/complex_torus.obj");

        // Light and material properties
        glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 objectColor(1.0f, 1.0f, 1.0f); // Set object color to white

        while (!ShouldClose())
        {
            _deltaTime = CalculateDeltaTime();
            // Poll and handle events (inputs, window resize, etc.)
            PollEvents();
            ProcessInput(window, mouseState, camera);
            // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
            // glm::mat4 view = camera.GetViewMatrix();
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

            shaders->useProgram("generic_complex_obj");
            for (auto& [modelName, model] : models) {
                //Apply transformations and other operations to the model
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
                glm::mat4 view = camera.GetViewMatrix();
                // Light and material properties
                glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
                glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

                // Example of applying transformations to the model
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
                //continous rotation
                float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
                modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

                // Set the shader uniforms
                shaders->setMat4("model", modelMatrix);
                shaders->setMat4("view", view);
                shaders->setMat4("projection", projection);
                shaders->setVec3("lightPos", lightPos);
                shaders->setVec3("viewPos", camera.Position);
                shaders->setVec3("lightColor", lightColor);
                shaders->setVec3("objectColor", objectColor);

                // Use the model matrix for rendering
                model->setModelMatrix(modelMatrix);
                model->draw();
            }

            // Rendering ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SwapBuffers();
            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR) {
                std::cerr << "OpenGL error: " << err << std::endl;
            }
        }
    }
}
