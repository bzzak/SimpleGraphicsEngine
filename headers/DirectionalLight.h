#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
private:
    Math::float3 direction;
public:
    explicit DirectionalLight(Math::float3 _direction) : direction(_direction) {direction.normalize();}
    ~DirectionalLight() override = default;

    Math::float3 calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos) const override;
    Math::float3 calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos, const Rasterizer& rasterizer) const override;
};

#endif //DIRECTIONALLIGHT_H
