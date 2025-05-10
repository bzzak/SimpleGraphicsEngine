#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H

#include "../headers/Math.h"
#include "../headers/Vertex.h"

class VertexProcessor {
private:
    Math::float4x4 obj2world;
    Math::float4x4 world2view;
    Math::float4x4 view2proj;

public:
    VertexProcessor();
    ~VertexProcessor() = default;
    void convertVertexToView(Vertex& vertex) const;
    void convertVertexToNDC(Vertex& vertex) const;
    void convertVertexToWorld(Vertex& vertex) const;
    Math::Point convertViewToNDC(Math::Point viewCoord);
    Math::Point convertObjToNDC(Math::Point objCoord);

    Math::float4x4 getObject2world() const;
    Math::float4x4 getWorld2view() const;
    Math::float4x4 getView2proj() const;

    void setPerspective(float fovy, float aspect, float near, float far);
    void setLookAt(Math::float3 eye, Math::float3 center, Math::float3 up);
    void multByTranslation(Math::float3 v);
    void multByScale(Math::float3 v);
    void multByUniformScale(float v);
    void multByRotation(float a, Math::float3 v);
    void setObjectToWorld(Math::float4x4 m);

    void resetTransformations();

};

#endif //VERTEXPROCESSOR_H
