#ifndef SIMPLERASTERIZER_H
#define SIMPLERASTERIZER_H
#include "Rasterizer.h"

class SimpleRasterizer : public Rasterizer {
    public:
    SimpleRasterizer(int w, int h);
    void triangleFromObj(Math::Point p1, Math::Point p2, Math::Point p3, unsigned int r1,unsigned int g1,unsigned int b1, unsigned int r2,unsigned int g2,unsigned int b2, unsigned int r3,unsigned int g3,unsigned int b3) override;
    void triangleFromView(Math::Point p1, Math::Point p2, Math::Point p3, unsigned int r1,unsigned int g1,unsigned int b1, unsigned int r2,unsigned int g2,unsigned int b2, unsigned int r3,unsigned int g3,unsigned int b3) override;
    void triangle(Math::Point p1, Math::Point p2, Math::Point p3, unsigned int r1,unsigned int g1,unsigned int b1, unsigned int r2,unsigned int g2,unsigned int b2, unsigned int r3,unsigned int g3,unsigned int b3) override;
    //int save() override;
};




#endif //SIMPLERASTERIZER_H
