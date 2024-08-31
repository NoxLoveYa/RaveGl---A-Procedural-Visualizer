#ifndef ObjLOADER_H
#define ObjLOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>
#include <filesystem>

#include "ILoader.hpp"
#include "ObjStructs.hpp"


class ObjLoader : public ILoader {
    public:
        bool loadOBJ(const std::string& path, std::vector<Vertex>& vertices, std::vector<TexCoord>& texCoords, std::vector<Normal>& normals, std::vector<Face>& faces);
        void prepareObjModels(const std::string& directoryPath);
    private:
        void load_process_save_Obj_Models(const std::string& objPath, const std::string& binPath);
        void parseVertex(std::istringstream& iss, std::vector<Vertex>& vertices);
        void parseTexCoord(std::istringstream& iss, std::vector<TexCoord>& texCoords);
        void parseNormal(std::istringstream& iss, std::vector<Normal>& normals);
        //void parseFaces1(std::istringstream& iss, std::vector<Face>& faces);
        void parseFace(const std::string& line, std::vector<Face>& faces);
        //void clearLoader();
        void parseFaceVertex(const std::string& token, Face& face, int index);

};

#endif // LOADER_H