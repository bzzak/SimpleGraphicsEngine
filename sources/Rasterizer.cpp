#include "../headers/Rasterizer.h"


Rasterizer::Rasterizer(int w, int h) : buffer(TgaBuffer(w, h)) {
    vp = VertexProcessor();
    vp.setPerspective(fovy, aspect, near, far);
}

void Rasterizer::setBackground(unsigned int r, unsigned int g, unsigned int b, unsigned int a) const {
    buffer.fillColor(r,g,b,a);
}

int Rasterizer::save() {
    return buffer.save();
}

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

