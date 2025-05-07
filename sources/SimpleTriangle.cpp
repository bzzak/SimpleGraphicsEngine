#include "../headers/SimpleTriangle.h"
#include "../headers/Vertex.h"
#include "../headers/Math.h"

SimpleTriangle::SimpleTriangle() : Mesh() {
    vSize = 3;
    tSize = 1;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];

    currentTransformations.loadIdentity();

    vertices[0].position = Math::float3(-0.5f, 0.0f, 0.0f);
    vertices[1].position = Math::float3(0.0f, 0.5f, 0.0f);
    vertices[2].position = Math::float3(0.5f, 0.0f, 0.0f);
    indices[0] = Math::Integer3(0, 1, 2);
}

//SimpleTriangle::~SimpleTriangle() {
    //delete[] vertices;
    //[] indices;
//}


