/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines a 3D sphere
 *
 *
 */
#ifndef SPHERE_H
#define SPHERE_H

#include "triMesh.h"

class Sphere: public TriMesh
{
public:
    Sphere(int depth=4);
    int getVertexID(Vertex vertex);
private:
    void _divideTriangle(int vertexId[3], int depth);

};

#endif // SPHERE_H
