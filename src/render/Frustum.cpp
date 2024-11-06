/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** Frutsum.cpp
*/

#include "Frustum.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void Frustum::update(const glm::mat4& projection, const glm::mat4& view) {
    try {
        glm::mat4 vp = projection * view;

        const float* m = glm::value_ptr(vp);

        // Extract frustum planes
        // Left plane
        planes[0] = glm::vec4(m[3] + m[0], m[7] + m[4], m[11] + m[8], m[15] + m[12]);
        // Right plane
        planes[1] = glm::vec4(m[3] - m[0], m[7] - m[4], m[11] - m[8], m[15] - m[12]);
        // Bottom plane
        planes[2] = glm::vec4(m[3] + m[1], m[7] + m[5], m[11] + m[9], m[15] + m[13]);
        // Top plane
        planes[3] = glm::vec4(m[3] - m[1], m[7] - m[5], m[11] - m[9], m[15] - m[13]);
        // Near plane
        planes[4] = glm::vec4(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]);
        // Far plane
        planes[5] = glm::vec4(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]);

        // Normalize the planes and check for zero length
        for (int i = 0; i < 6; ++i) {
            glm::vec3 normal = glm::vec3(planes[i]);
            float     length = glm::length(normal);
            if (length > 0.0f) {
                planes[i] /= length;
            } else {
                std::cerr << "Warning: Plane " << i << " has zero length normal vector."
                          << std::endl;
                planes[i] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception in frustum.update(): " << ex.what() << std::endl;
    }
}

bool Frustum::isPointVisible(const glm::vec3& point) const {
    // Check point against all frustum planes
    for (int i = 0; i < 6; ++i) {
        if (glm::dot(glm::vec3(planes[i]), point) + planes[i].w < 0) {
            // Point is outside this plane
            return false;
        }
    }
    return true;
}