#include "../headers/SimpleRasterizer.h"
#include <iostream>
#include <ostream>
#include <algorithm>

#include "../headers/Buffer.h"




SimpleRasterizer::SimpleRasterizer(int w, int h) : Rasterizer(w, h) {
}

void SimpleRasterizer::triangle(Math::Point p1, Math::Point p2, Math::Point p3, unsigned int r1,unsigned int g1,unsigned int b1, unsigned int r2,unsigned int g2,unsigned int b2, unsigned int r3,unsigned int g3,unsigned int b3) {

    float minX = std::min({p1.x,p2.x, p3.x});
    float maxX = std::max({p1.x,p2.x, p3.x});
    float minY = std::min({p1.y,p2.y, p3.y});
    float maxY = std::max({p1.y,p2.y, p3.y});

    maxX = std::min(static_cast<int>((maxX + 1) * buffer.getWidth() * .5f), buffer.getWidth());
    maxY = std::min(static_cast<int>((maxY + 1) * buffer.getHeight() * .5f), buffer.getHeight());
    minX = std::max(static_cast<int>((minX + 1) * buffer.getWidth() * .5f), 0);
    minY = std::max(static_cast<int>((minY + 1) * buffer.getHeight() * .5f), 0);

    float dx12 = p1.x - p2.x;
    float dx21 = -dx12;
    float dx23 = p2.x - p3.x;
    float dx32 = -dx23;
    float dx13 = p1.x - p3.x;
    float dx31 = -dx13;
    float dy12 = p1.y - p2.y;
    float dy21 = -dy12;
    float dy23 = p2.y - p3.y;
    float dy32 = -dy23;
    float dy31 = p3.y - p1.y;
    float dy13 = -dy31;

    auto _p1 =  Math::Point(static_cast<int>((p1.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p1.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p1.z + 1) * buffer.getMaxDepth() * .5f));
    auto _p2 =  Math::Point(static_cast<int>((p2.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p2.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p2.z + 1) * buffer.getMaxDepth() * .5f));
    auto _p3 =  Math::Point(static_cast<int>((p3.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p3.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p3.z + 1) * buffer.getMaxDepth() * .5f));

    float _dx12 = _p1.x - _p2.x;
    float _dx21 = -_dx12;
    float _dx23 = _p2.x - _p3.x;
    float _dx32 = -_dx23;
    float _dx13 = _p1.x - _p3.x;
    float _dx31 = -_dx13;
    float _dy12 = _p1.y - _p2.y;
    float _dy21 = -_dy12;
    float _dy23 = _p2.y - _p3.y;
    float _dy32 = -_dy23;
    float _dy31 = _p3.y - _p1.y;
    float _dy13 = -_dy31;

    bool isTopLeftEdge12 = false;
    bool isTopLeftEdge23 = false;
    bool isTopLeftEdge31 = false;

    if (_dy12 < 0 || (_dy12 == 0 && _dx12 >0)) isTopLeftEdge12 = true;
    if (_dy23 < 0 || (_dy23 == 0 && _dx23 >0)) isTopLeftEdge23 = true;
    if (_dy31 < 0 || (_dy31 == 0 && _dx31 >0)) isTopLeftEdge31 = true;

    for (int x = minX; x < maxX; x++) {
        for (int y = minY; y < maxY; y++) {

            if ((isTopLeftEdge12 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) == 0 &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) > 0 &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) > 0) ||
                (isTopLeftEdge23 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) > 0 &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) == 0 &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) > 0) ||
                (isTopLeftEdge31 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) > 0 &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) > 0 &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) == 0) ||
                (_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) > 0 &&
                 _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) > 0 &&
                 _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) > 0 )) {

                float xNorm = 2.0f * (x / static_cast<float>(buffer.getWidth())) - 1.0f;
                float yNorm = 2.0f * (y / static_cast<float>(buffer.getHeight())) - 1.0f;

                float _b1 = (dy23 * (xNorm - p3.x) + dx32 * (yNorm - p3.y)) / (dy23 * dx13 + dx32 * dy13);
                float _b2 = (dy31 * (xNorm - p3.x) + dx13 * (yNorm - p3.y)) / (dy31 * dx23 + dx13 * dy23);
                float _b3 = 1 - _b1 - _b2;

                float R = _b1 * r1+ _b2 * r2 + _b3 * r3;
                float G = _b1 * g1+ _b2 * g2 + _b3 * g3;
                float B = _b1 * b1+ _b2 * b2 + _b3 * b3;

                float depth = _b1 * _p1.z + _b2 * _p2.z + _b3 * _p3.z;
                int targetIndex = y * buffer.getWidth() + x;

                if (depth < buffer.getDepth(targetIndex)) {
                    buffer.fillSingleColor(targetIndex, R, G, B, 255 );
                    buffer.setDepth(targetIndex, depth);
                 }

            }
        }
    }
}

//int SimpleRasterizer::save() {
  // return Rasterizer::save();
//}
