#pragma once
#include <vector>
#include "Face.h"
#include <glm/glm.hpp>

std::vector<glm::vec4> setupVertexArray(const std::vector<glm::vec3>& vertices, const std::vector<Face>& faces)
{
    std::vector<glm::vec4> vertexArray;
    
    // For each face
    for (const auto& face : faces)
    {
        // For each vertex in the face
        for (const auto& vertexIndices : face.vertexIndices)
        {
            // Get the vertex position and normal from the input arrays using the indices from the face
            glm::vec4 vertexPosition(vertices[vertexIndices[0]], 1);

            // Add the vertex position and normal to the vertex array
            vertexArray.push_back(vertexPosition);
        }
    }

    return vertexArray;
}