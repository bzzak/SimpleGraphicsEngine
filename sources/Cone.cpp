#include "../headers/Cone.h"

#include <cmath>

#include "../headers/Vertex.h"
#include "../headers/Math.h"


Cone::Cone(int sides) : Mesh() {
    if (sides < 3) sides = 3;
    vSize = sides + 2;
    tSize = sides * 2;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];

    currentTransformations.loadIdentity();

    float radius = 0.5f;
    float height = 1.0f;

    // Cone tip
    vertices[0].position = {0.0f, 0.5f, 0.0f}; // tip of the cone
    vertices[0].uvCoords = {0.5f, 0.0f};       // center of upper edge
    int tipIndex = 0;

    // Base circle vertices
    for (int i = 0; i < sides; ++i) {
        float angle = 2 * M_PI * i / sides;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        float y = -0.5f;

        vertices[i + 1].position = {x, y, z};
        vertices[i + 1].uvCoords = {0.5f + 0.5f * std::cos(angle), 0.5f + 0.5f * std::sin(angle)}; // mapowanie kołowe
    }

    // Center of the base
    int centerIndex = sides + 1;
    vertices[centerIndex].position = {0.0f, -0.5f, 0.0f};
    vertices[centerIndex].uvCoords = {0.5f, 0.5f}; // center of a texture

    // Side triangles (tip -> base edge)
    for (int i = 0; i < sides; ++i) {
        int curr = i + 1;
        int next = (i + 1) % sides + 1;

        if (tipIndex >= 0 && tipIndex < vSize && curr >= 0 && curr < vSize && next >= 0 && next < vSize) {
            indices[i] = Math::Integer3(tipIndex, next, curr);
        }
    }

    // Base triangles (center -> base edge)
    for (int i = 0; i < sides; ++i) {
        int curr = i + 1;
        int next = (i + 1) % sides + 1;

        if (centerIndex >= 0 && centerIndex < vSize && curr >= 0 && curr < vSize && next >= 0 && next < vSize) {
            indices[i + sides] = Math::Integer3(centerIndex, curr, next);
        }
    }
}