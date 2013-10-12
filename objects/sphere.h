#ifndef SPHERE_H
#define SPHERE_H

#include "triMesh.h"

class Sphere: public TriMesh
{
public:
    Sphere(int depth=3);
    int getVertexID(Vertex vertex);
private:
    void _divideTriangle(int vertexId[3], int depth);

};

#endif // SPHERE_H
