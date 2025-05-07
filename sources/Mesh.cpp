#include "../headers/Mesh.h"
#include "../headers/Vertex.h"
#include "../headers/Math.h"

void Mesh::draw(Rasterizer& rasterizer, Math::Integer3 color1, Math::Integer3 color2, Math::Integer3 color3) const {
    for (int i = 0; i < tSize; i++) {

        //Math::Point p = Math::Point(vertices[0].position.x, vertices[0].position.y, vertices[0].position.z);

        Math::Point p1 = Math::Point(vertices[indices[i].x].position.x, vertices[indices[i].x].position.y, vertices[indices[i].x].position.z);
        Math::Point p2 = Math::Point(vertices[indices[i].y].position.x, vertices[indices[i].y].position.y, vertices[indices[i].y].position.z);
        Math::Point p3 = Math::Point(vertices[indices[i].z].position.x, vertices[indices[i].z].position.y, vertices[indices[i].z].position.z);

        rasterizer.triangleFromObj( p1, p2, p3,color1,color2,color3);
    }

    rasterizer.resetTransformations();
}

void Mesh::draw(Rasterizer& rasterizer, Math::Integer3 color) const {
    for (int i = 0; i < tSize; i++) {

        //Math::Point p = Math::Point(vertices[0].position.x, vertices[0].position.y, vertices[0].position.z);

        Math::Point p1 = Math::Point(vertices[indices[i].x].position.x, vertices[indices[i].x].position.y, vertices[indices[i].x].position.z);
        Math::Point p2 = Math::Point(vertices[indices[i].y].position.x, vertices[indices[i].y].position.y, vertices[indices[i].y].position.z);
        Math::Point p3 = Math::Point(vertices[indices[i].z].position.x, vertices[indices[i].z].position.y, vertices[indices[i].z].position.z);

        rasterizer.triangleFromObj( p1, p2, p3,color,color,color);
    }

    rasterizer.resetTransformations();
}

void Mesh::makeNormals() {

    for (int i = 0; i < vSize; i++) {
        vertices[i].normal = Math::float3(0, 0, 0);
    }

    for (int i = 0; i < tSize; i++) {

        const Math::float3 n = (vertices[indices[i].z].position - vertices[indices[i].x].position).cross(vertices[indices[i].y].position - vertices[indices[i].x].position);

        vertices[indices[i].x].normal += n;
        vertices[indices[i].y].normal += n;
        vertices[indices[i].z].normal += n;
    }

    for (int i = 0; i < vSize; i++) {
        vertices[i].normal.normalize();
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