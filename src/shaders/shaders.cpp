/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** shaders
*/

#include "shaders.hpp"

Shaders::Shaders() {}

Shaders::~Shaders() {
    for (auto& program : programs) {
        glDeleteProgram(program.second);
    }
}

GLuint Shaders::compileShaderFromFile(const char* path, GLenum type) {
    std::ifstream file(path);
    std::string   source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    const char* src = source.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint  success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << "from file: " << path << std::endl;
        return 0;
    }
    return shader;
}

bool Shaders::createProgram(GLuint vertexShader, GLuint fragmentShader, const char* id) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint  success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    programs[id] = program;
    return true;
}

void Shaders::useProgram(const char* id) {
    if (programs.find(id) == programs.end()) {
        std::cerr << "[" << id << "]" << "ERROR::SHADER::PROGRAM::ID_NOT_FOUND\n";
        return;
    }
    glUseProgram(programs[id]);
}

GLuint Shaders::getProgramID(const char* id) const {
    auto it = programs.find(id);
    if (it != programs.end()) {
        return it->second;
    }
    std::cerr << "ERROR::SHADER::PROGRAM::ID_NOT_FOUND\n";
    return 0;
}

// shader management

void Shaders::attachShader(const char* id, GLuint shader) { glAttachShader(programs[id], shader); }

void Shaders::linkProgram(const char* id) {
    glLinkProgram(programs[id]);
    GLint  success;
    GLchar infoLog[512];
    glGetProgramiv(programs[id], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programs[id], 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

// setters

void Shaders::setBool(const char* name, bool value) const {
    glUniform1i(glGetUniformLocation(programs.begin()->second, name), (int)value);
}

void Shaders::setInt(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(programs.begin()->second, name), value);
}

void Shaders::setFloat(const char* name, float value) const {
    glUniform1f(glGetUniformLocation(programs.begin()->second, name), value);
}

void Shaders::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(programs.begin()->second, name.c_str()), 1, &value[0]);
}

void Shaders::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(programs.begin()->second, name.c_str()), x, y);
}

void Shaders::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(programs.begin()->second, name.c_str()), 1, &value[0]);
}

void Shaders::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(programs.begin()->second, name.c_str()), x, y, z);
}

void Shaders::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(programs.begin()->second, name.c_str()), 1, &value[0]);
}

void Shaders::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(programs.begin()->second, name.c_str()), x, y, z, w);
}

void Shaders::setMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(programs.begin()->second, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
}

void Shaders::setMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(programs.begin()->second, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
}

void Shaders::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programs.begin()->second, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
}
