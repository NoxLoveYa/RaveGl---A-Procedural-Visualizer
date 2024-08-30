/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** primitive_generator.cpp
*/

#include "primitive_generator.hpp"

const char *military_alphabet[] = {
    "Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf",
    "Hotel", "India", "Juliett", "Kilo", "Lima", "Mike", "November",
    "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform",
    "Victor", "Whiskey", "Xray", "Yankee", "Zulu"
};

std::string generateRandomName()
{
    int index = rand() % 26;
    std::string primary_name = military_alphabet[index];
    int number = rand() % 10000;

    return primary_name + "_" + std::to_string(number);
}

// use the primitive_name, if not provided generate a random uuid
void PrimitiveGenerator::setPrimitiveName(const std::string& primitive_name)
{
    _primitive_name = primitive_name;
    if (_primitive_name.empty()) {
        _primitive_name = generateRandomName();
    }
}

PrimitiveGenerator::~PrimitiveGenerator()
{
}

PrimitiveGenerator::PrimitiveGenerator(const std::string& primitive_name, int numVertices, int numPositions, const std::string &filename)
{
    setPrimitiveName(primitive_name);
    _vertices = generateRandomVertices(numVertices);
    _positions = generateRandomPositions(numPositions);

    clearFile(filename);
    appendVerticesToFile(_vertices, filename);
    appendPositionsToFile(_positions, filename);
}

float PrimitiveGenerator::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Function to generate random vertices
std::vector<float> PrimitiveGenerator::generateRandomVertices(int numVertices)
{
    std::vector<float> vertices;
    for (int i = 0; i < numVertices; ++i) {
        float x = randomFloat(-1.0f, 1.0f);
        float y = randomFloat(-1.0f, 1.0f);
        float z = randomFloat(-1.0f, 1.0f);
        float u = randomFloat(0.0f, 1.0f);
        float v = randomFloat(0.0f, 1.0f);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(u);
        vertices.push_back(v);
    }
    return vertices;
}

std::vector<glm::vec3> PrimitiveGenerator::generateRandomPositions(int numPositions)
{
    std::vector<glm::vec3> positions;
    for (int i = 0; i < numPositions; ++i) {
        float x = randomFloat(-10.0f, 10.0f);
        float y = randomFloat(-10.0f, 10.0f);
        float z = randomFloat(-10.0f, 10.0f);
        positions.push_back(glm::vec3(x, y, z));
    }
    return positions;
}

void PrimitiveGenerator::appendVerticesToFile(const std::vector<float>& vertices, const std::string& filename)
{
    std::ofstream file;
    file.open(filename, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "#pragma once" << std::endl;
    file << "#include <glm/glm.hpp>" << std::endl;
    file << std::endl;
    file << "float " << _primitive_name << "_vertices[] = {" << std::endl;
    file << "    // x, y, z, u, v" << std::endl;
    file << "    // Positions        // Texture Coords " << std::endl;
    for (size_t i = 0; i < vertices.size(); i += 5) {
        file << "    " << vertices[i] << "f, " << vertices[i + 1] << "f, " << vertices[i + 2] << "f,  " << vertices[i + 3] << "f, " << vertices[i + 4] << "f," << std::endl;
    }
    file << "};" << std::endl;

    file.close();
}

void PrimitiveGenerator::appendPositionsToFile(const std::vector<glm::vec3>& positions, const std::string& filename)
{
    std::ofstream file;
    file.open(filename, std::ios::app); // Open file in append mode

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    file << std::endl;
    file << "glm::vec3 " << _primitive_name << "_positions[] = {" << std::endl;
    file << "    // x, y, z" << std::endl;
    for (const auto& pos : positions) {
        file << "    glm::vec3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f)," << std::endl;
    }
    file << "};" << std::endl;

    file.close();
}

void PrimitiveGenerator::clearFile(const std::string& filename)
{
    std::ofstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc); // Open file in truncate mode

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file.close();
}

// Debug
void PrimitiveGenerator::printVertices(const std::vector<float>& vertices)
{
    std::cout << "float random_vertices[] = {" << std::endl;
    for (size_t i = 0; i < vertices.size(); i += 5) {
        std::cout << "    " << vertices[i] << "f, " << vertices[i + 1] << "f, " << vertices[i + 2] << "f,  " << vertices[i + 3] << "f, " << vertices[i + 4] << "f," << std::endl;
    }
    std::cout << "};" << std::endl;
}

void PrimitiveGenerator::printPositions(const std::vector<glm::vec3>& positions) {
    std::cout << "glm::vec3 random_positions[] = {" << std::endl;
    for (const auto& pos : positions) {
        std::cout << "    glm::vec3(" << pos.x << "f, " << pos.y << "f, " << pos.z << "f)," << std::endl;
    }
    std::cout << "};" << std::endl;
}

//getters

std::vector<float> PrimitiveGenerator::getVertices() const
{
    return _vertices;
}

std::vector<glm::vec3> PrimitiveGenerator::getPositions() const
{
    return _positions;
}

std::string PrimitiveGenerator::getPrimitiveName() const
{
    return _primitive_name;
}
