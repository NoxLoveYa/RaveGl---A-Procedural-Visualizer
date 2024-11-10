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

ProceduralVisualizer::ProceduralVisualizer(int width, int height, Camera& camera)
    : width(width), height(height), numVertices(128), numPositions(10), camera(camera) {
    frustum = std::make_shared<Frustum>();
    shaders = std::make_shared<Shaders>();
}

ProceduralVisualizer::~ProceduralVisualizer() {}

void ProceduralVisualizer::initialize() {
    GLuint vertexComplexShader = shaders->compileShaderFromFile(
        "src/shaders/glsl/complex_vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentComplexShader = shaders->compileShaderFromFile(
        "src/shaders/glsl/complex_fragment_shader.glsl", GL_FRAGMENT_SHADER);
    shaders->createProgram(vertexComplexShader, fragmentComplexShader, "generic_complex_obj");

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

    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

void ProceduralVisualizer::update(float deltaTime) {
    (void)deltaTime;
    view = camera.GetViewMatrix();
    frustum->update(projection, view);

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