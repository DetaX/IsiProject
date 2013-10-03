#ifndef CYLINDER_H
#define CYLINDER_H

#include "triMesh.h"

class Cylinder : public TriMesh
{
public:
    Cylinder(double nbVectrices = 200);
    virtual ~Cylinder();
};

#endif // CYLINDER_H
