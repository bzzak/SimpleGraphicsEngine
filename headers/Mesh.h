#ifndef MESH_H
#define MESH_H

#include <algorithm>
#include <vector>

#include "../headers/Light.h"
//#include "../headers/Rasterizer.h"
#include "../headers/Vertex.h"
#include "../headers/Texture.h"

class Rasterizer;

struct Material {
    Math::float3 diffuse = {1.0f, 0.0f, 0.0f};
    Math::float3 specular = {0.05f, 0.05f, 0.05f};
    float shininess = 5.0f;
};


class Mesh {
protected:
    int vSize;
    int tSize;
    bool hasTexture = false;
    Texture* texture;
    Material material;
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
        if (texture != nullptr) delete texture;
    }

    bool loadTexture(const std::string& filename);
    void setTexture(const Texture& tex);
    bool enableTexturing() { if (texture != nullptr){hasTexture = true; return true;}  return false; }
    void disableTexturing() { hasTexture = false; }
    bool isTexturingEnabled() const { return hasTexture; }

    Vertex* getVertices() const { return vertices; }
    Math::Integer3* getIndices() const { return indices; }
    int getVertexCount() const { return vSize; }
    int getTriangleCount() const { return tSize; }

    void draw(Rasterizer& rasterizer, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) const;
    void draw(Rasterizer& rasterizer, Math::Integer3 color) const;
    void draw(Rasterizer& rasterizer) const;
    void drawPixel(Rasterizer& rasterizer) const;
    void drawPhong(Rasterizer& rasterizer, const std::vector<Light*>& lights) const;
    void drawPhongPixel(Rasterizer& rasterizer, const std::vector<Light*>& lights) const;

    void makeNormals();

    void scale(Rasterizer& rasterizer, Math::float3 s);
    void uniformScale(Rasterizer& rasterizer, float s);
    void translate(Rasterizer& rasterizer, Math::float3 t);
    void rotate(Rasterizer& rasterizer, float angle, Math::float3 axis);

    void setTransformations(Rasterizer& rasterizer) const;
    void setDiffuseColor(Math::float3 color) { material.diffuse = {std::clamp(color.x, 0.0f, 1.0f), std::clamp(color.y, 0.0f, 1.0f), std::clamp(color.z, 0.0f, 1.0f) }; }
    void setSpecularColor(Math::float3 color) { material.specular = {std::clamp(color.x, 0.0f, 1.0f), std::clamp(color.y, 0.0f, 1.0f), std::clamp(color.z, 0.0f, 1.0f) }; }
    void setShininess(float shininess) { material.shininess = shininess; }
};


#endif //MESH_H
