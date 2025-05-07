#ifndef CYLINDER_H
#define CYLINDER_H

#include "../headers/Mesh.h"


class Cylinder : public Mesh {
public:
    Cylinder(int verticalSides, int horizontalSides);
    ~Cylinder() = default;

};

#endif //CYLINDER_H
