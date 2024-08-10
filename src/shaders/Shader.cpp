/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** Shader.cpp
*/

#include "Shader.hpp"

//Shader constructor for any number of shaders
Shader::Shader(const std::vector<std::pair<GLenum, std::string>>& shaderPaths)
{
    _program = createShaderProgram(shaderPaths);
}

//Shader constructor for a single directory, loading all shaders in that directory
Shader::Shader(const std::string& shaderDir)
{
    std::vector<std::pair<GLenum, std::string>> shaderPaths;

    for (const auto& entry : std::filesystem::directory_iterator(shaderDir)) {
        if (entry.path().extension() == ".vert") {
            shaderPaths.push_back({GL_VERTEX_SHADER, entry.path().string()});
        }
        if (entry.path().extension() == ".frag") {
            shaderPaths.push_back({GL_FRAGMENT_SHADER, entry.path().string()});
        }
        if (entry.path().extension() == ".glsl") {
            shaderPaths.push_back({GL_VERTEX_SHADER, entry.path().string()});
            shaderPaths.push_back({GL_FRAGMENT_SHADER, entry.path().string()});
        }
    }
    _program = createShaderProgram(shaderPaths);
}

void Shader::use() const
{
    glUseProgram(_program);
}

GLuint Shader::getProgram() const
{
    return _program;
}

std::string Shader::readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;

    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    int success = 0;

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint Shader::createShaderProgram(const std::vector<std::pair<GLenum, std::string>>& shaderPaths)
{
    std::vector<GLuint> shaders;
    int success = 0;

    for (const auto& shaderPath : shaderPaths) {
        std::string shaderCode = readFile(shaderPath.second);
        GLuint shader = compileShader(shaderPath.first, shaderCode);
        shaders.push_back(shader);
    }

    GLuint shaderProgram = glCreateProgram();
    for (const auto& shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    for (const auto& shader : shaders) {
        glDeleteShader(shader);
    }
    return shaderProgram;
}