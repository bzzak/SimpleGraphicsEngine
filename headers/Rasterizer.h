#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "../headers/Math.h"
#include "../headers/TgaBuffer.h"
#include "../headers/VertexProcessor.h"

class Rasterizer {
protected:
    VertexProcessor vp;
    TgaBuffer buffer;
    float fovy = 45.0f;
    float aspect = 1.0f;
    float near = 0.1f;
    float far = 100.0f;

public:
    Rasterizer(int w, int h);
    virtual ~Rasterizer() = default;
    void setBackground(unsigned int r,unsigned int g,unsigned int b, unsigned int a = 255) const;
    virtual void triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, unsigned int r1,unsigned int g1,unsigned int b1, unsigned int r2,unsigned int g2,unsigned int b2, unsigned int r3,unsigned int g3,unsigned int b3) = 0;
    virtual void triangle(Math::Point p1, Math::Point p2, Math::Point p3, unsigned int r1,unsigned int g1,unsigned int b1, unsigned int r2,unsigned int g2,unsigned int b2, unsigned int r3,unsigned int g3,unsigned int b3) = 0;
    virtual int save();

    // Getters

    float getFovy() const;
    float getAspect() const;
    float getNear() const;
    float getFar() const;

    // Setters

    void setFovy(float fovy);
    void setAspect(float aspect);
    void setPlanes(float near, float far);
};




#endif //RASTERIZER_H
