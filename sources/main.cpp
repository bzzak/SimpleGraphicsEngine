#include <iostream>
#include "../headers/Buffer.h"
#include "../headers/TgaBuffer.h"
#include "../headers/Rasterizer.h"
#include "../headers/SimpleRasterizer.h"
#include "../headers/Math.h"
#include "../headers/VertexProcessor.h"


int main() {

    auto simpleRasterizer = SimpleRasterizer(800,600);

    simpleRasterizer.setFovy(65.0f);
    simpleRasterizer.setAspect(16.0f/9.0f);
    simpleRasterizer.setPlanes(0.1f, 100.0f);

    simpleRasterizer.setBackground(0,0,0);

    simpleRasterizer.triangleFromView({ 0.0f, 0.41f, -4.0f }, {0.41f, -0.41f, -4.0f}, { -0.41f, -0.41f, -4.0f }, 0, 255, 0, 255, 0, 0, 0, 0, 255);

    simpleRasterizer.save();

    return 0;
}



