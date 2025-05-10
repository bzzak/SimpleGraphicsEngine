cmake_minimum_required(VERSION 3.30)
project(MiAGK)

set(CMAKE_CXX_STANDARD 20)

add_executable(MiAGK sources/main.cpp
        sources/Buffer.cpp
        headers/Buffer.h
        headers/ITgaSavable.h
        sources/TgaBuffer.cpp
        headers/TgaBuffer.h
        headers/Math.h
        headers/Rasterizer.h
        headers/SimpleRasterizer.h
        sources/SimpleRasterizer.cpp
        sources/Rasterizer.cpp
        sources/Math.cpp
        headers/VertexProcessor.h
        sources/VertexProcessor.cpp
        headers/Vertex.h
        headers/Mesh.h
        sources/Mesh.cpp
        headers/SimpleTriangle.h
        sources/SimpleTriangle.cpp
        headers/Cube.h
        sources/Cube.cpp
        headers/Cone.h
        sources/Cone.cpp
        headers/Cylinder.h
        sources/Cylinder.cpp
        headers/Sphere.h
        sources/Sphere.cpp
        headers/Torus.h
        sources/Torus.cpp
        headers/Light.h
        headers/DirectionalLight.h
        sources/DirectionalLight.cpp
        headers/PointLight.h
        sources/PointLight.cpp
        headers/Texture.h
        sources/Texture.cpp
)
