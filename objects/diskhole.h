/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines 3D disk with a hole
 *
 *
 */
#ifndef DISKHOLE_H
#define DISKHOLE_H

#include "triMesh.h"

class DiskHole : public TriMesh
{
public:
    DiskHole(int nvertices = 20,float radius=0.2,int ndisk=6);
    virtual ~DiskHole();
};

#endif // DISKHOLE_H
