#ifndef SIMPLERASTERIZER_H
#define SIMPLERASTERIZER_H
#include "Rasterizer.h"

class SimpleRasterizer : public Rasterizer {
    public:
    SimpleRasterizer(int w, int h);
    void triangleFromObj(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) override;
    void triangleFromObjPixel(Math::Point p1, Math::Point p2, Math::Point p3, Math::float2 uv1, Math::float2 uv2, Math::float2 uv3) override;
    void triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) override;
    void triangle(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) override;
    void trianglePixel(Math::Point p1, Math::Point p2, Math::Point p3, Math::float2 uv1, Math::float2 uv2, Math::float2 uv3) override;
    void trianglePhong(Math::Point p1, Math::Point p2, Math::Point p3, Math::float3 normal1, Math::float3 normal2, Math::float3 normal3, const Material& material, const Math::float3& cameraPos, const std::vector<Light*>& lights) override;
    void trianglePhong(Math::Point p1, Math::Point p2, Math::Point p3, Math::float3 normal1, Math::float3 normal2, Math::float3 normal3, Math::float2 uv1, Math::float2 uv2, Math::float2 uv3, const Material& material, const Math::float3& cameraPos, const std::vector<Light*>& lights, Texture* texture) override;
    //int save() override;
};




#endif //SIMPLERASTERIZER_H
