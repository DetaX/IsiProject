#ifndef TORUS_H
#define TORUS_H

#include "triMesh.h"

class Torus : public TriMesh
{
public:
    Torus(int nbVertexLong=5, int nbVertexCircle=5);
};

#endif // TORUS_H
