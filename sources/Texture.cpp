#include "../headers/Texture.h"

#include "../headers/Math.h"
#include "../headers/TGABuffer.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iostream>

Texture::Texture() : width(0), height(0) {}

Texture::~Texture() = default;

bool Texture::loadFromFile(const std::string& filename) {
    std::cout << "Attempting to load texture from: " << filename << std::endl;

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open texture file: " << filename << " (File may not exist or is not accessible)" << std::endl;
        return false;
    }

    // Read TGA header fields directly
    unsigned char idLength;
    unsigned char colorMapType;
    unsigned char imageType;
    unsigned char colorMapSpec[5];  // Color map specification
    unsigned short xOrigin;
    unsigned short yOrigin;
    unsigned short width;
    unsigned short height;
    unsigned char pixelDepth;
    unsigned char imageDescriptor;

    // Read byte fields
    file.read(reinterpret_cast<char*>(&idLength), 1);
    file.read(reinterpret_cast<char*>(&colorMapType), 1);
    file.read(reinterpret_cast<char*>(&imageType), 1);

    // Read color map specification
    file.read(reinterpret_cast<char*>(colorMapSpec), 5);

    // Read short fields
    file.read(reinterpret_cast<char*>(&xOrigin), 2);
    file.read(reinterpret_cast<char*>(&yOrigin), 2);
    file.read(reinterpret_cast<char*>(&width), 2);
    file.read(reinterpret_cast<char*>(&height), 2);

    // Read final byte fields
    file.read(reinterpret_cast<char*>(&pixelDepth), 1);
    file.read(reinterpret_cast<char*>(&imageDescriptor), 1);

    // Debug header values
    std::cout << "TGA Header values:" << std::endl;
    std::cout << "ID Length: " << (int)idLength << std::endl;
    std::cout << "Color Map Type: " << (int)colorMapType << std::endl;
    std::cout << "Image Type: " << (int)imageType << std::endl;
    std::cout << "Color Map Start: " << (colorMapSpec[0] | (colorMapSpec[1] << 8)) << std::endl;
    std::cout << "Color Map Length: " << (colorMapSpec[2] | (colorMapSpec[3] << 8)) << std::endl;
    std::cout << "Color Map Depth: " << (int)colorMapSpec[4] << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Pixel Depth: " << (int)pixelDepth << std::endl;
    std::cout << "Image Descriptor: " << (int)imageDescriptor << std::endl;

    // Validate dimensions
    if (width <= 0 || height <= 0 || width > 4096 || height > 4096) {
        std::cerr << "Invalid texture dimensions in " << filename << ": " << width << "x" << height << std::endl;
        return false;
    }

    // Validate pixel depth and image type
    bool isGrayscale = (imageType == 3);  // Type 3 is grayscale
    if (!isGrayscale && pixelDepth != 24 && pixelDepth != 32) {
        std::cerr << "Unsupported pixel depth in " << filename << ": " << (int)pixelDepth << " (only 24 or 32 bit RGB/RGBA supported)" << std::endl;
        return false;
    }
    if (isGrayscale && pixelDepth != 8) {
        std::cerr << "Unsupported grayscale pixel depth in " << filename << ": " << (int)pixelDepth << " (only 8 bit grayscale supported)" << std::endl;
        return false;
    }

    // Store dimensions
    this->width = width;
    this->height = height;

    // Skip image ID if present
    if (idLength > 0) {
        file.seekg(idLength, std::ios::cur);
    }

    // Skip color map if present
    if (colorMapType == 1) {  // Has color map
        unsigned short colorMapLength = colorMapSpec[2] | (colorMapSpec[3] << 8);
        unsigned char colorMapDepth = colorMapSpec[4];
        unsigned short bytesPerColor = (colorMapDepth + 7) / 8;
        file.seekg(colorMapLength * bytesPerColor, std::ios::cur);
    }

    // Read pixel data
    pixels.resize(width * height);
    unsigned short bytesPerPixel = pixelDepth / 8;

    std::cout << "Reading " << width * height << " pixels with " << bytesPerPixel << " bytes per pixel" << std::endl;

    for (int i = 0; i < width * height; i++) {
        if (isGrayscale) {
            // Read grayscale value
            unsigned char gray;
            if (!file.read(reinterpret_cast<char*>(&gray), 1)) {
                std::cerr << "Failed to read grayscale value at index " << i << std::endl;
                pixels.clear();
                width = height = 0;
                return false;
            }
            // Convert grayscale to RGB (same value for all channels)
            pixels[i] = (gray << 16) | (gray << 8) | gray | (255 << 24);  // Full alpha
        } else {
            unsigned char b = 0, g = 0, r = 0, a = 255;  // Default alpha to 255

            // Read BGR components
            if (bytesPerPixel >= 3) {
                if (!file.read(reinterpret_cast<char*>(&b), 1) ||
                    !file.read(reinterpret_cast<char*>(&g), 1) ||
                    !file.read(reinterpret_cast<char*>(&r), 1)) {
                    std::cerr << "Failed to read RGB components at index " << i << std::endl;
                    pixels.clear();
                    width = height = 0;
                    return false;
                }
            }

            // Read alpha if present
            if (bytesPerPixel == 4) {
                if (!file.read(reinterpret_cast<char*>(&a), 1)) {
                    std::cerr << "Failed to read alpha component at index " << i << std::endl;
                    pixels.clear();
                    width = height = 0;
                    return false;
                }
            }

            // Convert BGR to RGB and store with alpha
            pixels[i] = (r << 16) | (g << 8) | b | (a << 24);
        }
    }

    std::cout << "Successfully loaded texture: " << filename << std::endl;
    return true;
}

unsigned int Texture::getPixel(int x, int y) const {
    x = std::clamp(x, 0, width - 1);
    y = std::clamp(y, 0, height - 1);
    return pixels[y * width + x];
}

Math::float3 Texture::rgbToFloat(unsigned int color) const {
    return Math::float3(
        ((color >> 16) & 0xFF) / 255.0f,
        ((color >> 8) & 0xFF) / 255.0f,
        (color & 0xFF) / 255.0f
    );
}

unsigned int Texture::floatToRgb(const Math::float3& color) const {
    unsigned int r = static_cast<unsigned int>(std::clamp(color.x * 255.0f, 0.0f, 255.0f));
    unsigned int g = static_cast<unsigned int>(std::clamp(color.y * 255.0f, 0.0f, 255.0f));
    unsigned int b = static_cast<unsigned int>(std::clamp(color.z * 255.0f, 0.0f, 255.0f));
    return (r << 16) | (g << 8) | b;
}

unsigned int Texture::sample(float u, float v) const {
    // Wrap texture coordinates
    u = u - std::floor(u);
    v = v - std::floor(v);

    // Convert to pixel coordinates
    int x = static_cast<int>(u * width);
    int y = static_cast<int>(v * height);

    return getPixel(x, y);
}

unsigned int Texture::sampleBilinear(float u, float v) const {
    // Wrap texture coordinates
    u = u - std::floor(u);
    v = v - std::floor(v);

    // Convert to pixel coordinates
    float x = u * width - 0.5f;
    float y = v * height - 0.5f;

    // Get surrounding pixels
    int x0 = static_cast<int>(std::floor(x));
    int y0 = static_cast<int>(std::floor(y));
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Get interpolation weights
    float wx = x - x0;
    float wy = y - y0;

    // Sample surrounding pixels
    unsigned int p00 = getPixel(x0, y0);
    unsigned int p10 = getPixel(x1, y0);
    unsigned int p01 = getPixel(x0, y1);
    unsigned int p11 = getPixel(x1, y1);

    // Extract alpha values
    float a00 = ((p00 >> 24) & 0xFF) / 255.0f;
    float a10 = ((p10 >> 24) & 0xFF) / 255.0f;
    float a01 = ((p01 >> 24) & 0xFF) / 255.0f;
    float a11 = ((p11 >> 24) & 0xFF) / 255.0f;

    // Extract RGB values
    Math::float3 c00 = rgbToFloat(p00);
    Math::float3 c10 = rgbToFloat(p10);
    Math::float3 c01 = rgbToFloat(p01);
    Math::float3 c11 = rgbToFloat(p11);

    // Bilinear interpolation for RGB
    Math::float3 c0 = c00 * (1 - wx) + c10 * wx;
    Math::float3 c1 = c01 * (1 - wx) + c11 * wx;
    Math::float3 final = c0 * (1 - wy) + c1 * wy;

    // Bilinear interpolation for alpha
    float a0 = a00 * (1 - wx) + a10 * wx;
    float a1 = a01 * (1 - wx) + a11 * wx;
    float finalAlpha = a0 * (1 - wy) + a1 * wy;

    // Convert back to RGBA
    unsigned int r = static_cast<unsigned int>(std::clamp(final.x * 255.0f, 0.0f, 255.0f));
    unsigned int g = static_cast<unsigned int>(std::clamp(final.y * 255.0f, 0.0f, 255.0f));
    unsigned int b = static_cast<unsigned int>(std::clamp(final.z * 255.0f, 0.0f, 255.0f));
    unsigned int a = static_cast<unsigned int>(std::clamp(finalAlpha * 255.0f, 0.0f, 255.0f));

    return (a << 24) | (r << 16) | (g << 8) | b;
}
