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

        Shaders shaders;
        GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
        shaders.createProgram(vertexShader, fragmentShader, "cube");
        // shaders.createProgram(vertexShader, fragmentShader, theShapes.getPrimitiveName().c_str());

        //pre process all .obj files and save them in a file readable afterwards
        //Model model;
        //for each model, model.loadObj("src/primitives/obj/complex_torus.obj");
        //model.processData(get_all_vertices, get_all_normals, get_all_uvs);
        //model.saveData("src/primitives/obj/complex_torus.obj");
        //Model loadedComplexTorus;
        //loadedComplexTorus.parseModel("src/primitives/obj/complex_torus.obj");
        //loadedComplexTorus.loadProcessedData("src/primitives/obj/complex_torus.bin");
        //loadedComplexTorus.parseModel("src/primitives/obj/complex_torus.obj");
        //loadedComplexTorus.saveProcessedData("src/primitives/obj/complex_torus.bin");
        //loadedComplexTorus.loadProcessedData("src/primitives/obj/complex_torus.bin");
        //std::cout << "loadedComplexTorus " << loadedComplexTorus.getNumFaces() << std::endl;

        // Model loadedCreepyGirl;
        // loadedCreepyGirl.parseModel("src/primitives/obj/Vanellope.obj");
        // loadedCreepyGirl.saveProcessedData("src/primitives/obj/Vanellope.bin");
        // loadedCreepyGirl.loadProcessedData("src/primitives/obj/Vanellope.bin");

        //load whenever needed
        // spawn at will

        GLuint torusVertexShader = shaders.compileShaderFromFile("src/shaders/glsl/torus_vertex_shader.glsl", GL_VERTEX_SHADER);
        GLuint torusFragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/torus_fragment_shader.glsl", GL_FRAGMENT_SHADER);
        //shaders.createProgram(torusVertexShader, torusFragmentShader, "complex_torus");
        shaders.createProgram(vertexShader, fragmentShader, "complex_torus");
        //shaders.createProgram(vertexShader, fragmentShader, "Vanellope");

        // VertexArray cubeVAO(cube_vertices, sizeof(cube_vertices));
        // cubeVAO.bindAndUnbind();
        // VertexArray randomVAO(vertices.data(), vertices.size());
        // randomVAO.bindAndUnbind();

        std::unordered_map<std::string, std::shared_ptr<Model>> models = processAllModels("src/primitives/obj");
        std::cout << "faceszgerhreherhree" <<  models["complex_torus"]->getNumFaces() << std::endl;

        // Debug: Verify that the model is correctly retrieved from the map
        if (models.find("complex_torus") != models.end()) {
            std::cout << "Model 'complex_torus' found in map" << std::endl;
            std::cout << "Number of vertices: " << models["complex_torus"]->getNumVertices() << std::endl;
            std::cout << "Number of faces: " << models["complex_torus"]->getNumFaces() << std::endl;
            std::cout << "IndexData size: " << models["complex_torus"]->getIndexData().size() << std::endl;
        } else {
            std::cerr << "Model 'complex_torus' not found in map" << std::endl;
        }
        //Model loadedComplexTorus;
        //loadedComplexTorus.loadProcessedData("src/primitives/obj/complex_torus.bin");
        // loadedComplexTorus.getVao().initializeObj(loadedComplexTorus.getVertexData(), loadedComplexTorus.getTexCoordData(), loadedComplexTorus.getNormalData(), loadedComplexTorus.getIndexData());
        // std::cout << "loadedComplexTorus " << loadedComplexTorus.getNumVertices() << std::endl;
        // std::cout << "loadedComplexTorus faces" << loadedComplexTorus.getNumFaces() << std::endl;
        // for (auto& [modelName, model] : models) {
        //     std::cout << "Using model: " << modelName << std::endl;
        //     std::cout << "gimme that !" << model.getNumVertices() << std::endl;
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
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
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
            // shaders.useProgram("complex_torus");

            // shaders.setMat4("projection", projection);
            // shaders.setMat4("view", view);
            // glm::mat4 model = glm::mat4(1.0f);
            // model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
            // shaders.setMat4("model", model);
            // shaders.setVec3("lightPos", lightPos);
            // shaders.setVec3("viewPos", camera.Position);
            // shaders.setVec3("lightColor", lightColor);
            // shaders.setVec3("objectColor", objectColor);
            // models["complex_torus"].draw();

            // for (auto& [modelName, model] : models) {
            //     //shaders.useProgram(modelName.c_str());
            //     //std::cout << "Drawing model: [" << modelName << "]" << std::endl;
            //     // Apply transformations and other operations to the model
            //     glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
            //     glm::mat4 view = camera.GetViewMatrix();

            //     // Light and material properties
            //     glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
            //     glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

            //     // Example of applying transformations to the model
            //     glm::mat4 modelMatrix = glm::mat4(1.0f);
            //     modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
            //     modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            //     // Set the shader uniforms
            //     shaders.setMat4("model", modelMatrix);
            //     shaders.setMat4("view", view);
            //     shaders.setMat4("projection", projection);
            //     shaders.setVec3("lightPos", lightPos);
            //     shaders.setVec3("viewPos", camera.Position);
            //     shaders.setVec3("lightColor", lightColor);
            //     shaders.setVec3("objectColor", objectColor);

            //     // Use the model matrix for rendering
            //     model.setModelMatrix(modelMatrix);
            //     model.draw();
            // }

            // render primitives (Cubes in this case)
            //shaders.useProgram("cube");

            // set up view and projection matrices
            // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
            // shaders.setMat4("projection", projection);
            // // camera/view transformation
            // glm::mat4 view = camera.GetViewMatrix();
            // shaders.setMat4("view", view);

            // // render container
            //cubeVAO.bind();
            // glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            // glm::mat4 model = glm::mat4(1.0f);
            // model = glm::translate(model, modelPosition);
            // shaders.setMat4("model", model);
            // glDrawArrays(GL_TRIANGLES, 0, 36);
            // for (unsigned int i = 0; i < 10; i++) {
            //     // calculate the model matrix for each object and pass it to shader before drawing
            //     glm::mat4 model = glm::mat4(1.0f);
            //     model = glm::translate(model, cubePositions[i]);
            //     float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
            //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //     shaders.setMat4("model", model);

            //     glDrawArrays(GL_TRIANGLES, 0, 36);
            // }
        // shaders.useProgram(theShapes.getPrimitiveName().c_str());

        // // Set up view and projection matrices
        // shaders.setMat4("projection", projection);
        // shaders.setMat4("view", view);

        // // Render random primitives
        // randomVAO.bind();
        // for (unsigned int i = 0; i < randomPositions.size(); i++) {
        //     // Calculate the model matrix for each object and pass it to shader before drawing
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, randomPositions[i]);
        //     float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
        //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     shaders.setMat4("model", model);

        //     glDrawArrays(GL_TRIANGLES, 0, numVertices);
        // }

        // Draw the complex torus model
        if (models.find("complex_torus") == models.end()) {
            std::cerr << "Model complex_torus not found in models map." << std::endl;
            return;
        }
            shaders.useProgram("complex_torus");
            shaders.setMat4("projection", projection);
            shaders.setMat4("view", view);

            //Adjust model position (e.g., move it 5 units in front of the camera)
            // Adjust model position (e.g., move it 5 units in front of the camera)
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f)); // Move the model 5 units in front of the camera
            shaders.setMat4("model", model);
            shaders.setVec3("lightPos", lightPos);
            shaders.setVec3("viewPos", camera.Position);
            shaders.setVec3("lightColor", lightColor);
            shaders.setVec3("objectColor", objectColor);
            //complexTorus.draw();
            //loadedComplexTorus.draw();
            //loadedCreepyGirl.draw();
            // Model testTorus;
            // testTorus.loadProcessedData("src/primitives/obj/complex_torus.bin");
            // // std::cout << "testtorus " << testTorus.getNumVertices() << std::endl;
            // std::cout << "testtorus indexdata " << testTorus.getIndexData().size() << std::endl;
            // testTorus.draw();

            //drawModel(models, "complex_torus");
            models["complex_torus"]->draw();
            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR) {
                std::cerr << "OpenGL error: " << err << std::endl;
            }
            // Rendering ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SwapBuffers();
        }
        // cubeVAO.deleteBuffers();
        // randomVAO.deleteBuffers();
    }
}
