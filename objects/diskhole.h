#ifndef DISKHOLE_H
#define DISKHOLE_H

#include "triMesh.h"

class DiskHole : public TriMesh
{
public:
    DiskHole(double nbVectrices=20);
    virtual ~DiskHole();
};

#endif // DISKHOLE_H
