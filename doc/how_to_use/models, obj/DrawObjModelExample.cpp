/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ModelExample.cpp
*/

// Include Model.hpp

//In window_update.cpp, (update function)

/* Window::update()
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    MouseState mouseState;
    Shaders shaders;
    //Create the program and shaders
    GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    shaders.createProgram(vertexShader, fragmentShader, "complex_torus");

/////////////////////// Create the model (method 1: create a model from a file) ///////////////////////
    Model model("src/primitives/obj/complex_torus.obj");

    //
    //
    // While loop (!Close) :
        // After clearing the window : 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaders.useProgram("complex_torus");
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shaders.setMat4("projection", projection);
        shaders.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
        shaders.setMat4("model", model);
        shaders.setVec3("lightPos", lightPos);
        shaders.setVec3("viewPos", camera.Position);
        shaders.setVec3("lightColor", lightColor);
        shaders.setVec3("objectColor", objectColor);
        model.draw(); //this will bind the VAO, draw and unbind the VAO

/////////////////////// Create a model (method 2: create a model and parse it manually) ///////////////////////
        // Model loadedCreepyGirl;
        // loadedCreepyGirl.parseModel("src/primitives/obj/Vanellope.obj");
        // loadedCreepyGirl.saveProcessedData("src/primitives/obj/Vanellope.bin");
        // loadedCreepyGirl.loadProcessedData("src/primitives/obj/Vanellope.bin"); // load the .bin file in the model

        //set shaders vectors... (same as above)
        // loadedCreepyGirl.draw(); //this will bind the VAO, draw and unbind the VAO

/////////////////////// Create a model (method 3: pre-process all models and then load it when needed) - this is the fastest method, but is not recommended for large models ///////////////////////
        
        std::unordered_map<std::string, std::shared_ptr<Model>> models = processAllModels("src/primitives/obj");
        // Debug: Verify that the model is correctly retrieved from the map
        if (models.find("complex_torus") != models.end()) {
            std::cout << "Model 'complex_torus' found in map" << std::endl;
            std::cout << "Number of vertices: " << models["complex_torus"]->getNumVertices() << std::endl;
            std::cout << "Number of faces: " << models["complex_torus"]->getNumFaces() << std::endl;
            std::cout << "IndexData size: " << models["complex_torus"]->getIndexData().size() << std::endl;
        } else {
            std::cerr << "Model 'complex_torus' not found in map" << std::endl;
        }

        //set shaders vectors... (same as above)

        models["complex_torus"]->draw(); //this will bind the VAO, draw and unbind the VAO

*/