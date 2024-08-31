/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** VertexArray.cpp
*/

#include "VertexArray.hpp"

VertexArray::VertexArray() : _vao(0), _vbo(0)
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
    addBuffer(vertices, 0, 3);

    // Texture coordinates
    if (!texCoords.empty()) {
        addBuffer(texCoords, 1, 2);
    }

    // Normals
    if (!normals.empty()) {
        addBuffer(normals, 2, 3);
    }
    // Indices (index buffer)
    createElementBuffer(indexData);

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
        _vboBuffers.clear();
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

void VertexArray::createElementBuffer(const std::vector<int>& indexData)
{
    GLuint eboID;
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(int), indexData.data(), GL_STATIC_DRAW);
}