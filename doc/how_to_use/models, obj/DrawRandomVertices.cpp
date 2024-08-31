/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** DrawRandomVertices.cpp
*/

// #include "primitive_generator.hpp"
// #include "random_primitive.hpp"

// We will be using primitive generator in order to create a random shapes with X vertices and X positions

/*Window::update() {

    int numVertices = 128;
    int numPositions = 10;
    PrimitiveGenerator theShapes("", numVertices, numPositions, "src/primitives/random_primitive.hpp");
    std::vector<float> vertices = theShapes.getVertices();
    std::vector<glm::vec3> randomPositions = theShapes.getPositions();

    Shaders shaders;
    GLuint vertexShader = shaders.compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = shaders.compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    shaders.createProgram(vertexShader, fragmentShader, theShapes.getPrimitiveName().c_str());

    VertexArray randomVAO(vertices.data(), vertices.size());
    randomVAO.bindAndUnbind();

    // While loop (!Close) : 
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaders.useProgram(theShapes.getPrimitiveName().c_str());

        // Set up view and projection matrices
        shaders.setMat4("projection", projection);
        shaders.setMat4("view", view);

        // Render random primitives
        randomVAO.bind();
        for (unsigned int i = 0; i < randomPositions.size(); i++) {
            // Calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, randomPositions[i]);
            float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaders.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, numVertices);
        }
    randomVAO.deleteBuffers(); // acts like the destructor
}
*/