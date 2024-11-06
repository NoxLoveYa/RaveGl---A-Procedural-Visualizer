/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** Model.hpp
*/

#pragma once

#include "VertexArray.hpp"
#include <glad/glad.h>
//include glm
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <filesystem>
#include <string>
#include <memory>
#include "ObjStructs.hpp"
#include "Frustum.hpp"

//ensure that the tuple is hashed in a way that the order of the elements does not matter
struct TupleHash {
    std::size_t operator()(const std::tuple<int, int, int>& t) const {
        auto hash1 = std::hash<int>{}(std::get<0>(t));
        auto hash2 = std::hash<int>{}(std::get<1>(t));
        auto hash3 = std::hash<int>{}(std::get<2>(t));
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};

struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;
};

bool isBoundingBoxInFrustum(const Frustum& frustum, const BoundingBox& box);
class Model {
public:
    // Constructor / Destructor
    Model() : _numFaces(0), _position(0.0f) {}
    virtual ~Model() {}

    // Methods
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void draw() = 0;

    // Getters and setters
    size_t getNumVertices() const { return _numFaces * 3; }
    size_t getNumFaces() const { return _numFaces; }
    glm::vec3 getPosition() const { return _position; }
    void setPosition(const glm::vec3& position) { _position = position; }
    BoundingBox getBoundingBox() const { return _boundingBox; }

    // Processing data
    virtual void parseModel(const std::string& path) = 0;
    virtual void saveProcessedData(const std::string& filename) = 0;
    virtual bool loadProcessedData(const std::string& filename) = 0;
    virtual void clearData() = 0;
    virtual void unloadModel() = 0;

    //Frustum culling
    bool isInFrustum(const Frustum& frustum) const;

protected:
    VertexArray _vao;
    std::vector<float> _vertexData;
    std::vector<float> _texCoordData;
    std::vector<float> _normalData;
    std::vector<int> _indexData;
    size_t _numFaces;
    BoundingBox _boundingBox;

    glm::vec3 _position;
};
