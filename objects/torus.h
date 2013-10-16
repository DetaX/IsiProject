#ifndef TORUS_H
#define TORUS_H

#include "triMesh.h"

class Torus : public TriMesh
{
public:
    Torus(int nbCircles=10, int nbVertexCircle=10);
};

#endif // TORUS_H
