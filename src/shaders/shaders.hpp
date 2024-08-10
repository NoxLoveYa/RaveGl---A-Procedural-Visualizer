/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** shaders
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>

class Shaders
{
public:
    Shaders();
    ~Shaders();
    GLuint compileShaderFromFile(const char *path, GLenum type);
    bool createProgram(GLuint vertexShader, GLuint fragmentShader, const char *id);
    void useProgram(const char *id);

private:
    std::map<const char *, GLuint> programs;
};
