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

    vertices[0].position = {0.0f, 0.5f, 0.0f}; // tip of the cone
    int tipIndex = 0;

    // Base circle vertices
    for (int i = 0; i < sides; ++i) {
        float angle = 2 * M_PI * i / sides;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        float y = -0.5f;

        vertices[i+1].position = {x, y, z};
    }

    // center of the base
    int centerIndex = sides + 1;
    vertices[centerIndex].position = {0.0f, -0.5f, 0.0f};

    // Side triangles (tip -> base edge)
    for (int i = 0; i < sides; ++i) {
        int curr = i + 1;
        int next = (i + 1) % sides + 1;
        indices[i] = Math::Integer3(tipIndex, next, curr);
    }

    // Base triangles (center -> base edge)
    for (int i = 0; i < sides; ++i) {
        int curr = i + 1;
        int next = (i + 1) % sides + 1;

        indices[i + sides] = Math::Integer3(centerIndex, curr, next);
    }
}