#include "../headers/SimpleRasterizer.h"
#include "../headers/Buffer.h"

#include <iostream>
#include <ostream>
#include <algorithm>






SimpleRasterizer::SimpleRasterizer(int w, int h) : Rasterizer(w, h) {
}

void SimpleRasterizer::triangleFromObj(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) {
    Math::Point p1View = vp.convertObjToNDC(p1);
    Math::Point p2View = vp.convertObjToNDC(p2);
    Math::Point p3View = vp.convertObjToNDC(p3);

    triangle(p1View, p2View, p3View, color1, color2, color3);
}
void SimpleRasterizer::triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) {
    Math::Point p1View = vp.convertViewToNDC(p1);
    Math::Point p2View = vp.convertViewToNDC(p2);
    Math::Point p3View = vp.convertViewToNDC(p3);

    triangle(p1View, p2View, p3View, color1, color2, color3);
}

void SimpleRasterizer::triangle(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) {

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

                _b1 = std::clamp(_b1, 0.0f, 1.0f);
                _b2 = std::clamp(_b2, 0.0f, 1.0f);
                _b3 = std::clamp(_b3, 0.0f, 1.0f);

                // Sum normalization:
                float sum = _b1 + _b2 + _b3;
                if (sum > 0.0f) {
                    _b1 /= sum;
                    _b2 /= sum;
                    _b3 /= sum;
                }


                float R = _b1 * color1.x + _b2 * color2.x + _b3 * color3.x;
                float G = _b1 * color1.y + _b2 * color2.y + _b3 * color3.y;
                float B = _b1 * color1.z + _b2 * color2.z + _b3 * color3.z;

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
