#ifndef VERTEX_H
#define VERTEX_H

#include "../headers/Math.h"

class Vertex {
public:
    Math::float3 position;
    Math::float3 normal;

    Vertex() = default;
    Vertex(Math::float3 _position, Math::float3 _normal) : position(_position), normal(_normal) {}
};


#endif //VERTEX_H
