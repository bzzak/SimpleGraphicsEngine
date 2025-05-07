#include "../headers/Cylinder.h"

#include <cmath>

#include "../headers/Vertex.h"
#include "../headers/Math.h"

Cylinder::Cylinder(int verticalSides, int horizontalSides) : Mesh() {
    if (verticalSides < 3) verticalSides = 3;
    if (horizontalSides < 2) horizontalSides = 2;
    vSize = (horizontalSides  * verticalSides) + 2; // +2 for top and bottom center vertices
    tSize = 2 * (horizontalSides - 1) * verticalSides + 2 * verticalSides;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];
    int indicesCounter = 0;

    currentTransformations.loadIdentity();

    float radius = 0.5f;
    float height = 1.0f;
    float halfHeight = height / 2.0f;

    // Generate side vertices
    for (int h = 0; h < horizontalSides; ++h) {
        float y = -halfHeight + (float(h) / (horizontalSides - 1)) * height;
        for (int v = 0; v < verticalSides; ++v) {

            float angle = 2 * M_PI * v / verticalSides;
            float x = radius * std::cos(angle);
            float z = radius * std::sin(angle);

            vertices[h * verticalSides + v].position = {x, y, z};
        }
    }

    // Generate side indices
    for (int h = 0; h < horizontalSides-1; ++h) {
        for (int v = 0; v < verticalSides; ++v) {
            int curr = h * verticalSides + v;
            int next = h * verticalSides + (v + 1) % verticalSides;
            int currAbove = (h + 1) * verticalSides + v;
            int nextAbove = (h + 1) * verticalSides + (v + 1) % verticalSides;

            // Two triangles per quad
            indices[indicesCounter++] = Math::Integer3(curr, currAbove, nextAbove);
            indices[indicesCounter++] = Math::Integer3(curr, nextAbove, next);
        }
    }

    // Add top center vertex
    int topCenterIndex = horizontalSides * verticalSides;
    vertices[topCenterIndex].position = {0.0f, halfHeight, 0.0f};

    // Top cap
    for (int v = 0; v < verticalSides; ++v) {
        int curr = (horizontalSides - 1) * verticalSides + v;
        int next = (horizontalSides - 1) * verticalSides + (v + 1) % verticalSides;

        indices[indicesCounter++] = Math::Integer3(topCenterIndex, next, curr );
    }

    // Add bottom center vertex
    int bottomCenterIndex = vSize - 1;
    vertices[bottomCenterIndex].position = {0.0f, -halfHeight, 0.0f};

    // Bottom cap
    for (int v = 0; v < verticalSides; ++v) {
        int curr = v;
        int next = (v + 1) % verticalSides;
        indices[indicesCounter++] = Math::Integer3(bottomCenterIndex, curr, next);
    }

}
