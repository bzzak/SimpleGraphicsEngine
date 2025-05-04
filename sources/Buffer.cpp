#include "../headers/Buffer.h"

Buffer::Buffer(int w, int h, float _maxDepth) : w(w), h(h), maxDepth(_maxDepth) {
    color = new unsigned int[w * h];
    depth = new float[w * h];

    this->clearColor();
    this->clearDepth();
}

Buffer::~Buffer() {
    delete[] color;
    delete[] depth;
}

void Buffer::setSize(int width, int height) {
    delete[] color;
    delete[] depth;

    w = width;
    h = height;

    color = new unsigned int[w * h];
    depth = new float[w * h];

    this->clearColor();
    this->clearDepth();
}

float Buffer::getMaxDepth() const {
    return maxDepth;
};


void Buffer::setMaxDepth(float depth) {
    this->maxDepth = depth;
}

void Buffer::fillColor(unsigned int r,unsigned int g,unsigned int b, unsigned int a) const {
    for (int i = 0; i < w * h; i++) {
       fillSingleColor(i, r, g, b, a);
    }
}

void Buffer::fillSingleColor(int index, unsigned int r, unsigned int g, unsigned int b, unsigned int a) const {
    color[index] = 0;

    unsigned int rgba[] = { b,g,r,a };
    int shift = 0;
    for (auto c: rgba) {
        if (c > 255) c = 255;
        color[index] |= c << shift;
        shift += 8;
    }
}

float Buffer::getDepth(int index) const {
    return this->depth[index];
};

void Buffer::setDepth(int index, float d) const {
    depth[index] = d;
}

void Buffer::clearColor() const {
    for (int i = 0; i < w * h; i++) color[i] = 0;
}

void Buffer::clearDepth() const {
    for (int i = 0; i < w * h; i++) depth[i] = this->maxDepth;
}
