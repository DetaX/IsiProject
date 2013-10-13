#ifndef TORUS_H
#define TORUS_H

#include "triMesh.h"

class Torus : public TriMesh
{
public:
    Torus();

private:
    void _drawCircles(Vertex center, glm::vec3 normal, int nbVertex);

};

#endif // TORUS_H
