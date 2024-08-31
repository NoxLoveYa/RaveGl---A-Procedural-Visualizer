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
        void initializeObj(const std::vector<float>& vertices, const std::vector<float>& texCoords, const std::vector<float>& normals, const std::vector<int>& indexData);
 
    private:
        void initialize(const float* vertices, size_t size);

        GLuint _vao;
        GLuint _vbo;
        std::vector<GLuint> _vboBuffers; // Store all the VBOs
};