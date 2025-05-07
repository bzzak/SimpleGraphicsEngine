#ifndef SIMPLERASTERIZER_H
#define SIMPLERASTERIZER_H
#include "Rasterizer.h"

class SimpleRasterizer : public Rasterizer {
    public:
    SimpleRasterizer(int w, int h);
    void triangleFromObj(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) override;
    void triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) override;
    void triangle(Math::Point p1, Math::Point p2, Math::Point p3, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) override;
    //int save() override;
};




#endif //SIMPLERASTERIZER_H
