/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** primitive_generator.cpp
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ostream>
#include <fstream>

#include <glm/glm.hpp>

class PrimitiveGenerator
{
    public:
        PrimitiveGenerator(const std::string& primitive_name, int numVertices, int numPositions, const std::string &filename);
        ~PrimitiveGenerator();

        void setPrimitiveName(const std::string& primitive_name);
        float randomFloat(float min, float max);
        std::vector<float> generateRandomVertices(int numVertices);
        std::vector<glm::vec3> generateRandomPositions(int numPositions);
        void appendVerticesToFile(const std::vector<float>& vertices, const std::string& filename);
        void appendPositionsToFile(const std::vector<glm::vec3>& positions, const std::string& filename);
        void clearFile(const std::string& filename);
        void printVertices(const std::vector<float>& vertices);
        void printPositions(const std::vector<glm::vec3>& positions);

        //getters
        std::vector<float> getVertices() const;
        std::vector<glm::vec3> getPositions() const;
        std::string getPrimitiveName() const;
    private:
        std::vector<float> _vertices;
        std::vector<glm::vec3> _positions;
        std::string _primitive_name;
};
