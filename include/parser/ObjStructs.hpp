/*
** EPITECH PROJECT, 2024
** RaveGl---A-Procedural-Visualizer
** File description:
** ObjStructs.hpp
*/

#pragma once

#include <array>

struct Vertex {
    float x, y, z;
};

struct TexCoord {
    float u, v, w;
};

struct Normal {
    float nx, ny, nz;
};

struct Face {
    std::array<int, 3> vertexIndices;
    std::array<int, 3> texCoordIndices;
    std::array<int, 3> normalIndices;
};