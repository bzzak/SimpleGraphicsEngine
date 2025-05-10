#include "../headers/Mesh.h"
#include "../headers/Rasterizer.h"
#include <cmath>

#include "../headers/Vertex.h"
#include "../headers/Math.h"

bool Mesh::loadTexture(const std::string& filename) {
    if (texture != nullptr) delete texture;
    texture = new Texture();
    if (texture->loadFromFile(filename)) {
        hasTexture = true;
        return true;
    } else {
        return false;
    }
}

void Mesh::setTexture(const Texture& tex) {
    if (texture != nullptr) delete texture;
    texture = new Texture(tex);
    hasTexture = true;
}

void Mesh::draw(Rasterizer& rasterizer, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) const {
    for (int i = 0; i < tSize; i++) {

        Vertex v1 = vertices[indices[i].x];
        Vertex v2 = vertices[indices[i].y];
        Vertex v3 = vertices[indices[i].z];

        Math::Point p1 = Math::Point(v1.position.x, v1.position.y, v1.position.z);
        Math::Point p2 = Math::Point(v2.position.x, v2.position.y, v2.position.z);
        Math::Point p3 = Math::Point(v3.position.x, v3.position.y, v3.position.z);

        rasterizer.triangleFromObj( p1, p2, p3,color1,color2,color3);
    }

    rasterizer.resetTransformations();
}

void Mesh::draw(Rasterizer& rasterizer, Math::Integer3 color) const {
    for (int i = 0; i < tSize; i++) {

        Vertex v1 = vertices[indices[i].x];
        Vertex v2 = vertices[indices[i].y];
        Vertex v3 = vertices[indices[i].z];

        Math::Point p1 = Math::Point(v1.position.x, v1.position.y, v1.position.z);
        Math::Point p2 = Math::Point(v2.position.x, v2.position.y, v2.position.z);
        Math::Point p3 = Math::Point(v3.position.x, v3.position.y, v3.position.z);


        rasterizer.triangleFromObj( p1, p2, p3,color,color,color);
    }

    rasterizer.resetTransformations();
}

void Mesh::draw(Rasterizer& rasterizer) const {
    for (int i = 0; i < tSize; i++) {

        std::vector<Vertex> triangleVertices;
        triangleVertices.push_back(vertices[indices[i].x]);
        triangleVertices.push_back(vertices[indices[i].y]);
        triangleVertices.push_back(vertices[indices[i].z]);

        Math::Point p1 = Math::Point(triangleVertices[0].position.x, triangleVertices[0].position.y, triangleVertices[0].position.z);
        Math::Point p2 = Math::Point(triangleVertices[1].position.x, triangleVertices[1].position.y, triangleVertices[1].position.z);
        Math::Point p3 = Math::Point(triangleVertices[2].position.x, triangleVertices[2].position.y, triangleVertices[2].position.z);

        std::vector<Math::float3> resultColors;
        std::vector<Math::Integer3> resultColorsInt;

        if (rasterizer.isTexturingEnabled() && isTexturingEnabled()) rasterizer.setActiveTexture(texture);

        if (isTexturingEnabled() && rasterizer.isTexturingEnabled() && rasterizer.getActiveTexture() != nullptr) {
            for (int i = 0; i < 3; i++) {
                resultColorsInt.emplace_back(rasterizer.sampleTexture(triangleVertices[i].uvCoords.x, triangleVertices[i].uvCoords.y));
            }
        }
        else {
            for (int i = 0; i < 3; i++) {
                resultColors.emplace_back(material.diffuse);
            }
        }


        if (!(isTexturingEnabled() && rasterizer.isTexturingEnabled() && rasterizer.getActiveTexture() != nullptr)) {
            for (int i = 0; i < 3; i++) {
                resultColorsInt.emplace_back(static_cast<int>(std::round(resultColors[i].x * 255.0f)), static_cast<int>(std::round(resultColors[i].y * 255.0f)), static_cast<int>(std::round(resultColors[i].z * 255.0f)));
            }
        }


        rasterizer.triangleFromObj( p1, p2, p3,resultColorsInt[0],resultColorsInt[1],resultColorsInt[2]);
    }

    rasterizer.resetTransformations();
}

void Mesh::drawPixel(Rasterizer& rasterizer) const {

    if (hasTexture) rasterizer.setActiveTexture(texture);

    for (int i = 0; i < tSize; i++) {

        if (indices[i].x < 0 || indices[i].x >= vSize ||
            indices[i].y < 0 || indices[i].y >= vSize ||
            indices[i].z < 0 || indices[i].z >= vSize) {
            continue; // Ignoruj nieprawidłowe indeksy
            }

        std::vector<Vertex> triangleVertices;
        triangleVertices.push_back(vertices[indices[i].x]);
        triangleVertices.push_back(vertices[indices[i].y]);
        triangleVertices.push_back(vertices[indices[i].z]);
        std::vector<Math::float3> resultColors;

        Math::Point p1 = Math::Point(triangleVertices[0].position.x, triangleVertices[0].position.y, triangleVertices[0].position.z);
        Math::Point p2 = Math::Point(triangleVertices[1].position.x, triangleVertices[1].position.y, triangleVertices[1].position.z);
        Math::Point p3 = Math::Point(triangleVertices[2].position.x, triangleVertices[2].position.y, triangleVertices[2].position.z);

        if (isTexturingEnabled() && hasTexture) {
            rasterizer.triangleFromObjPixel(p1, p2, p3, triangleVertices[0].uvCoords, triangleVertices[1].uvCoords, triangleVertices[2].uvCoords);
        } else {

            for (int i = 0; i < 3; i++) {
                resultColors.emplace_back(material.diffuse);
            }

            std::vector<Math::Integer3> resultColorsInt;

            for (int i = 0; i < 3; i++) {
                resultColorsInt.emplace_back(static_cast<int>(std::round(resultColors[i].x * 255.0f)), static_cast<int>(std::round(resultColors[i].y * 255.0f)), static_cast<int>(std::round(resultColors[i].z * 255.0f)));
            }

            rasterizer.triangleFromObj(p1, p2, p3,  resultColorsInt[0], resultColorsInt[1], resultColorsInt[2]);
        }

    }
    rasterizer.setActiveTexture(nullptr);
    rasterizer.resetTransformations();
}

void Mesh::drawPhong(Rasterizer& rasterizer, const std::vector<Light*>& lights) const {
    for (int i = 0; i < tSize; i++) {

        if (indices[i].x < 0 || indices[i].x >= vSize ||
            indices[i].y < 0 || indices[i].y >= vSize ||
            indices[i].z < 0 || indices[i].z >= vSize) {
            continue; // Ignoruj nieprawidłowe indeksy
            }

        std::vector<Vertex> triangleVertices;
        triangleVertices.push_back(vertices[indices[i].x]);
        triangleVertices.push_back(vertices[indices[i].y]);
        triangleVertices.push_back(vertices[indices[i].z]);
        std::vector<Math::float3> resultColors = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

        Math::Point p1 = Math::Point(triangleVertices[0].position.x, triangleVertices[0].position.y, triangleVertices[0].position.z);
        Math::Point p2 = Math::Point(triangleVertices[1].position.x, triangleVertices[1].position.y, triangleVertices[1].position.z);
        Math::Point p3 = Math::Point(triangleVertices[2].position.x, triangleVertices[2].position.y, triangleVertices[2].position.z);

        if (rasterizer.isTexturingEnabled() && isTexturingEnabled()) rasterizer.setActiveTexture(texture);

        for (const auto& light : lights) {
            for (int j = 0; j < 3; j++) {
                if (isTexturingEnabled() && rasterizer.isTexturingEnabled() && rasterizer.getActiveTexture() != nullptr) {
                    //rasterizer.setActiveTexture(texture);
                    resultColors[j] += light->calculate(triangleVertices[j], material, rasterizer.getEye(), rasterizer);
                }
                else {
                    resultColors[j] += light->calculate(triangleVertices[j], material, rasterizer.getEye());
                }

            }
        }

        rasterizer.setActiveTexture(nullptr);

        for (auto color : resultColors) {
            color = {
                std::clamp(color.x, 0.0f, 1.0f),
                std::clamp(color.y, 0.0f, 1.0f),
                std::clamp(color.z, 0.0f, 1.0f)
            };
        }

        std::vector<Math::Integer3> resultColorsInt;

        for (int i = 0; i < 3; i++) {
            resultColorsInt.emplace_back(static_cast<int>(std::round(resultColors[i].x * 255.0f)), static_cast<int>(std::round(resultColors[i].y * 255.0f)), static_cast<int>(std::round(resultColors[i].z * 255.0f)));
        }



        rasterizer.triangleFromObj( p1, p2, p3,resultColorsInt[0],resultColorsInt[1],resultColorsInt[2]);
    }

    rasterizer.resetTransformations();
}

void Mesh::drawPhongPixel(Rasterizer& rasterizer, const std::vector<Light*>& lights) const {
    for (int i = 0; i < tSize; i++) {

        if (indices[i].x < 0 || indices[i].x >= vSize ||
            indices[i].y < 0 || indices[i].y >= vSize ||
            indices[i].z < 0 || indices[i].z >= vSize) {
            continue; // Ignoruj nieprawidłowe indeksy
            }

        std::vector<Vertex> triangleVertices;
        triangleVertices.push_back(vertices[indices[i].x]);
        triangleVertices.push_back(vertices[indices[i].y]);
        triangleVertices.push_back(vertices[indices[i].z]);
        std::vector<Math::float3> resultColors = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

        Math::Point p1 = Math::Point(triangleVertices[0].position.x, triangleVertices[0].position.y, triangleVertices[0].position.z);
        Math::Point p2 = Math::Point(triangleVertices[1].position.x, triangleVertices[1].position.y, triangleVertices[1].position.z);
        Math::Point p3 = Math::Point(triangleVertices[2].position.x, triangleVertices[2].position.y, triangleVertices[2].position.z);

        if (isTexturingEnabled() && hasTexture) {
            rasterizer.trianglePhong(p1, p2, p3,  triangleVertices[0].normal, triangleVertices[1].normal, triangleVertices[2].normal, triangleVertices[0].uvCoords, triangleVertices[1].uvCoords, triangleVertices[2].uvCoords, material, rasterizer.getEye(), lights, texture);
        } else {
            rasterizer.trianglePhong(p1, p2, p3,  triangleVertices[0].normal, triangleVertices[1].normal, triangleVertices[2].normal, material, rasterizer.getEye(), lights);
        }

    }
    rasterizer.setActiveTexture(nullptr);
    rasterizer.resetTransformations();

}

void Mesh::makeNormals() {

    for (int i = 0; i < vSize; i++) {
        vertices[i].normal = Math::float3(0, 0, 0);
    }

    for (int i = 0; i < tSize; i++) {

        if (indices[i].x < 0 || indices[i].x >= vSize ||
            indices[i].y < 0 || indices[i].y >= vSize ||
            indices[i].z < 0 || indices[i].z >= vSize) {
            continue; // Ignoruj nieprawidłowe indeksy
        }
        //Math::float3 temp1 = vertices[indices[i].z].position;
        //Math::float3 temp2 = vertices[indices[i].x].position;

        Math::float3 v1 = vertices[indices[i].z].position - vertices[indices[i].x].position;
        Math::float3 v2 = vertices[indices[i].y].position - vertices[indices[i].x].position;

        const Math::float3 n = v1.cross(v2);

        vertices[indices[i].x].normal += n;
        vertices[indices[i].y].normal += n;
        vertices[indices[i].z].normal += n;
    }

    for (int i = 0; i < vSize; i++) {
        float len = vertices[i].normal.len();
        if (len > 1e-6f) {
            vertices[i].normal.normalize();
        } else {
            vertices[i].normal = Math::float3(0, 1, 0); // lub inny domyślny kierunek
        }
    }

}

void Mesh::scale(Rasterizer& rasterizer, Math::float3 s) {
    Math::float4x4 mat;
    mat.loadIdentity();
    mat.setScale(s);
    rasterizer.setTransformations(currentTransformations);
    rasterizer.scale(s);
    currentTransformations = currentTransformations * mat;
}

void Mesh::uniformScale(Rasterizer& rasterizer, float s) {
    Math::float4x4 mat;
    mat.loadIdentity();
    mat.setUniformScale(s);
    rasterizer.setTransformations(currentTransformations);
    rasterizer.uniformScale(s);
    currentTransformations = currentTransformations * mat;
}

void Mesh::translate(Rasterizer& rasterizer, Math::float3 t) {
    Math::float4x4 mat;
    mat.loadIdentity();
    mat.setTranslation(t);
    rasterizer.setTransformations(currentTransformations);
    rasterizer.translate(t);
    currentTransformations = currentTransformations * mat;
}

void Mesh::rotate(Rasterizer& rasterizer, float angle, Math::float3 axis) {
    Math::float4x4 mat;
    mat.loadIdentity();
    mat.setRotationAxis(angle, axis);
    rasterizer.setTransformations(currentTransformations);
    rasterizer.rotate(angle, axis);
    currentTransformations = currentTransformations * mat;
}

void Mesh::setTransformations(Rasterizer& rasterizer) const {
    rasterizer.setTransformations(currentTransformations);
}