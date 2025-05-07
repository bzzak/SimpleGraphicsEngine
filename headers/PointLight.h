#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
private:
    Math::float3 position;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

public:
    explicit PointLight(Math::float3 _position) : position(_position) {}
    ~PointLight() override = default;

    Math::float3 calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos) const override;

    void setConstant(float c) { constant = c; }
    void setLinear(float l) { linear = l; }
    void setQuadratic(float q) { quadratic = q; }
};

#endif //POINTLIGHT_H
