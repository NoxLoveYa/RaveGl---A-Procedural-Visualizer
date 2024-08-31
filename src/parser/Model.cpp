/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ObjModel.cpp
*/

#include "Model.hpp"

Model::Model()
{
}

Model::Model(const std::string& filePath)
{
    std::vector<Vertex> vertices;
    std::vector<TexCoord> texCoords;
    std::vector<Normal> normals;
    std::vector<Face> faces;

    if (loadOBJ(filePath, vertices, texCoords, normals, faces)) {
        std::cout << "Vertices: " << vertices.size()
        << " | Texture Coordinates: " << texCoords.size()
        << " | Normals: " << normals.size()
        << " | Faces: " << faces.size() << std::endl;
        std::cout << "Processing data..." << std::endl;
        processData(vertices, texCoords, normals, faces);
        _vao.initializeObj(_vertexData, _texCoordData, _normalData, _indexData);
        _numFaces = faces.size();
    } else {
        std::cerr << "Failed to load OBJ file: " << filePath << std::endl;
    }
}

Model::~Model()
{
}

void Model::bind()
{
    _vao.bind();
}

void Model::unbind()
{
    _vao.unbind();
}

void Model::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, _indexData.size(), GL_UNSIGNED_INT, 0);
    unbind();
}

bool Model::loadOBJ(const std::string& path, std::vector<Vertex>& vertices, std::vector<TexCoord>& texCoords, std::vector<Normal>& normals, std::vector<Face>& faces) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
            parseVertex(iss, vertices);
        else if (prefix == "vt")
            parseTexCoord(iss, texCoords);
        else if (prefix == "vn")
            parseNormal(iss, normals);
        //f can have 3 or more index specifiers If there are more than 3, the triangles are the first and each pair of adjacent others
        else if (prefix == "f")
            parseFaces(iss, faces);
    }
    std::cout << "Loaded OBJ file: " << path << std::endl;
    return true;
}

std::tuple<int, int, int> Model::generateKey(int vertexIndex, int texCoordIndex, int normalIndex)
{
    return std::make_tuple(vertexIndex, texCoordIndex, normalIndex);
}

int Model::addUniqueVertex(const Vertex& vertex, const TexCoord& texCoord, const Normal& normal) {
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

void Model::processData(const std::vector<Vertex>& vertices, const std::vector<TexCoord>& texCoords, const std::vector<Normal>& normals, const std::vector<Face>& faces) {
    std::unordered_map<std::tuple<int, int, int>, int, TupleHash> uniqueVertexMap;

    for (const auto& face : faces) {
        for (int i = 0; i < 3; ++i) {
            int vertexIndex = face.vertexIndices[i];
            int texCoordIndex = face.texCoordIndices[i];
            int normalIndex = face.normalIndices[i];

            auto key = generateKey(vertexIndex, texCoordIndex, normalIndex);

            if (uniqueVertexMap.find(key) == uniqueVertexMap.end()) {
                const Vertex& vertex = vertices[vertexIndex];
                const TexCoord& texCoord = texCoords[texCoordIndex];
                const Normal& normal = normals[normalIndex];

                int newIndex = addUniqueVertex(vertex, texCoord, normal);
                uniqueVertexMap[key] = newIndex;
            }

            _indexData.push_back(uniqueVertexMap[key]);
        }
    }
    std::cout
    << " Vertices: " << _vertexData.size() / 3
    << " | texCoords: " << _texCoordData.size() / 2
    << " | normals: " << _normalData.size() / 3 << std::endl;
    std::cout << "Processed data" << std::endl;
}

void Model::parseVertex(std::istringstream& iss, std::vector<Vertex>& vertices)
{
    Vertex vertex;
    iss >> vertex.x >> vertex.y >> vertex.z;
    vertices.push_back(vertex);
}

void Model::parseTexCoord(std::istringstream& iss, std::vector<TexCoord>& texCoords)
{
    TexCoord texCoord;
    iss >> texCoord.u >> texCoord.v;
    texCoords.push_back(texCoord);
}

void Model::parseNormal(std::istringstream& iss, std::vector<Normal>& normals)
{
    Normal normal;
    iss >> normal.nx >> normal.ny >> normal.nz;
    normals.push_back(normal);
}

void Model::parseFaces(std::istringstream& iss, std::vector<Face>& faces)
{
    std::vector<int> vertexIndices;
    std::vector<int> texCoordIndices;
    std::vector<int> normalIndices;

    std::string vertex;
    while (iss >> vertex) {
        std::replace(vertex.begin(), vertex.end(), '/', ' ');
        std::istringstream vertexStream(vertex);
        int vertexIndex, texCoordIndex, normalIndex;
        vertexStream >> vertexIndex >> texCoordIndex >> normalIndex;

        // OBJ indices are 1-based, so we need to subtract 1
        vertexIndices.push_back(vertexIndex - 1);
        texCoordIndices.push_back(texCoordIndex - 1);
        normalIndices.push_back(normalIndex - 1);
    }

    // Triangulate the face : goes up to the second-to-last vertex (index vertexIndices.size() - 2).
        for (size_t i = 0; i < vertexIndices.size() - 2; ++i) {
        Face face;
        face.vertexIndices.push_back(vertexIndices[0]);
        face.vertexIndices.push_back(vertexIndices[i + 1]);
        face.vertexIndices.push_back(vertexIndices[i + 2]);

        face.texCoordIndices.push_back(texCoordIndices[0]);
        face.texCoordIndices.push_back(texCoordIndices[i + 1]);
        face.texCoordIndices.push_back(texCoordIndices[i + 2]);

        face.normalIndices.push_back(normalIndices[0]);
        face.normalIndices.push_back(normalIndices[i + 1]);
        face.normalIndices.push_back(normalIndices[i + 2]);

        faces.push_back(face);
    }
}

// Pre-process the data and save it to a binary file

void Model::saveProcessedData(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    size_t vertexDataSize = _vertexData.size();
    size_t texCoordDataSize = _texCoordData.size();
    size_t normalDataSize = _normalData.size();
    size_t indexDataSize = _indexData.size();
    size_t numFaces = _numFaces;
    std::cout << " numfaces: " << numFaces << std::endl;

    // Write sizes
    outFile.write(reinterpret_cast<const char*>(&vertexDataSize), sizeof(vertexDataSize));
    outFile.write(reinterpret_cast<const char*>(&texCoordDataSize), sizeof(texCoordDataSize));
    outFile.write(reinterpret_cast<const char*>(&normalDataSize), sizeof(normalDataSize));
    outFile.write(reinterpret_cast<const char*>(&indexDataSize), sizeof(indexDataSize));
    outFile.write(reinterpret_cast<const char*>(&numFaces), sizeof(numFaces));

    // Write data
    outFile.write(reinterpret_cast<const char*>(_vertexData.data()), vertexDataSize * sizeof(float));
    outFile.write(reinterpret_cast<const char*>(_texCoordData.data()), texCoordDataSize * sizeof(float));
    outFile.write(reinterpret_cast<const char*>(_normalData.data()), normalDataSize * sizeof(float));
    outFile.write(reinterpret_cast<const char*>(_indexData.data()), indexDataSize * sizeof(unsigned int));

    std::cout << "Model data saved successfully to " << filename << std::endl;
    outFile.close();
}

bool Model::loadProcessedData(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }

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

void Model::parseModel(const std::string& filePath)
{
    std::vector<Vertex> vertices;
    std::vector<TexCoord> texCoords;
    std::vector<Normal> normals;
    std::vector<Face> faces;

    if (loadOBJ(filePath, vertices, texCoords, normals, faces)) {
        std::cout << "Vertices: " << vertices.size()
        << " | Texture Coordinates: " << texCoords.size()
        << " | Normals: " << normals.size()
        << " | Faces: " << faces.size() << std::endl;
        std::cout << "Processing data..." << std::endl;
        processData(vertices, texCoords, normals, faces);
        _vao.initializeObj(_vertexData, _texCoordData, _normalData, _indexData);
        _numFaces = faces.size();
    } else {
        std::cerr << "Failed to load OBJ file: " << filePath << std::endl;
    }
}