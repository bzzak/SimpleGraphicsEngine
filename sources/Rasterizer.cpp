#include "../headers/Rasterizer.h"

// Constructors

Rasterizer::Rasterizer(int w, int h) : buffer(TgaBuffer(w, h)) {
    vp = VertexProcessor();
    vp.setLookAt(eye, center, up);
    vp.setPerspective(fovy, aspect, near, far);
}

// Buffer

void Rasterizer::setBackground(unsigned int r, unsigned int g, unsigned int b, unsigned int a) const {
    buffer.fillColor(r,g,b,a);
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
