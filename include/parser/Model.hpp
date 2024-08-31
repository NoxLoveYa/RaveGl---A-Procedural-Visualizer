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
#include <memory>
#include "ObjStructs.hpp"

// struct Vertex {
//     float x, y, z;
// };

// struct TexCoord {
//     float u, v, w;
// };

// struct Normal {
//     float nx, ny, nz;
// };

// struct Face {
//     std::vector<int> vertexIndices;
//     std::vector<int> texCoordIndices;
//     std::vector<int> normalIndices;
// };

//ensure that the tuple is hashed in a way that the order of the elements does not matter
struct TupleHash {
    std::size_t operator()(const std::tuple<int, int, int>& t) const {
        auto hash1 = std::hash<int>{}(std::get<0>(t));
        auto hash2 = std::hash<int>{}(std::get<1>(t));
        auto hash3 = std::hash<int>{}(std::get<2>(t));
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
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
        //std::vector<float> getVertexData() { return _vertexData; }
        std::vector<float> getTexCoordData() { return _texCoordData; }
        std::vector<float> getNormalData() { return _normalData; }
        std::vector<int> getIndexData() { return _indexData; }
        VertexArray getVao() { return _vao; }

        // Processing data
        void parseModel(const std::string& path);
        void saveProcessedData(const std::string& filename);
        bool loadProcessedData(const std::string& filename);
        void clearData();

        void processData(const std::vector<Vertex>& vertices, const std::vector<TexCoord>& texCoords, const std::vector<Normal>& normals, const std::vector<Face>& faces, const std::string &binPath);
    private:
        //ensure the vertex is unique (optimization)
        int addUniqueVertex(const Vertex& vertex, const TexCoord& texCoord, const Normal& normal);
        std::tuple<int, int, int> generateKey(int vertexIndex, int texCoordIndex, int normalIndex);


        VertexArray _vao;

        std::vector<float> _vertexData;
        std::vector<float> _texCoordData;
        std::vector<float> _normalData;
        std::vector<int> _indexData; // Flattened indices
        size_t _numFaces;
};

//Process all data and add it to a Map
std::unordered_map<std::string, std::shared_ptr<Model>> loadAllModels(const std::string& directoryPath);