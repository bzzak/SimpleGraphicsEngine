#ifndef LIGHT_H
#define LIGHT_H

#include <algorithm>
#include "Math.h"
#include "Vertex.h"

struct Material;

class Light {
protected:
    Math::float3 ambient = {0.2f, 0.2f, 0.2f};
    Math::float3 diffuse = {0.8f, 0.8f, 0.8f};
    Math::float3 specular = {1.0f, 1.0f, 1.0f};

public:

    virtual ~Light() = default;
    virtual Math::float3 calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos) const = 0;

    void setAmbientColor(Math::float3 color) { ambient = {std::clamp(color.x, 0.0f, 1.0f), std::clamp(color.y, 0.0f, 1.0f), std::clamp(color.z, 0.0f, 1.0f) }; }
    void setDiffuseColor(Math::float3 color) { diffuse = {std::clamp(color.x, 0.0f, 1.0f), std::clamp(color.y, 0.0f, 1.0f), std::clamp(color.z, 0.0f, 1.0f) }; }
    void setSpecularColor(Math::float3 color) { specular = {std::clamp(color.x, 0.0f, 1.0f), std::clamp(color.y, 0.0f, 1.0f), std::clamp(color.z, 0.0f, 1.0f) }; }
};

#endif //LIGHT_H
