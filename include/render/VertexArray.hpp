/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** VertexArray.hpp
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>


struct VertexData {
    float x, y, z; // Vertex coordinates
    float u, v, w;    // Texture coordinates
    float nx, ny, nz; // Normal coordinates

    bool operator==(const VertexData& other) const {
        return x == other.x && y == other.y && z == other.z &&
               u == other.u && v == other.v && w == other.w &&
               nx == other.nx && ny == other.ny && nz == other.nz;
    }
};

struct VertexDataHash {
    std::size_t operator()(const VertexData& v) const {
        return std::hash<float>()(v.x) ^ std::hash<float>()(v.y) ^ std::hash<float>()(v.z) ^
               std::hash<float>()(v.u) ^ std::hash<float>()(v.v) ^ std::hash<float>()(v.w) ^
               std::hash<float>()(v.nx) ^ std::hash<float>()(v.ny) ^ std::hash<float>()(v.nz);
    }
};

class VertexArray
{
    public:
        // Constructor / Destructor
        VertexArray(const std::vector<float>& vertices);
        VertexArray(const float* vertices, size_t size);
        VertexArray();
        ~VertexArray();

        // methods
        void bindAndUnbind(); // call this when you want to initialize the buffers (VAO/VBO) 
        void bind();
        void unbind();
        void deleteBuffers();

        // getters
        GLuint getVao() const { return _vao; }
        GLuint getVbo() const { return _vbo; }

        void addBuffer(const std::vector<float>& data, GLuint index, GLint size);
        void createElementBuffer(const std::vector<int>& indexData);
        void initializeObj(const std::vector<float>& vertices, const std::vector<float>& texCoords, const std::vector<float>& normals, const std::vector<int>& indexData);
    private:
        void initialize(const float* vertices, size_t size);

        GLuint _vao;
        GLuint _vbo;
        std::vector<GLuint> _vboBuffers; // Store all the VBOs
};
