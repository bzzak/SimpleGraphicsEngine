#include <cmath>

#include "../headers/Sphere.h"
#include "../headers/Vertex.h"
#include "../headers/Math.h"


Sphere::Sphere(int verticalSides, int horizontalSides) : Mesh() {
    if (verticalSides < 3) verticalSides = 3;
    if (horizontalSides < 2) horizontalSides = 2;
    vSize = (horizontalSides  * verticalSides) + 2; // +2 for top and bottom center vertices
    tSize = 2 * (horizontalSides - 1) * verticalSides + 2 * verticalSides;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];
    int indicesCounter = 0;

    currentTransformations.loadIdentity();


    float radius = 0.5f;

    // Generate vertices (excluding poles)
    for (int h = 1; h < horizontalSides; ++h) {
        float theta = M_PI * h / horizontalSides;  // from 0 to PI
        float y = radius * std::cos(theta);
        float r = radius * std::sin(theta);

        for (int v = 0; v < verticalSides; ++v) {
            float phi = 2 * M_PI * v / verticalSides;  // from 0 to 2PI
            float x = r * std::cos(phi);
            float z = r * std::sin(phi);

            vertices[(h-1) * verticalSides + v].position = {x, y, z};
        }
    }

    // Top and bottom poles
    int topIndex = (horizontalSides - 1) * verticalSides;
    vertices[topIndex].position = {0.0f, radius, 0.0f};

    int bottomIndex = topIndex + 1;
    vertices[bottomIndex].position = {0.0f, -radius, 0.0f};

    // Indices for inner quads
    for (int h = 0; h < horizontalSides - 2; ++h) {
        for (int v = 0; v < verticalSides; ++v) {
            int curr = h * verticalSides + v;
            int next = h * verticalSides + (v + 1) % verticalSides;
            int above = (h + 1) * verticalSides + v;
            int aboveNext = (h + 1) * verticalSides + (v + 1) % verticalSides;

            // Two triangles per quad
            indices[indicesCounter++] = Math::Integer3(curr, above, aboveNext);

            indices[indicesCounter++] = Math::Integer3(curr, aboveNext, next);
        }
    }

    // Top cap
    for (int v = 0; v < verticalSides; ++v) {
        int next = (v + 1) % verticalSides;

        indices[indicesCounter++] = Math::Integer3(topIndex, v, next);

    }

    // Bottom cap
    int base = (horizontalSides - 2) * verticalSides;
    for (int v = 0; v < verticalSides; ++v) {
        int curr = base + v;
        int next = base + (v + 1) % verticalSides;

        indices[indicesCounter++] = Math::Integer3(bottomIndex, next, curr);
    }

}