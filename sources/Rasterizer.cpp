#include "../headers/Rasterizer.h"


Rasterizer::Rasterizer(int w, int h) : buffer(TgaBuffer(w, h)) {
}

void Rasterizer::setBackground(unsigned int r, unsigned int g, unsigned int b, unsigned int a) const {
    buffer.fillColor(r,g,b,a);
}

int Rasterizer::save() {
    return buffer.save();
}


