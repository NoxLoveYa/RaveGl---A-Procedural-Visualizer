/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** Frustum
*/

#pragma once
// Frustum.hpp

#include <glm/glm.hpp>

class Frustum {
public:
    void update(const glm::mat4& projection, const glm::mat4& view);
    bool isPointVisible(const glm::vec3& point) const;
    const glm::vec4* getPlanes() const { return planes; }
    glm::vec4 getPlanes(int index) const { return planes[index]; }
private:
    glm::vec4 planes[6];
};