#include "../headers/Cube.h"
#include "../headers/Vertex.h"
#include "../headers/Math.h"

Cube::Cube() : Mesh() {
    vSize = 8;
    tSize = 12;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];

    currentTransformations.loadIdentity();

    vertices[0].position = Math::float3(-0.5f, -0.5f, -0.5f);
    vertices[1].position = Math::float3( 0.5f, -0.5f, -0.5f);
    vertices[2].position = Math::float3(0.5f,  0.5f, -0.5f);
    vertices[3].position = Math::float3(-0.5f,  0.5f, -0.5f);
    vertices[4].position = Math::float3(-0.5f, -0.5f,  0.5f);
    vertices[5].position = Math::float3(0.5f, -0.5f,  0.5f);
    vertices[6].position = Math::float3(0.5f,  0.5f,  0.5f);
    vertices[7].position = Math::float3(-0.5f,  0.5f,  0.5f);

    indices[0] = Math::Integer3(0, 1, 2);
    indices[1] = Math::Integer3(0, 2, 3);
    indices[2] = Math::Integer3(4, 6, 5);
    indices[3] = Math::Integer3(4, 7, 6);
    indices[4] = Math::Integer3(0, 3, 7);
    indices[5] = Math::Integer3(0, 7, 4);
    indices[6] = Math::Integer3(1, 5, 6);
    indices[7] = Math::Integer3(1, 6, 2);
    indices[8] = Math::Integer3(3, 2, 6);
    indices[9] = Math::Integer3( 3, 6, 7);
    indices[10] = Math::Integer3(0, 4, 5);
    indices[11] = Math::Integer3(0, 5, 1);
}
