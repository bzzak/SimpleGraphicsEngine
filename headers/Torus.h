#ifndef TORUS_H
#define TORUS_H

#include "../headers/Mesh.h"


class Torus : public Mesh {
public:
    Torus(int verticalSides, int horizontalSides);
    ~Torus() = default;

};

#endif //TORUS_H
