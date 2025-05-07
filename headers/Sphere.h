#ifndef SPHERE_H
#define SPHERE_H

#include "../headers/Mesh.h"


class Sphere : public Mesh {
public:
    Sphere(int verticalSides, int horizontalSides);
    ~Sphere() = default;

};


#endif //SPHERE_H
