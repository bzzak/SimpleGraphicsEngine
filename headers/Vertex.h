#ifndef VERTEX_H
#define VERTEX_H

#include "../headers/Math.h"

class Vertex {
public:
    Math::float3 position;
    Math::float3 normal;
    Math::float2 uvCoords;

    Vertex() = default;
    Vertex(Math::float3 _position, Math::float3 _normal) : position(_position), normal(_normal) {}
    Vertex(Math::float3 _position, Math::float3 _normal, Math::float2 _uvCoords) : position(_position), normal(_normal), uvCoords(_uvCoords) {}

    void setPosition(Math::float3 _position) {position = _position;}
    void setNormal(Math::float3 _normal) {normal = _normal;}
    void setUVCoords(Math::float2 _uvCoords) {uvCoords = _uvCoords;}
};


#endif //VERTEX_H
