#include "../headers/VertexProcessor.h"

#define M_PI 3.14159265358979323846
#include <cmath>

VertexProcessor::VertexProcessor() {
    obj2world = Math::float4x4();
    obj2world.loadIdentity();
    world2view = Math::float4x4();
    world2view.loadIdentity();
    view2proj = Math::float4x4();
    view2proj.loadIdentity();
}

//VertexProcessor::~VertexProcessor() {}

void VertexProcessor::resetTransformations() {
    obj2world.loadIdentity();
}

Math::Point VertexProcessor::convertObjToNDC(Math::Point objCoord) {
    Math::float4 objFloat= {objCoord.x, objCoord.y, objCoord.z, 1.0};
    Math::float4 worldFloat= obj2world * objFloat;
    Math::float4 viewFloat= world2view * worldFloat;
    Math::float4 projFloat= view2proj * viewFloat;
    return {projFloat.x / projFloat.w, projFloat.y / projFloat.w, projFloat.z / projFloat.w};
}

Math::Point VertexProcessor::convertViewToNDC(Math::Point viewCoord) {
    Math::float4 viewFloat= {viewCoord.x, viewCoord.y, viewCoord.z, 1.0};
    Math::float4 projFloat= view2proj * viewFloat;
    return {projFloat.x / projFloat.w, projFloat.y / projFloat.w, projFloat.z / projFloat.w};
}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far) {
    fovy *= M_PI / 360.0f; // FOVy/2
    float f = cos(fovy) / sin(fovy);
    view2proj[0] = Math::float4(f/aspect,0,0,0);
    view2proj[1] = Math::float4(0,f,0,0);
    view2proj[2] = Math::float4(0,0,(far + near)/(near - far),-1);
    view2proj[3] = Math::float4(0,0,2*far*near/(near-far),0);
}

void VertexProcessor::setLookAt(Math::float3 eye, Math::float3 center, Math::float3 up) {
    Math::float3 f = center - eye;
    f.normalize();
    up.normalize();
    Math::float3 s = f.cross(up);
    s.normalize();
    Math::float3 u = s.cross(f);
    world2view[0] = Math::float4(s.x, u.x, -f.x, 0);
    world2view[1] = Math::float4(s.y, u.y, -f.y, 0);
    world2view[2] = Math::float4(s.z, u.z, -f.z, 0);
    world2view[3] = Math::float4(0, 0, 0, 1);
    Math::float4x4 m;
    m.loadIdentity();
    m[3] = Math::float4(-eye.x, -eye.y, -eye.z, 1);
    world2view *= m;
}

void VertexProcessor::multByTranslation(Math::float3 v) {
    Math::float4x4 m;
    m.loadIdentity();
    m.setTranslation(v);

    obj2world = m * obj2world;
}

void VertexProcessor::multByScale(Math::float3 v) {
    Math::float4x4 m;
    m.loadIdentity();
    m.setScale(v);

    obj2world = m * obj2world;
}

void VertexProcessor::multByUniformScale(float v) {
    Math::float4x4 m;
    m.loadIdentity();
    m.setUniformScale(v);

    obj2world = m * obj2world;
}

void VertexProcessor::multByRotation(float a, Math::float3 v) {
    //float s = sin(a * M_PI/180), c = cos(a * M_PI/180);
    v.normalize();
    Math::float4x4 m;
    m.loadIdentity();
    m.setRotationAxis(a, v);
    //m[0] = Math::float4();

    obj2world = m * obj2world;
}

void VertexProcessor::setObjectToWorld(Math::float4x4 m) {
    obj2world = m;
}



