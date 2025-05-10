#include "../headers/Rasterizer.h"

#include <cmath>
#include <iostream>

// Constructors

Rasterizer::Rasterizer(int w, int h) : buffer(TgaBuffer(w, h)) {
    vp = VertexProcessor();
    vp.setLookAt(eye, center, up);
    vp.setPerspective(fovy, aspect, near, far);
}

// Buffer

float Rasterizer::wrapCoords(float coord) const {
    if (coord < 0.0f) {
        coord = 1.0f - (std::fmod(-coord, 1.0f));
    }
    return std::fmod(coord, 1.0f);
}

void Rasterizer::setBackground(unsigned int r, unsigned int g, unsigned int b, unsigned int a) const {
    buffer.fillColor(r,g,b,a);
}

Math::Integer3 Rasterizer::sampleTexture(float u, float v) const {
    // Return transparent black if texturing is disabled or no active texture
    if (!texturingEnabled || !activeTexture) {

        return {0, 0, 0};
    }

    // Validate texture dimensions
    if (activeTexture->getWidth() <= 0 || activeTexture->getHeight() <= 0) {
        std::cerr << "Invalid texture dimensions" << std::endl;
        return {0, 0, 0};
    }

    // Wrap texture coordinates
    u = wrapCoords(u);
    v = wrapCoords(v);

    // Sample texture with error handling
    try {
        unsigned int texColor = activeTexture->sampleBilinear(u, v);
        // If the sampled color is fully transparent, return transparent black
        if ((texColor >> 24) == 0) {
            return {0,0,0};
        }

        Math::Integer3 texColorInt3 = {0, 0, 0};

        texColorInt3.x = (texColor >> 16) & 0xFF;
        texColorInt3.y = (texColor >> 8) & 0xFF;
        texColorInt3.z = texColor & 0xFF;

        return texColorInt3;
    } catch (const std::exception& e) {
        std::cerr << "Error sampling texture: " << e.what() << std::endl;
        return {0,0,0};
    }
}



int Rasterizer::save() {
    return buffer.save();
}

// Transformations

void Rasterizer::scale(Math::float3 v) {
    vp.multByScale(v);
}
void Rasterizer::uniformScale(float v) {
    vp.multByUniformScale(v);
}
void Rasterizer::translate(Math::float3 v) {
    vp.multByTranslation(v);
}
void Rasterizer::rotate(float a, Math::float3 v) {
    vp.multByRotation(a, v);
}

void Rasterizer::setTransformations(Math::float4x4 m) {
    vp.setObjectToWorld(m);
}
void Rasterizer::resetTransformations() {
    vp.resetTransformations();
}


// Getters

float Rasterizer::getFovy() const {
    return fovy;
}

float Rasterizer::getAspect() const {
    return aspect;
}

float Rasterizer::getNear() const {
    return near;
}

float Rasterizer::getFar() const {
    return far;
}

Math::float3 Rasterizer::getEye() const {
    return eye;
}

Math::float3 Rasterizer::getCenter() const {
    return center;
}

Math::float3 Rasterizer::getUp() const {
    return up;
}


// Setters

void Rasterizer::setFovy(float fovy) {
    this->fovy = fovy;
    vp.setPerspective(fovy, aspect, near, far);
}

void Rasterizer::setAspect(float aspect) {
    this->aspect = aspect;
    vp.setPerspective(fovy, aspect, near, far);
}

void Rasterizer::setPlanes(float near, float far) {
    this->near = near;
    this->far = far;
    vp.setPerspective(fovy, aspect, near, far);
}

void Rasterizer::setEye(Math::float3 eye) {
    this->eye = eye;
    vp.setLookAt(eye, center, up);
}

void Rasterizer::setCenter(Math::float3 center) {
    this->center = center;
    vp.setLookAt(eye, center, up);
}

void Rasterizer::setUp(Math::float3 up) {
    this->up = up;
    vp.setLookAt(eye, center, up);
}

// Set to default values

void Rasterizer::resetView() {
    eye = {0, 0, 0};
    center = {0, 0, -1};
    up = {0, 1, 0};
}

void Rasterizer::resetProjection() {
    fovy = 45.0f;
    aspect = 1.0f;
    near = 0.1f;
    far = 100.0f;
}
