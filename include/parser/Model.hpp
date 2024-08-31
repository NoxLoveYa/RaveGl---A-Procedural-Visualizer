/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** Model.hpp
*/

#pragma once

#include "VertexArray.hpp"

#include <glad/glad.h>
//include glm
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <filesystem>
#include <string>

//#include <glm/glm.hpp>
struct Vertex {
    float x, y, z;
};

struct TexCoord {
    float u, v;
};

struct Normal {
    float nx, ny, nz;
};

//ensure that the tuple is hashed in a way that the order of the elements does not matter
struct TupleHash {
    std::size_t operator()(const std::tuple<int, int, int>& t) const {
        auto hash1 = std::hash<int>{}(std::get<0>(t));
        auto hash2 = std::hash<int>{}(std::get<1>(t));
        auto hash3 = std::hash<int>{}(std::get<2>(t));
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};

struct Face {
    std::vector<int> vertexIndices;
    std::vector<int> texCoordIndices;
    std::vector<int> normalIndices;
};


class Model {
    public:
        // Constructor / Destructor
        Model(const std::string& filePath);
        Model();
        ~Model();

        // methods
        void bind();
        void unbind();
        void draw();

        // getters
        size_t getNumVertices() { return _numFaces * 3; }
        size_t getNumFaces() { return _numFaces; }
        std::vector<float> getVertexData() { return _vertexData; }
        std::vector<float> getTexCoordData() { return _texCoordData; }
        std::vector<float> getNormalData() { return _normalData; }
        std::vector<int> getIndexData() { return _indexData; }
        VertexArray getVao() { return _vao; }

        // setters
        void setModelMatrix(const glm::mat4& modelMatrix) { _modelMatrix = modelMatrix; }

        // Processing data
        void parseModel(const std::string& path);
        void saveProcessedData(const std::string& filename);
        bool loadProcessedData(const std::string& filename);

        //Process all data and add it to a Map
        void processAllModels(const std::string& directoryPath, std::unordered_map<std::string, Model>& models);
    private:
        //individual parsing methods (contained in loadOBJ)
        bool loadOBJ(const std::string& path, std::vector<Vertex>& vertices, std::vector<TexCoord>& texCoords, std::vector<Normal>& normals, std::vector<Face>& faces);
        void processData(const std::vector<Vertex>& vertices, const std::vector<TexCoord>& texCoords, const std::vector<Normal>& normals, const std::vector<Face>& faces);
        void parseVertex(std::istringstream& iss, std::vector<Vertex>& vertices);
        void parseTexCoord(std::istringstream& iss, std::vector<TexCoord>& texCoords);
        void parseNormal(std::istringstream& iss, std::vector<Normal>& normals);
        void parseFaces(std::istringstream& iss, std::vector<Face>& faces);
        //ensure the vertex is unique (optimization)
        int addUniqueVertex(const Vertex& vertex, const TexCoord& texCoord, const Normal& normal);
        std::tuple<int, int, int> generateKey(int vertexIndex, int texCoordIndex, int normalIndex);


        VertexArray _vao;
        std::vector<float> _vertexData;
        std::vector<float> _texCoordData;
        std::vector<float> _normalData;
        std::vector<int> _indexData; // Flattened indices
        size_t _numFaces;
        glm::mat4 _modelMatrix;
};