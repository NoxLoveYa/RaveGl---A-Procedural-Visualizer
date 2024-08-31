/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** DrawMultipleObject.cpp
*/

//Lets see how to draw multiple objects in the scene
// In this example we will use the processAllModels function to load all the models in the folder and then draw them in the scene

// #include "Model.hpp"

/* Window::update() {

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    MouseState mouseState;
    Shaders shaders;
    //Create the program and shaders
    GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);

    std::unordered_map<std::string, std::shared_ptr<Model>> models = processAllModels("src/primitives/obj");

    //don't forget to use the program
    for (auto& [modelName, model] : models) {
        shaders->createProgram(vertexShader, fragmentShader, modelName.c_str());
        std::cout << "Using model: " << modelName << std::endl;
        std::cout << "gimme that !" << model->getNumVertices() << std::endl;
    }

    //
    //
    // After clearing the window : 
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // use the model
    for (auto& [modelName, model] : models) {
        shaders->useProgram(modelName.c_str());
        std::cout << "Drawing model: [" << modelName.c_str() << "]" << std::endl;
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
*/
