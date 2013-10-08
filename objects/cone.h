#ifndef CONE_H
#define CONE_H

#include "triMesh.h"

class Cone : public TriMesh
{
public:
    Cone(double nbVectrices=20);
    virtual ~Cone();
};

#endif // CONE_H
