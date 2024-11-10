/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ObjModel.hpp
*/

#pragma once

#include "Model.hpp"

class ObjModel : public Model {
  public:
    // Constructor / Destructor
    ObjModel(const std::string& filePath);
    ObjModel(){};
    ~ObjModel();

    // Methods
    void bind() override;
    void unbind() override;
    void draw() override;

    // Processing data
    void parseModel(const std::string& path) override;
    void saveProcessedData(const std::string& filename) override;
    bool loadProcessedData(const std::string& filename) override;
    void clearData() override;
    void unloadModel() override;

    // new methods
    void processData(const std::vector<Vertex>& vertices, const std::vector<TexCoord>& texCoords,
                     const std::vector<Normal>& normals, const std::vector<Face>& faces,
                     const std::string& binPath);
    std::tuple<int, int, int> generateKey(int vertexIndex, int texCoordIndex, int normalIndex);
    int addUniqueVertex(const Vertex& vertex, const TexCoord& texCoord, const Normal& normal);
};

std::unordered_map<std::string, std::shared_ptr<ObjModel>>
loadAllModels(const std::string& directoryPath);