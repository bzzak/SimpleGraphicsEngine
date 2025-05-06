#include <iostream>
#include "../headers/Buffer.h"
#include "../headers/TgaBuffer.h"
#include "../headers/Rasterizer.h"
#include "../headers/SimpleRasterizer.h"
#include "../headers/Math.h"
#include "../headers/VertexProcessor.h"


int main() {

    auto simpleRasterizer = SimpleRasterizer(800,600);

    simpleRasterizer.setEye({0.0f, 0.0f, 0.0f});
    simpleRasterizer.setCenter({0.0f, 0.0f, -1.0f});
    simpleRasterizer.setUp({0.0f, 1.0f, 0.0f});

    simpleRasterizer.setFovy(65.0f);
    simpleRasterizer.setAspect(16.0f/9.0f);
    //simpleRasterizer.setAspect(1.0f);
    //simpleRasterizer.setAspect(4.0f/3.0f);
    simpleRasterizer.setPlanes(0.1f, 100.0f);

    // Transformations

    simpleRasterizer.scale({2.0f, 2.0f, 1.0f});
    simpleRasterizer.rotate(90.0f, {0.0f, 0.0f, 1.0f});
    simpleRasterizer.translate({2.0f, 1.0f, 0.0f});


    simpleRasterizer.setBackground(0,0,0);


    simpleRasterizer.triangleFromObj({ 0.0f, 0.41f, -4.0f }, {0.41f, -0.41f, -4.0f}, { -0.41f, -0.41f, -4.0f }, 0, 255, 0, 255, 0, 0, 0, 0, 255);

    simpleRasterizer.resetTransformations();

    simpleRasterizer.scale({15.0f, 15.0f, 1.0f});
    simpleRasterizer.rotate(-45.0f, {0.0f, 0.0f, 1.0f});
    simpleRasterizer.translate({3.0f, 2.0f, -10.0f});

    simpleRasterizer.triangleFromObj({ 0.0f, 0.41f, -4.0f }, {0.41f, -0.41f, -4.0f}, { -0.41f, -0.41f, -4.0f }, 255, 255, 0, 255, 255, 0, 255, 255, 0);

    //simpleRasterizer.triangleFromView({ 0.0f, 0.41f, -4.0f }, {0.41f, -0.41f, -4.0f}, { -0.41f, -0.41f, -4.0f }, 0, 255, 0, 255, 0, 0, 0, 0, 255);

    simpleRasterizer.save();

    return 0;
}



