#ifndef CYLINDER_H
#define CYLINDER_H

#include "triMesh.h"

class Cylinder : public TriMesh
{
public:
    Cylinder(int nvertices = 20, int ndisk = 6);
    virtual ~Cylinder();
};

#endif // CYLINDER_H
