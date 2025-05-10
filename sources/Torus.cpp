#include <cmath>

#include "../headers/Torus.h"

#include <iostream>

#include "../headers/Vertex.h"
#include "../headers/Math.h"


Torus::Torus(int verticalSides, int horizontalSides) : Mesh() {
    if (verticalSides < 3) verticalSides = 3;
    if (horizontalSides < 2) horizontalSides = 2;
    vSize = (horizontalSides  * verticalSides) + 2; // +2 for top and bottom center vertices
    tSize = 2 * (horizontalSides - 1) * verticalSides + 2 * verticalSides;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];
    int indicesCounter = 0;

    currentTransformations.loadIdentity();

    float R = 0.35f;  // Major radius
    float r = 0.15f;  // Minor radius

    // Generate vertices
    for (int i = 0; i < verticalSides; ++i) {
        float u = 2 * M_PI * i / verticalSides;
        float cosU = std::cos(u);
        float sinU = std::sin(u);

        for (int j = 0; j < horizontalSides; ++j) {
            float v = 2 * M_PI * j / horizontalSides;
            float cosV = std::cos(v);
            float sinV = std::sin(v);

            float x = (R + r * cosV) * cosU;
            float y = r * sinV;
            float z = (R + r * cosV) * sinU;

            vertices[i * verticalSides + j].position = {x, y, z};


            // Calculate UV coordinates
            float uCoord = static_cast<float>(i) / verticalSides;
            float vCoord = static_cast<float>(j) / horizontalSides;
            vertices[i * horizontalSides + j].uvCoords = {uCoord, vCoord};
        }
    }

    // Generate indices
    for (int i = 0; i < verticalSides; ++i) {
        for (int j = 0; j < horizontalSides; ++j) {
            int current = i * horizontalSides + j;
            int nextJ = (j + 1) % horizontalSides;
            int nextI = (i + 1) % verticalSides;

            int nextRow = nextI * horizontalSides + j;
            int diag = nextI * horizontalSides + nextJ;
            int next = i * horizontalSides + nextJ;

            // Two triangles per quad
            indices[indicesCounter++] = Math::Integer3(current, nextRow, diag);

            indices[indicesCounter++] = Math::Integer3(current, diag, next);
        }
    }


    //std::cout << "Vertex Numbers: " << vSize << std::endl;
    //for (int i = 0; i < tSize; i++) {
    //    std::cout << i << " : " << indices[i].x << ", " << indices[i].y << ", " << indices[i].z << std::endl;

    //}

}