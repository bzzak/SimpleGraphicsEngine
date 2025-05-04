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
        sources/Rasterizer.cpp)
