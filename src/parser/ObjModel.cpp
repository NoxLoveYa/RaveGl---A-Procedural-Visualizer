/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ObjModel.cpp
*/

#include "ObjModel.hpp"
#include <iostream>
#include <ObjLoader.hpp>

ObjModel::ObjModel(const std::string& filePath) {
    std::vector<Vertex>   vertices;
    std::vector<TexCoord> texCoords;
    std::vector<Normal>   normals;
    std::vector<Face>     faces;

    ObjLoader loader;
    if (loader.loadOBJ(filePath, vertices, texCoords, normals, faces)) {
        std::cout << "Vertices: " << vertices.size()
                  << " | Texture Coordinates: " << texCoords.size()
                  << " | Normals: " << normals.size() << " | Faces: " << faces.size() << std::endl;
        std::cout << "Processing data..." << std::endl;
        // processData(vertices, texCoords, normals, faces);
        _vao.initializeObj(_vertexData, _texCoordData, _normalData, _indexData);
        _numFaces = faces.size();
        _position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 min(FLT_MAX);
        glm::vec3 max(-FLT_MAX);
        for (const auto& vertex : vertices) {
            min.x = std::min(min.x, vertex.x);
            min.y = std::min(min.y, vertex.y);
            min.z = std::min(min.z, vertex.z);
            max.x = std::max(max.x, vertex.x);
            max.y = std::max(max.y, vertex.y);
            max.z = std::max(max.z, vertex.z);
        }
        _boundingBox = {min, max};
    } else {
        std::cerr << "Failed to load OBJ file: " << filePath << std::endl;
    }
    // parseModel(filePath);
}

ObjModel::~ObjModel() { unloadModel(); }

void ObjModel::bind() { _vao.bind(); }

void ObjModel::unbind() { _vao.unbind(); }

void ObjModel::draw() {
    _vao.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indexData.size()), GL_UNSIGNED_INT, 0);
    _vao.unbind();
}

std::tuple<int, int, int> ObjModel::generateKey(int vertexIndex, int texCoordIndex,
                                                int normalIndex) {
    return std::make_tuple(vertexIndex, texCoordIndex, normalIndex);
}

int ObjModel::addUniqueVertex(const Vertex& vertex, const TexCoord& texCoord,
                              const Normal& normal) {
    int index = _vertexData.size() / 3;

    _vertexData.push_back(vertex.x);
    _vertexData.push_back(vertex.y);
    _vertexData.push_back(vertex.z);

    _texCoordData.push_back(texCoord.u);
    _texCoordData.push_back(texCoord.v);

    _normalData.push_back(normal.nx);
    _normalData.push_back(normal.ny);
    _normalData.push_back(normal.nz);

    return index;
}

void ObjModel::processData(const std::vector<Vertex>&   vertices,
                           const std::vector<TexCoord>& texCoords,
                           const std::vector<Normal>& normals, const std::vector<Face>& faces,
                           const std::string& binPath) {
    std::unordered_map<std::tuple<int, int, int>, int, TupleHash> uniqueVertexMap;

    for (const auto& face : faces) {
        for (int i = 0; i < 3; ++i) {
            int vertexIndex   = face.vertexIndices[i];
            int texCoordIndex = face.texCoordIndices[i];
            int normalIndex   = face.normalIndices[i];

            auto key = generateKey(vertexIndex, texCoordIndex, normalIndex);

            if (uniqueVertexMap.find(key) == uniqueVertexMap.end()) {
                const Vertex&   vertex   = vertices[vertexIndex];
                const TexCoord& texCoord = texCoords[texCoordIndex];
                const Normal&   normal   = normals[normalIndex];
                int             newIndex = addUniqueVertex(vertex, texCoord, normal);
                uniqueVertexMap[key]     = newIndex;
            }

            _indexData.push_back(uniqueVertexMap[key]);
        }
    }

    std::cout << " Vertices: " << _vertexData.size() / 3
              << " | texCoords: " << _texCoordData.size() / 2
              << " | normals: " << _normalData.size() / 3 << std::endl;
    std::cout << "Vertices: " << _vertexData.size() / 3 << " | Indices: " << _indexData.size()
              << std::endl;
    saveProcessedData(binPath);
    clearData(); // Clear the data after processing
    uniqueVertexMap.clear();
    uniqueVertexMap = std::unordered_map<std::tuple<int, int, int>, int, TupleHash>();

    std::cout << "Processed data" << std::endl;
}

void ObjModel::parseModel(const std::string& path) {
    // Implementation of model parsing
    std::vector<Vertex>   vertices;
    std::vector<TexCoord> texCoords;
    std::vector<Normal>   normals;
    std::vector<Face>     faces;

    ObjLoader loader;
    if (loader.loadOBJ(path, vertices, texCoords, normals, faces)) {
        std::cout << "Vertices: " << vertices.size()
                  << " | Texture Coordinates: " << texCoords.size()
                  << " | Normals: " << normals.size() << " | Faces: " << faces.size() << std::endl;
        std::cout << "Processing data..." << std::endl;
        std::filesystem::path binPath = path;
        binPath.replace_extension(".bin");
        processData(vertices, texCoords, normals, faces, binPath);
        _numFaces = faces.size();

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error after VAO initialization: " << err << std::endl;
        }
        // // Clear the vectors to free memory
        vertices.clear();
        vertices.shrink_to_fit();
        texCoords.clear();
        texCoords.shrink_to_fit();
        normals.clear();
        normals.shrink_to_fit();
        faces.clear();
        faces.shrink_to_fit();

        // // Clear data to free memory
        clearData();

        // Reload from .bin file
        loadProcessedData(binPath.string());
    } else {
        std::cerr << "Failed to load OBJ file: " << path << std::endl;
    }
}

void ObjModel::saveProcessedData(const std::string& filename) {
    // Implementation of saving processed data
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    size_t vertexDataSize   = _vertexData.size();
    size_t texCoordDataSize = _texCoordData.size();
    size_t normalDataSize   = _normalData.size();
    size_t indexDataSize    = _indexData.size();
    size_t numFaces         = _numFaces;

    // Write sizes
    outFile.write(reinterpret_cast<const char*>(&vertexDataSize), sizeof(vertexDataSize));
    outFile.write(reinterpret_cast<const char*>(&texCoordDataSize), sizeof(texCoordDataSize));
    outFile.write(reinterpret_cast<const char*>(&normalDataSize), sizeof(normalDataSize));
    outFile.write(reinterpret_cast<const char*>(&indexDataSize), sizeof(indexDataSize));
    outFile.write(reinterpret_cast<const char*>(&numFaces), sizeof(numFaces));

    // Write data
    outFile.write(reinterpret_cast<const char*>(_vertexData.data()),
                  vertexDataSize * sizeof(float));
    outFile.write(reinterpret_cast<const char*>(_texCoordData.data()),
                  texCoordDataSize * sizeof(float));
    outFile.write(reinterpret_cast<const char*>(_normalData.data()),
                  normalDataSize * sizeof(float));
    outFile.write(reinterpret_cast<const char*>(_indexData.data()),
                  indexDataSize * sizeof(unsigned int));

    clearData(); // Clear the data after saving
    std::cout << "Model data saved successfully to " << filename << std::endl;
    outFile.close();
}

bool ObjModel::loadProcessedData(const std::string& filename) {
    // Implementation of loading processed data
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }

    clearData(); // Clear the data before loading

    size_t vertexDataSize;
    size_t texCoordDataSize;
    size_t normalDataSize;
    size_t indexDataSize;
    size_t numFaces;

    // Read sizes
    inFile.read(reinterpret_cast<char*>(&vertexDataSize), sizeof(vertexDataSize));
    inFile.read(reinterpret_cast<char*>(&texCoordDataSize), sizeof(texCoordDataSize));
    inFile.read(reinterpret_cast<char*>(&normalDataSize), sizeof(normalDataSize));
    inFile.read(reinterpret_cast<char*>(&indexDataSize), sizeof(indexDataSize));
    inFile.read(reinterpret_cast<char*>(&numFaces), sizeof(numFaces));

    // Resize vectors to hold the data
    _vertexData.resize(vertexDataSize);
    _texCoordData.resize(texCoordDataSize);
    _normalData.resize(normalDataSize);
    _indexData.resize(indexDataSize);

    // Read data
    inFile.read(reinterpret_cast<char*>(_vertexData.data()), vertexDataSize * sizeof(float));
    inFile.read(reinterpret_cast<char*>(_texCoordData.data()), texCoordDataSize * sizeof(float));
    inFile.read(reinterpret_cast<char*>(_normalData.data()), normalDataSize * sizeof(float));
    inFile.read(reinterpret_cast<char*>(_indexData.data()), indexDataSize * sizeof(unsigned int));

    inFile.close();
    // Set the number of faces
    _numFaces = numFaces;

    _vao.initializeObj(_vertexData, _texCoordData, _normalData, _indexData);
    std::cout << "Model data loaded successfully from " << filename << std::endl;
    return true;
}

void ObjModel::clearData() {
    _vertexData.clear();
    _vertexData.shrink_to_fit();
    _texCoordData.clear();
    _texCoordData.shrink_to_fit();
    _normalData.clear();
    _normalData.shrink_to_fit();
    _indexData.clear();
    _indexData.shrink_to_fit();
    _numFaces = 0;
}

void ObjModel::unloadModel() {
    clearData();
    _vao.deleteBuffers();
}

std::unordered_map<std::string, std::shared_ptr<ObjModel>>
loadAllModels(const std::string& directoryPath) {
    std::unordered_map<std::string, std::shared_ptr<ObjModel>> models;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".obj") {
            std::string           objPath = entry.path().string();
            std::filesystem::path binPath = entry.path();
            binPath.replace_extension(".bin");
            std::string modelName =
                entry.path().stem().string(); // Get the file name without extension

            auto model = std::make_shared<ObjModel>(objPath);
            if (std::filesystem::exists(binPath)) {
                model->loadProcessedData(binPath.string());
            }

            models[modelName] = model;

            std::cout << "Processed model: " << modelName << std::endl;
        }
    }
    return models;
}