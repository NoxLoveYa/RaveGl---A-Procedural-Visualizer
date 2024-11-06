// /*
// ** EPITECH PROJECT, 2024
// ** RaveGl---A-Procedural-Visualizer
// ** File description:
// ** ObjModel.cpp
// */

#include "Model.hpp"

bool Model::isInFrustum(const Frustum& frustum) {
    const glm::vec4* planes = frustum.getPlanes(); // Get a pointer to the array of planes
    for (int i = 0; i < 6; ++i) {
        glm::vec3 positiveVertex = _boundingBox.min;
        if (planes[i].x >= 0)
            positiveVertex.x = _boundingBox.max.x;
        if (planes[i].y >= 0)
            positiveVertex.y = _boundingBox.max.y;
        if (planes[i].z >= 0)
            positiveVertex.z = _boundingBox.max.z;

        if (glm::dot(glm::vec3(planes[i]), positiveVertex) + planes[i].w < 0) {
            setModelShown(false);
            return false;
        }
    }
    setModelShown(true);
    return true;
}
