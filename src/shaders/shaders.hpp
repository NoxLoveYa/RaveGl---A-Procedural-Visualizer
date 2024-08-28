/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** shaders
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    GLuint getProgramID(const char *id) const;
    //shader management
    void attachShader(const char *id, GLuint shader);
    void linkProgram(const char *id);
    
    //uniform management
    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;
    //vec2
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    //vec3
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    //vec4
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    //mat2
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    //mat3
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    //mat4
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    std::map<const char *, GLuint> programs;
};
