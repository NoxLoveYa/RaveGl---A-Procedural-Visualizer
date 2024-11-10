/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ProceduralVisualizer.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Model.hpp"
#include "shaders.hpp"
#include "Frustum.hpp"
#include "VertexArray.hpp"
#include "camera.hpp"
#include <shaders.hpp>
#include <camera.hpp>
#include <ObjModel.hpp>
#include <primitive_generator.hpp>
#include <camera.hpp>

class ProceduralVisualizer {
  public:
    ProceduralVisualizer(int width, int height, Camera& camera);
    ~ProceduralVisualizer();

    void initialize();
    void update(float deltaTime);
    void render();
    void addModel(const std::string& modelName, const std::shared_ptr<ObjModel>& model);
    void setLightProperties(const glm::vec3& lightPos, const glm::vec3& lightColor);
    void setObjectColor(const glm::vec3& color);

  private:
    int                                                        width, height;
    glm::vec3                                                  lightPos;
    glm::vec3                                                  lightColor;
    glm::vec3                                                  objectColor;
    glm::mat4                                                  projection;
    glm::mat4                                                  view;
    std::shared_ptr<Frustum>                                   frustum;
    std::shared_ptr<Shaders>                                   shaders;
    std::unordered_map<std::string, std::shared_ptr<ObjModel>> models;
    MouseState                                                 mouseState;
    VertexArray                                                randomVAO;
    std::vector<glm::vec3>                                     randomPositions;
    int                                                        numVertices;
    int                                                        numPositions;
    Camera&                                                    camera;
    GLuint                                                     quadVAO;
    GLuint                                                     quadVBO;
    glm::vec2                                                  fractalOffset;
    float                                                      fractalZoom;
    int                                                        maxIterations;
    float                                                      time;
};