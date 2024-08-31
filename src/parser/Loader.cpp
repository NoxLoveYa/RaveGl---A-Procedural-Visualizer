/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** Loader.cpp
*/

#include "ObjLoader.hpp"
#include <algorithm>

void ObjLoader::parseVertex(std::istringstream& iss, std::vector<Vertex>& vertices)
{
    Vertex vertex;
    iss >> vertex.x >> vertex.y >> vertex.z;
    vertices.push_back(vertex);
}

void ObjLoader::parseTexCoord(std::istringstream& iss, std::vector<TexCoord>& texCoords)
{
    TexCoord texCoord;
    iss >> texCoord.u >> texCoord.v;
    if (iss.peek() != '\n' && iss.peek() != EOF) {
        iss >> texCoord.w;
    } else {
        texCoord.w = 0.0f; // Default value if w is not provided
    }
    texCoords.push_back(texCoord);
}

void ObjLoader::parseNormal(std::istringstream& iss, std::vector<Normal>& normals)
{
    Normal normal;
    iss >> normal.nx >> normal.ny >> normal.nz;
    normals.push_back(normal);
}

void ObjLoader::parseFaceVertex(const std::string& token, Face& face, int index)
{
    std::stringstream ss(token);
    std::string part;
    int idx = 0;

    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            int value = std::stoi(part) - 1; // OBJ indices are 1-based
            switch (idx) {
                case 0: face.vertexIndices[index] = value; break;
                case 1: face.texCoordIndices[index] = value; break;
                case 2: face.normalIndices[index] = value; break;
            }
        } else {
            // Handle missing indices
            switch (idx) {
                case 0: face.vertexIndices[index] = -1; break;
                case 1: face.texCoordIndices[index] = -1; break;
                case 2: face.normalIndices[index] = -1; break;
            }
        }
        idx++;
    }
}

void ObjLoader::parseFace(const std::string& line, std::vector<Face>& faces)
{
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix; // Skip the 'f' prefix

    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    // Triangulate faces with more than 3 vertices
    for (size_t i = 1; i < tokens.size() - 1; ++i) {
        Face face;
        parseFaceVertex(tokens[0], face, 0);
        parseFaceVertex(tokens[i], face, 1);
        parseFaceVertex(tokens[i + 1], face, 2);
        faces.push_back(face);
    }
}


bool ObjLoader::loadOBJ(const std::string& path, std::vector<Vertex>& vertices, std::vector<TexCoord>& texCoords, std::vector<Normal>& normals, std::vector<Face>& faces) {
    std::ifstream inFile(path);
    if (!inFile) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            parseVertex(iss, vertices);
        }
        else if (prefix == "vt") {
             parseTexCoord(iss, texCoords);
        }
        else if (prefix == "vn") {
            parseNormal(iss, normals);
        }
        else if (prefix == "f") {
            parseFace(line, faces);
        }
    }

    inFile.close();
    return true;
}

void ObjLoader::load_process_save_Obj_Models(const std::string& objPath, const std::string& binPath) {
    std::vector<Vertex> vertices;
    std::vector<TexCoord> texCoords;
    std::vector<Normal> normals;
    std::vector<Face> faces;


    if (loadOBJ(objPath, vertices, texCoords, normals, faces)) {
        std::cout << "Processing model: " << objPath << std::endl;
        Model model;
        model.processData(vertices, texCoords, normals, faces, binPath);

        //Clear
        vertices = std::vector<Vertex>();
        texCoords = std::vector<TexCoord>();
        normals = std::vector<Normal>();
        faces = std::vector<Face>();
        model.clearData();
    } else {
        std::cerr << "Failed to load OBJ file: " << objPath << std::endl;
    }
}

void ObjLoader::prepareObjModels(const std::string& directoryPath) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".obj") {
            std::string objPath = entry.path().string();
            std::filesystem::path binPath = entry.path();
            binPath.replace_extension(".bin");
            if (!std::filesystem::exists(binPath)) {
                load_process_save_Obj_Models(objPath, binPath.string());
            } else {
                std::cout << "Skipping preprocessing for " << objPath << " as " << binPath.string() << " already exists." << std::endl;
            }
        }
    }
    std::cout << "Finished preprocessing all models" << std::endl;
}
