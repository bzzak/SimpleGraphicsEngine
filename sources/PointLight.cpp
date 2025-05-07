#include "../headers/PointLight.h"
#include "../headers/Mesh.h"

#include <cmath>

Math::float3 PointLight::calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos) const {
    Math::float3 fragPos = vertex.position;

    Math::float3 L = position - fragPos;
    L.normalize();

    float distance = L.len();
    float attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));

    Math::float3 N = vertex.normal;
    N.normalize();

    Math::float3 V = cameraPos - fragPos;
    V.normalize();


    // Diffuse

    float diffuseFactor = std::max(0.0f, N.dot(L));

    // Specular

    Math::float3 R = (-1 * L) - 2 * ((-1 * L).dot(N)) * N;
    R.normalize();

    float specularFactor = std::pow(std::max(0.0f, V.dot(R)), material.shininess);

    // Final components

    Math::float3 ambient = material.diffuse * this->ambient;
    Math::float3 diffuse = material.diffuse * this->diffuse * diffuseFactor;
    Math::float3 specular = material.specular * this->specular * specularFactor;

    // Combine and apply attenuation

    return (ambient + diffuse  + specular) * attenuation;
}
