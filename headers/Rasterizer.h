#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "../headers/Math.h"
#include "../headers/TgaBuffer.h"
#include "../headers/VertexProcessor.h"
#include "../headers/Mesh.h"

class Rasterizer {
protected:
    VertexProcessor vp;
    TgaBuffer buffer;
    float fovy = 45.0f;
    float aspect = 1.0f;
    float near = 0.1f;
    float far = 100.0f;
    Math::float3 eye = {0, 0, 0};
    Math::float3 center = {0, 0, -1};
    Math::float3 up = {0, 1, 0};



public:
    // Constructor and Destructor
    Rasterizer(int w, int h);
    virtual ~Rasterizer() = default;

    // Buffer
    void setBackground(unsigned int r,unsigned int g,unsigned int b, unsigned int a = 255) const;

    // Virtual functions

    virtual void triangleFromObj(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) = 0;
    virtual void triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) = 0;
    virtual void triangle(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) = 0;
    virtual void trianglePhong(Math::Point p1, Math::Point p2, Math::Point p3, Math::float3 normal1, Math::float3 normal2, Math::float3 normal3, const Material& material, const Math::float3& cameraPos, const std::vector<Light*>& lights) = 0;
    virtual int save();

    // Transformations

    void scale(Math::float3 v);
    void uniformScale(float v);
    void translate(Math::float3 v);
    void rotate(float a, Math::float3 v);
    void setTransformations(Math::float4x4 m);
    void resetTransformations();

    // Getters

    float getFovy() const;
    float getAspect() const;
    float getNear() const;
    float getFar() const;
    Math::float3 getEye() const;
    Math::float3 getCenter() const;
    Math::float3 getUp() const;

    // Setters

    void setFovy(float fovy);
    void setAspect(float aspect);
    void setPlanes(float near, float far);
    void setEye(Math::float3 eye);
    void setCenter(Math::float3 center);
    void setUp(Math::float3 up);

    // Set to default values

    void resetView();
    void resetProjection();
};




#endif //RASTERIZER_H
