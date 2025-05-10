#include "../headers/SimpleRasterizer.h"
#include "../headers/Buffer.h"

#include <iostream>
#include <ostream>
#include <algorithm>
#include <cmath>


SimpleRasterizer::SimpleRasterizer(int w, int h) : Rasterizer(w, h) {
}

void SimpleRasterizer::triangleFromObj(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) {
    Math::Point p1proj = vp.convertObjToNDC(p1);
    Math::Point p2proj = vp.convertObjToNDC(p2);
    Math::Point p3proj = vp.convertObjToNDC(p3);

    triangle(p1proj, p2proj, p3proj, color1, color2, color3);
}

void SimpleRasterizer::triangleFromObjPixel(Math::Point p1, Math::Point p2, Math::Point p3, Math::float2 uv1, Math::float2 uv2, Math::float2 uv3) {
    Math::Point p1proj = vp.convertObjToNDC(p1);
    Math::Point p2proj = vp.convertObjToNDC(p2);
    Math::Point p3proj = vp.convertObjToNDC(p3);

    trianglePixel(p1proj, p2proj, p3proj, uv1, uv2, uv3);
}

void SimpleRasterizer::triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) {
    Math::Point p1View = vp.convertViewToNDC(p1);
    Math::Point p2View = vp.convertViewToNDC(p2);
    Math::Point p3View = vp.convertViewToNDC(p3);

    triangle(p1View, p2View, p3View, color1, color2, color3);
}

void SimpleRasterizer::triangle(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) {

    const float epsilon = 0.0000000000000000001f;

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
                std::abs(_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x)) <= epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge23 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                std::abs(_dx23 * (y - _p2.y) - _dy23 * (x - _p2.x)) <= epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge31 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                std::abs(_dx31 * (y - _p3.y) - _dy31 * (x - _p3.x)) <= epsilon) ||
                (_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                 _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                 _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon )) {

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

void SimpleRasterizer::trianglePixel(Math::Point p1, Math::Point p2, Math::Point p3, Math::float2 uv1, Math::float2 uv2, Math::float2 uv3) {
    const float epsilon = 0.0000000000000000001f;

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
                std::abs(_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x)) <= epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge23 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                std::abs(_dx23 * (y - _p2.y) - _dy23 * (x - _p2.x)) <= epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge31 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                std::abs(_dx31 * (y - _p3.y) - _dy31 * (x - _p3.x)) <= epsilon) ||
                (_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                 _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                 _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon )) {

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

                float uvX = _b1 * uv1.x + _b2 * uv2.x + _b3 * uv3.x;
                float uvY = _b1 * uv1.y + _b2 * uv2.y + _b3 * uv3.y;

                Math::Integer3 colors = sampleTexture(uvX, uvY);

                float depth = _b1 * _p1.z + _b2 * _p2.z + _b3 * _p3.z;
                int targetIndex = y * buffer.getWidth() + x;

                if (depth < buffer.getDepth(targetIndex)) {
                    buffer.fillSingleColor(targetIndex, colors.x, colors.y, colors.z, 255 );
                    buffer.setDepth(targetIndex, depth);
                 }

            }
        }
    }
}

void SimpleRasterizer::trianglePhong(Math::Point p1, Math::Point p2, Math::Point p3, Math::float3 normal1, Math::float3 normal2, Math::float3 normal3, const Material& material, const Math::float3& cameraPos, const std::vector<Light*>& lights) {

    Vertex vertexWorld1({p1.x,p1.y,p1.z}, normal1);
    vp.convertVertexToWorld(vertexWorld1);
    Vertex vertexWorld2({p2.x,p2.y,p2.z}, normal2);
    vp.convertVertexToWorld(vertexWorld2);
    Vertex vertexWorld3({p3.x,p3.y,p3.z}, normal3);
    vp.convertVertexToWorld(vertexWorld3);

    float dx12View = vertexWorld1.position.x - vertexWorld2.position.x;
    float dx21View = -dx12View;
    float dx23View = vertexWorld2.position.x - vertexWorld3.position.x;
    float dx32View = -dx23View;
    float dx13View = vertexWorld1.position.x - vertexWorld3.position.x;
    float dx31View = -dx13View;
    float dy12View = vertexWorld1.position.y - vertexWorld2.position.y;
    float dy21View = -dy12View;
    float dy23View = vertexWorld2.position.y - vertexWorld3.position.y;
    float dy32View = -dy23View;
    float dy31View = vertexWorld3.position.y - vertexWorld1.position.y;
    float dy13View = -dy31View;

    Math::Point p1proj = vp.convertObjToNDC(p1);
    Math::Point p2proj = vp.convertObjToNDC(p2);
    Math::Point p3proj = vp.convertObjToNDC(p3);

    const float epsilon = 0.0000000000000000001f;

    float minX = std::min({p1proj.x,p2proj.x, p3proj.x});
    float maxX = std::max({p1proj.x,p2proj.x, p3proj.x});
    float minY = std::min({p1proj.y,p2proj.y, p3proj.y});
    float maxY = std::max({p1proj.y,p2proj.y, p3proj.y});

    maxX = std::min(static_cast<int>((maxX + 1) * buffer.getWidth() * .5f), buffer.getWidth());
    maxY = std::min(static_cast<int>((maxY + 1) * buffer.getHeight() * .5f), buffer.getHeight());
    minX = std::max(static_cast<int>((minX + 1) * buffer.getWidth() * .5f), 0);
    minY = std::max(static_cast<int>((minY + 1) * buffer.getHeight() * .5f), 0);

    float dx12 = p1proj.x - p2proj.x;
    float dx21 = -dx12;
    float dx23 = p2proj.x - p3proj.x;
    float dx32 = -dx23;
    float dx13 = p1proj.x - p3proj.x;
    float dx31 = -dx13;
    float dy12 = p1proj.y - p2proj.y;
    float dy21 = -dy12;
    float dy23 = p2proj.y - p3proj.y;
    float dy32 = -dy23;
    float dy31 = p3proj.y - p1proj.y;
    float dy13 = -dy31;

    auto _p1 =  Math::Point(static_cast<int>((p1proj.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p1proj.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p1proj.z + 1) * buffer.getMaxDepth() * .5f));
    auto _p2 =  Math::Point(static_cast<int>((p2proj.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p2proj.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p2proj.z + 1) * buffer.getMaxDepth() * .5f));
    auto _p3 =  Math::Point(static_cast<int>((p3proj.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p3proj.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p3proj.z + 1) * buffer.getMaxDepth() * .5f));

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
                std::abs(_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x)) <= epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge23 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                std::abs(_dx23 * (y - _p2.y) - _dy23 * (x - _p2.x)) <= epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge31 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                std::abs(_dx31 * (y - _p3.y) - _dy31 * (x - _p3.x)) <= epsilon) ||
                (_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                 _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                 _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon )) {


                float _b1 = (_dy23 * (x - _p3.x) + _dx32 * (y - _p3.y)) / (_dy23 * _dx13 + _dx32 * _dy13);
                float _b2 = (_dy31 * (x - _p3.x) + _dx13 * (y - _p3.y)) / (_dy31 * _dx23 + _dx13 * _dy23);
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

                // PHONG here

                Math::float3 resultColor = {0.0f, 0.0f, 0.0f};

                Math::float3 p1Float = { p1.x, p1.y, p1.z };
                Math::float3 p2Float = { p2.x, p2.y, p2.z };
                Math::float3 p3Float = { p3.x, p3.y, p3.z };

                Math::float3 p1World = { vertexWorld1.position.x, vertexWorld1.position.y, vertexWorld1.position.z };
                Math::float3 p2World = { vertexWorld2.position.x, vertexWorld2.position.y, vertexWorld2.position.z };
                Math::float3 p3World = { vertexWorld3.position.x, vertexWorld3.position.y, vertexWorld3.position.z };

                Math::float3 n1World = { vertexWorld1.normal.x, vertexWorld1.normal.y, vertexWorld1.normal.z };
                Math::float3 n2World = { vertexWorld2.normal.x, vertexWorld2.normal.y, vertexWorld2.normal.z };
                Math::float3 n3World = { vertexWorld3.normal.x, vertexWorld3.normal.y, vertexWorld3.normal.z };

                Math::float3 currentFragmentPosition = _b1 * p1World + _b2 * p2World + _b3 * p3World;
                Math::float3 currentFragmentNormal = _b1 * n1World + _b2 * n2World + _b3 * n3World;

                currentFragmentNormal.normalize();

                Vertex fragment(currentFragmentPosition,currentFragmentNormal);

                for (const auto& light : lights) {
                    resultColor += light->calculate(fragment, material, cameraPos);
                }


                resultColor = {
                    std::clamp(resultColor.x, 0.0f, 1.0f),
                    std::clamp(resultColor.y, 0.0f, 1.0f),
                    std::clamp(resultColor.z, 0.0f, 1.0f)
                };


                Math::Integer3 resultColorInt = {
                    static_cast<int>(std::round(resultColor.x * 255.0f)),
                    static_cast<int>(std::round(resultColor.y * 255.0f)),
                    static_cast<int>(std::round(resultColor.z * 255.0f))
                };


                float depth = _b1 * _p1.z + _b2 * _p2.z + _b3 * _p3.z;
                int targetIndex = y * buffer.getWidth() + x;

                if (depth < buffer.getDepth(targetIndex)) {
                    buffer.fillSingleColor(targetIndex, resultColorInt.x, resultColorInt.y, resultColorInt.z, 255 );
                    buffer.setDepth(targetIndex, depth);
                 }
            }
        }
    }
}

void SimpleRasterizer::trianglePhong(Math::Point p1, Math::Point p2, Math::Point p3, Math::float3 normal1, Math::float3 normal2, Math::float3 normal3, Math::float2 uv1, Math::float2 uv2, Math::float2 uv3, const Material& material, const Math::float3& cameraPos, const std::vector<Light*>& lights, Texture* texture) {
    activeTexture = texture;

    Vertex vertexWorld1({p1.x,p1.y,p1.z}, normal1, uv1);
    vp.convertVertexToWorld(vertexWorld1);
    Vertex vertexWorld2({p2.x,p2.y,p2.z}, normal2, uv2);
    vp.convertVertexToWorld(vertexWorld2);
    Vertex vertexWorld3({p3.x,p3.y,p3.z}, normal3, uv3);
    vp.convertVertexToWorld(vertexWorld3);

    float dx12View = vertexWorld1.position.x - vertexWorld2.position.x;
    float dx21View = -dx12View;
    float dx23View = vertexWorld2.position.x - vertexWorld3.position.x;
    float dx32View = -dx23View;
    float dx13View = vertexWorld1.position.x - vertexWorld3.position.x;
    float dx31View = -dx13View;
    float dy12View = vertexWorld1.position.y - vertexWorld2.position.y;
    float dy21View = -dy12View;
    float dy23View = vertexWorld2.position.y - vertexWorld3.position.y;
    float dy32View = -dy23View;
    float dy31View = vertexWorld3.position.y - vertexWorld1.position.y;
    float dy13View = -dy31View;



    Math::Point p1proj = vp.convertObjToNDC(p1);
    Math::Point p2proj = vp.convertObjToNDC(p2);
    Math::Point p3proj = vp.convertObjToNDC(p3);

    const float epsilon = 0.0000000000000000001f;

    float minX = std::min({p1proj.x,p2proj.x, p3proj.x});
    float maxX = std::max({p1proj.x,p2proj.x, p3proj.x});
    float minY = std::min({p1proj.y,p2proj.y, p3proj.y});
    float maxY = std::max({p1proj.y,p2proj.y, p3proj.y});

    maxX = std::min(static_cast<int>((maxX + 1) * buffer.getWidth() * .5f), buffer.getWidth());
    maxY = std::min(static_cast<int>((maxY + 1) * buffer.getHeight() * .5f), buffer.getHeight());
    minX = std::max(static_cast<int>((minX + 1) * buffer.getWidth() * .5f), 0);
    minY = std::max(static_cast<int>((minY + 1) * buffer.getHeight() * .5f), 0);

    float dx12 = p1proj.x - p2proj.x;
    float dx21 = -dx12;
    float dx23 = p2proj.x - p3proj.x;
    float dx32 = -dx23;
    float dx13 = p1proj.x - p3proj.x;
    float dx31 = -dx13;
    float dy12 = p1proj.y - p2proj.y;
    float dy21 = -dy12;
    float dy23 = p2proj.y - p3proj.y;
    float dy32 = -dy23;
    float dy31 = p3proj.y - p1proj.y;
    float dy13 = -dy31;

    auto _p1 =  Math::Point(static_cast<int>((p1proj.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p1proj.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p1proj.z + 1) * buffer.getMaxDepth() * .5f));
    auto _p2 =  Math::Point(static_cast<int>((p2proj.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p2proj.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p2proj.z + 1) * buffer.getMaxDepth() * .5f));
    auto _p3 =  Math::Point(static_cast<int>((p3proj.x + 1) * buffer.getWidth() * .5f), static_cast<int>((p3proj.y + 1) * buffer.getHeight() * .5f), static_cast<int>((p3proj.z + 1) * buffer.getMaxDepth() * .5f));

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
                std::abs(_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x)) <= epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge23 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                std::abs(_dx23 * (y - _p2.y) - _dy23 * (x - _p2.x)) <= epsilon &&
                _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon) ||
                (isTopLeftEdge31 &&
                _dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                std::abs(_dx31 * (y - _p3.y) - _dy31 * (x - _p3.x)) <= epsilon) ||
                (_dx12 * (y - _p1.y) - _dy12 * (x - _p1.x) >= -epsilon &&
                 _dx23 * (y - _p2.y) - _dy23 * (x - _p2.x) >= -epsilon &&
                 _dx31 * (y - _p3.y) - _dy31 * (x - _p3.x) >= -epsilon )) {

                int targetIndex = y * buffer.getWidth() + x;

                float _b1 = (_dy23 * (x - _p3.x) + _dx32 * (y - _p3.y)) / (_dy23 * _dx13 + _dx32 * _dy13);
                float _b2 = (_dy31 * (x - _p3.x) + _dx13 * (y - _p3.y)) / (_dy31 * _dx23 + _dx13 * _dy23);
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

                // PHONG here

                Math::float3 resultColor = {0.0f, 0.0f, 0.0f};

                Math::float3 p1Float = { p1.x, p1.y, p1.z };
                Math::float3 p2Float = { p2.x, p2.y, p2.z };
                Math::float3 p3Float = { p3.x, p3.y, p3.z };

                Math::float3 p1World = { vertexWorld1.position.x, vertexWorld1.position.y, vertexWorld1.position.z };
                Math::float3 p2World = { vertexWorld2.position.x, vertexWorld2.position.y, vertexWorld2.position.z };
                Math::float3 p3World = { vertexWorld3.position.x, vertexWorld3.position.y, vertexWorld3.position.z };

                Math::float3 n1World = { vertexWorld1.normal.x, vertexWorld1.normal.y, vertexWorld1.normal.z };
                Math::float3 n2World = { vertexWorld2.normal.x, vertexWorld2.normal.y, vertexWorld2.normal.z };
                Math::float3 n3World = { vertexWorld3.normal.x, vertexWorld3.normal.y, vertexWorld3.normal.z };

                Math::float3 currentFragmentPosition = _b1 * p1World + _b2 * p2World + _b3 * p3World;
                Math::float3 currentFragmentNormal = _b1 * n1World + _b2 * n2World + _b3 * n3World;
                Math::float2 currentFragmentUV = _b1 * uv1 + _b2 * uv2 + _b3 * uv3;

                currentFragmentNormal.normalize();

                Vertex fragment(currentFragmentPosition,currentFragmentNormal, currentFragmentUV);

                for (const auto& light : lights) {
                    if (texturingEnabled && activeTexture != nullptr) {
                        activeTexture = texture;
                        resultColor += light->calculate(fragment, material, cameraPos, *this);
                    }
                    else {
                        resultColor += light->calculate(fragment, material, cameraPos);
                    }
                }


                resultColor = {
                    std::clamp(resultColor.x, 0.0f, 1.0f),
                    std::clamp(resultColor.y, 0.0f, 1.0f),
                    std::clamp(resultColor.z, 0.0f, 1.0f)
                };


                Math::Integer3 resultColorInt = {
                    static_cast<int>(std::round(resultColor.x * 255.0f)),
                    static_cast<int>(std::round(resultColor.y * 255.0f)),
                    static_cast<int>(std::round(resultColor.z * 255.0f))
                };


                float depth = _b1 * _p1.z + _b2 * _p2.z + _b3 * _p3.z;


                if (depth < buffer.getDepth(targetIndex)) {
                    buffer.fillSingleColor(targetIndex, resultColorInt.x, resultColorInt.y, resultColorInt.z, 255 );
                    buffer.setDepth(targetIndex, depth);
                 }
            }
        }
    }
}



//int SimpleRasterizer::save() {
  // return Rasterizer::save();
//}
