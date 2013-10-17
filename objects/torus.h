/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines a 3D torus
 *
 *
 */
#ifndef TORUS_H
#define TORUS_H

#include "triMesh.h"

class Torus : public TriMesh
{
public:
    Torus(int nbCircles=20, int nbVertexCircle=20);
};

#endif // TORUS_H
