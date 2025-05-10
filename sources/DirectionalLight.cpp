#include "../headers/DirectionalLight.h"
#include "../headers/Mesh.h"
#include "../headers/Rasterizer.h"

#include <cmath>


Math::float3 DirectionalLight::calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos) const {
    Math::float3 N = vertex.normal;
    N.normalize();
    Math::float3 fragPos = vertex.position;
    Math::float3 V = cameraPos - fragPos;
    V.normalize();
    Math::float3 L = -1 * direction;
    L.normalize();

    // Diffuse

    float diffuseFactor = std::max(0.0f, N.dot(L));

    // Specular

    Math::float3 R = (-1 * L) - 2 * ((-1 * L).dot(N)) * N;
    R.normalize();

    float specularFactor = std::pow(std::max(0.0f, V.dot(R)), material.shininess);

    // Combine components

    Math::float3 ambient = material.diffuse * this->ambient;
    Math::float3 diffuse = material.diffuse * this->diffuse * diffuseFactor;
    Math::float3 specular = material.specular * this->specular * specularFactor;

    return ambient + diffuse  + specular;
}

Math::float3 DirectionalLight::calculate(Vertex& vertex, const Material& material, const Math::float3& cameraPos, const Rasterizer& rasterizer) const {
    Math::float3 N = vertex.normal;
    N.normalize();
    Math::float3 fragPos = vertex.position;
    Math::float3 V = cameraPos - fragPos;
    V.normalize();
    Math::float3 L = -1 * direction;
    L.normalize();

    // Diffuse

    float diffuseFactor = std::max(0.0f, N.dot(L));

    // Specular

    Math::float3 R = (-1 * L) - 2 * ((-1 * L).dot(N)) * N;
    R.normalize();

    float specularFactor = std::pow(std::max(0.0f, V.dot(R)), material.shininess);

    // Combine components

    Math::Integer3 textureDiffuseInt = rasterizer.sampleTexture(vertex.uvCoords.x, vertex.uvCoords.y);

    Math::float3 textureDiffuse = {textureDiffuseInt.x / 255.0f,textureDiffuseInt.y / 255.0f,textureDiffuseInt.z / 255.0f};

    Math::float3 ambient = textureDiffuse * this->ambient;
    Math::float3 diffuse = textureDiffuse * this->diffuse * diffuseFactor;
    Math::float3 specular = material.specular * this->specular * specularFactor;

    return ambient + diffuse  + specular;
}
