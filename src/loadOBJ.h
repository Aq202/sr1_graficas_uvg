#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Face.h"
#include <SDL2/SDL.h>


bool loadOBJ(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<Face>& out_faces) {
    std::ifstream file(path);
    if (!file.is_open()) {
        SDL_Log("Error: Could not open file ");

        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            out_vertices.push_back(vertex);
        } else if (keyword == "f") {
            Face face;
            int v1, v2, v3;
            while (iss >> v1) {
                std::array<int, 3> vertexIndices = {v1 - 1, 0, 0}; // OBJ indices are 1-based
                if (iss.peek() == '/') {
                    iss.ignore();
                    if (iss.peek() != '/')
                        iss >> vertexIndices[1];
                    if (iss.peek() == '/') {
                        iss.ignore();
                        iss >> vertexIndices[2];
                    }
                }
                face.vertexIndices.push_back(vertexIndices);
            }
            out_faces.push_back(face);
        }
    }

    return true;
}

void loadModel(){

}