#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H

#include "../headers/Math.h"

class VertexProcessor {
private:
    Math::float4x4 obj2world;
    Math::float4x4 world2view;
    Math::float4x4 view2proj;

public:
    VertexProcessor();
    ~VertexProcessor() = default;

    Math::Point convertViewToNDC(Math::Point viewCoord);
    Math::Point convertObjToNDC(Math::Point objCoord);

    void setPerspective(float fovy, float aspect, float near, float far);
    void setLookAt(Math::float3 eye, Math::float3 center, Math::float3 up);
    void multByTranslation(Math::float3 v);
    void multByScale(Math::float3 v);
    void multByUniformScale(float v);
    void multByRotation(float a, Math::float3 v);
};

#endif //VERTEXPROCESSOR_H
