#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include "Math.h"

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& filename);
    unsigned int sample(float u, float v) const;
    unsigned int sampleBilinear(float u, float v) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::vector<unsigned int> pixels;
    int width;
    int height;

    unsigned int getPixel(int x, int y) const;
    Math::float3 rgbToFloat(unsigned int color) const;
    unsigned int floatToRgb(const Math::float3& color) const;
};

#endif //TEXTURE_H
