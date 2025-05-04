#include <iostream>
#include "../headers/Buffer.h"
#include "../headers/TgaBuffer.h"
#include "../headers/Rasterizer.h"
#include "../headers/SimpleRasterizer.h"


int main() {


    auto simpleRasterizer = SimpleRasterizer(600,800);

    simpleRasterizer.setBackground(0,0,0);

    simpleRasterizer.triangle(Math::Point(0.0f,1.0f), Math::Point(1.5f,0.0f), Math::Point(-0.5f,0.0f), 0, 255, 0, 255, 0, 0, 0, 0, 255);
    simpleRasterizer.triangle(Math::Point(0.0f,1.0f), Math::Point(-0.5f,0.0f), Math::Point(-0.7f,0.5f), 255, 0, 255, 255, 255, 0, 0, 255, 255);
    simpleRasterizer.triangle(Math::Point(-0.5f,-0.5f, 0.5f), Math::Point(0.0f,0.5f, -0.2f), Math::Point(0.5f,-0.5f, 0.5f), 255, 0, 0, 255, 0, 0, 255, 0, 0);


    simpleRasterizer.save();

    return 0;
}



