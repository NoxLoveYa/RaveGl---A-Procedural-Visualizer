/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** Shader.hpp
*/

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class Shader
{
    public:
        // Shader construction from any number of shaders
        Shader(const std::vector<std::pair<GLenum, std::string>>& shaderPaths);
        //Shader constructor for a single directory, loading all shaders in that directory
        Shader(const std::string& shaderDir);
        void use() const;
        GLuint getProgram() const;

    private:
        GLuint _program;
        std::string readFile(const std::string& filePath);
        GLuint compileShader(GLenum type, const std::string& source);
        GLuint createShaderProgram(const std::vector<std::pair<GLenum, std::string>>& shaderPaths);
};

#endif // SHADER_HPP