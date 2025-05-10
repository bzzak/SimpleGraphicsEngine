#include <cmath>

#include "../headers/Sphere.h"

#include <iostream>

#include "../headers/Vertex.h"
#include "../headers/Math.h"


Sphere::Sphere(int verticalSides, int horizontalSides) : Mesh() {
    if (verticalSides < 3) verticalSides = 3;
    if (horizontalSides < 2) horizontalSides = 2;
    vSize = (horizontalSides + 2)  * verticalSides; // +2 for top and bottom center vertices
    tSize = 2 * (horizontalSides - 1) * verticalSides + 2 * verticalSides;
    vertices = new Vertex[vSize];
    indices = new Math::Integer3[tSize];
    int indicesCounter = 0;

    currentTransformations.loadIdentity();

    float radius = 0.5f;

    // Generate vertices
    for (int h = 0; h < horizontalSides+1; ++h) {
        float theta = M_PI * h / horizontalSides;  // from 0 to PI
        float y = radius * std::cos(theta);
        float r = radius * std::sin(theta);
        float v = theta / M_PI; // v: 0 (top) -> 1 (bottom)

        for (int vIdx = 0; vIdx < verticalSides; ++vIdx) {
            float phi = 2 * M_PI * vIdx / verticalSides;  // from 0 to 2PI
            float x = r * std::cos(phi);
            float z = r * std::sin(phi);
            float u = phi / (2 * M_PI); // u: 0 -> 1

            int idx = h * verticalSides + vIdx;
            vertices[idx].position = {x, y, z};
            vertices[idx].uvCoords = {u, v};
        }
    }

    // Top and bottom poles
    //int topIndex = (horizontalSides - 1) * verticalSides;
    //vertices[topIndex].position = {0.0f, radius, 0.0f};
    //vertices[topIndex].uvCoords = {0.5f, 0.0f}; // środek górnej krawędzi

    //int bottomIndex = topIndex + 1;
    //vertices[bottomIndex].position = {0.0f, -radius, 0.0f};
    //vertices[bottomIndex].uvCoords = {0.5f, 1.0f}; // środek dolnej krawędzi

    // Indices for inner quads
    for (int h = 0; h < horizontalSides; ++h) {
        for (int v = 0; v < verticalSides; ++v) {
            int firstIndex = (v+1) % verticalSides + h*verticalSides;
            int secondIndex = v + verticalSides + h*verticalSides;
            int thirdIndex = (v+1) % verticalSides + verticalSides + h*verticalSides;
            int fourthIndex = v + 2*verticalSides + h*verticalSides;

            //int curr = h * verticalSides + v;
            //int next = h * verticalSides + (v + 1) % verticalSides;
            //int above = (h + 1) * verticalSides + v;
            //int aboveNext = (h + 1) * verticalSides + (v + 1) % verticalSides;

            indices[v + 2*h*verticalSides] = Math::Integer3(firstIndex, secondIndex, thirdIndex);
            indices[v + verticalSides + 2*h*verticalSides] = Math::Integer3(secondIndex, fourthIndex, thirdIndex);
        }
    }

    // Top cap
    //for (int v = 0; v < verticalSides; ++v) {
    //    int next = (v + 1) % verticalSides;
    //    indices[indicesCounter++] = Math::Integer3(topIndex, v, next);
    //}

    // Bottom cap
    //int base = (horizontalSides - 2) * verticalSides;
    //for (int v = 0; v < verticalSides; ++v) {
      //  int curr = base + v;
      //  int next = base + (v + 1) % verticalSides;
      //  indices[indicesCounter++] = Math::Integer3(bottomIndex, next, curr);
    //}

   //std::cout << "Indices counter: " << indicesCounter << std::endl;

   // std::cout << "Vertex Numbers: " << vSize << std::endl;
   // for (int i = 0; i < vSize; i++) {
   //         std::cout << i << " : " << vertices[i].position.x << ", " << vertices[i].position.y << ", " << vertices[i].position.z << std::endl;
   // }


    // std::cout << "Vertex Numbers: " << vSize << std::endl;
    // for (int i = 0; i < tSize; i++) {
    //     //if (i == 1740) {
    //         std::cout << i << " : " << indices[i].x << ", " << indices[i].y << ", " << indices[i].z << std::endl;
    //    //}
    //
    // }
}