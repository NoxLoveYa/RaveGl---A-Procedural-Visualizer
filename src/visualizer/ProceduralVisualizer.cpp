/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ProceduralVisualizer.cpp
*/

#include "ProceduralVisualizer.hpp"
#include "primitive_generator.hpp"
#include "random_primitive.hpp"
#include "ObjLoader.hpp"

ProceduralVisualizer::ProceduralVisualizer(int width, int height, Camera& camera,
                                           GLFWwindow& window)
    : width(width), height(height), numVertices(128), numPositions(10), camera(camera),
      window(window) {
    frustum       = std::make_shared<Frustum>();
    shaders       = std::make_shared<Shaders>();
    fractalOffset = glm::vec2(0.0f);
    fractalZoom   = 1.0f;
    maxIterations = 100;
    time          = 0.0f;
}
ProceduralVisualizer::~ProceduralVisualizer() {}

void ProceduralVisualizer::initialize() {

    GLuint vertexComplexShader = shaders->compileShaderFromFile(
        "src/shaders/glsl/complex_vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentComplexShader = shaders->compileShaderFromFile(
        "src/shaders/glsl/complex_fragment_shader.glsl", GL_FRAGMENT_SHADER);
    shaders->createProgram(vertexComplexShader, fragmentComplexShader, "generic_complex_obj");
    // GLuint fractalVertexShader = shaders->compileShaderFromFile(
    //     "src/shaders/glsl/fractal_vertex_shader.glsl", GL_VERTEX_SHADER);
    // GLuint fractalFragmentShader = shaders->compileShaderFromFile(
    //     "src/shaders/glsl/fractal_fragment_shader.glsl", GL_FRAGMENT_SHADER);
    // shaders->createProgram(fractalVertexShader, fractalFragmentShader, "fractal_shader");
    // Set light properties
    glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    setLightProperties(lightPos, lightColor);

    // Set object color
    glm::vec3 objectColor(1.0f, 1.0f, 1.0f);
    setObjectColor(objectColor);

    ObjLoader objLoader;
    objLoader.prepareObjModels("src/primitives/obj");
    models = loadAllModels("src/primitives/obj");
    for (const auto& [modelName, model] : models) {
        addModel(modelName, model);
    }

    float quadVertices[] = {
        // positions
        -1.0f, 1.0f,  // Top-left
        -1.0f, -1.0f, // Bottom-left
        1.0f,  1.0f,  // Top-right
        1.0f,  -1.0f, // Bottom-right
    };

    // Set up VAO and VBO for quad (fractal)
    // glGenVertexArrays(1, &quadVAO);
    // glGenBuffers(1, &quadVBO);
    // glBindVertexArray(quadVAO);
    // glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    // glBindVertexArray(0);

    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

void ProceduralVisualizer::update(float deltaTime) {
    (void)deltaTime;
    view = camera.GetViewMatrix();
    frustum->update(projection, view);
    time += deltaTime;

    for (auto& [modelName, model] : models) {
        if (model->isInFrustum(*frustum)) {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix           = glm::translate(modelMatrix, model->getPosition());
            float angle           = glfwGetTime() * 50.0f;
            modelMatrix =
                glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            model->setModelMatrix(modelMatrix);
        }
    }
}

void ProceduralVisualizer::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaders->useProgram("generic_complex_obj");
    for (const auto& [modelName, model] : models) {
        if (model->isInFrustum(*frustum)) {
            shaders->setMat4("model", model->getModelMatrix());
            shaders->setMat4("view", view);
            shaders->setMat4("projection", projection);
            shaders->setVec3("lightPos", lightPos);
            shaders->setVec3("viewPos", camera.Position);
            shaders->setVec3("lightColor", lightColor);
            shaders->setVec3("objectColor", objectColor);
            model->draw();
        }
    }
    // shaders->useProgram("fractal_shader");
    // shaders->setVec2("u_resolution", glm::vec2(width, height));
    // shaders->setFloat("u_time", time); // Pass the time uniform

    // // Bind the quad VAO and draw it
    // glBindVertexArray(quadVAO);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // glBindVertexArray(0);
}

void ProceduralVisualizer::addModel(const std::string&               modelName,
                                    const std::shared_ptr<ObjModel>& model) {
    models[modelName] = model;
}

void ProceduralVisualizer::setLightProperties(const glm::vec3& lightPos,
                                              const glm::vec3& lightColor) {
    this->lightPos   = lightPos;
    this->lightColor = lightColor;
}

void ProceduralVisualizer::setObjectColor(const glm::vec3& color) { this->objectColor = color; }