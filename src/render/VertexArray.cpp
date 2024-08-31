/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** VertexArray.cpp
*/

#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
}

VertexArray::VertexArray(const std::vector<float>& vertices)
{
    initialize(vertices.data(), vertices.size());
}

VertexArray::VertexArray(const float* vertices, size_t size)
{
    initialize(vertices, size);
}

void VertexArray::initialize(const float* vertices, size_t size)
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

    // Assuming the vertex data includes positions (3 floats per vertex) and texture coordinates (2 floats per vertex)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
}

void VertexArray::initializeObj(const std::vector<float>& vertices, const std::vector<float>& texCoords, const std::vector<float>& normals, const std::vector<int>& indexData)
{
    glBindVertexArray(_vao);

    // Vertex positions
    GLuint vertexVBO;
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    _vboBuffers.push_back(vertexVBO);

    // Texture coordinates
    if (!texCoords.empty()) {
        GLuint texCoordVBO;
        glGenBuffers(1, &texCoordVBO);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        _vboBuffers.push_back(texCoordVBO);
    }

    // Normals
    if (!normals.empty()) {
        GLuint normalVBO;
        glGenBuffers(1, &normalVBO);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        _vboBuffers.push_back(normalVBO);
    }

    // Indices (index buffer)
    GLuint eboID;
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(int), indexData.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    deleteBuffers();
}

void VertexArray::bindAndUnbind()
{
    bind();
    unbind();
}

void VertexArray::bind()
{
    glBindVertexArray(_vao);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::deleteBuffers()
{
    if (_vao != 0) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0; // Reset to 0 to indicate it has been deleted
    }
    if (_vbo != 0) {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0; // Reset to 0 to indicate it has been deleted
    }
    if (!_vboBuffers.empty()) {
        for (GLuint vbo : _vboBuffers) {
            glDeleteBuffers(1, &vbo);
        }
    }
}

void VertexArray::addBuffer(const std::vector<float>& data, GLuint index, GLint size)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(index);

    _vboBuffers.push_back(vbo);
}