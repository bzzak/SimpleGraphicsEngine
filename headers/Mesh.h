#ifndef MESH_H
#define MESH_H

#include "../headers/Rasterizer.h"
#include "../headers/Vertex.h"

class Mesh {
protected:
    int vSize;
    int tSize;
    Vertex* vertices;
    Math::Integer3* indices;
    Math::float4x4 currentTransformations;

public:
    Mesh() = default;
    Mesh(int _vSize, int _tSize, Vertex* _vertices, Math::Integer3* _indices) : vSize(_vSize), tSize(_tSize), vertices(_vertices), indices(_indices) {
        currentTransformations.loadIdentity();
    }

     ~Mesh() {
        delete[] vertices;
        delete[] indices;
    }

    Vertex* getVertices() const { return vertices; }
    Math::Integer3* getIndices() const { return indices; }
    int getVertexCount() const { return vSize; }
    int getTriangleCount() const { return tSize; }

    void draw(Rasterizer& rasterizer, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) const;
    void draw(Rasterizer& rasterizer, Math::Integer3 color) const;
    void makeNormals();

    void scale(Rasterizer& rasterizer, Math::float3 s);
    void uniformScale(Rasterizer& rasterizer, float s);
    void translate(Rasterizer& rasterizer, Math::float3 t);
    void rotate(Rasterizer& rasterizer, float angle, Math::float3 axis);

    void setTransformations(Rasterizer& rasterizer) const;
};


#endif //MESH_H
