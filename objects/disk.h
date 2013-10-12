/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines 3D disk
 *
 *
 */
#ifndef DISK_H
#define DISK_H
#include "triMesh.h"

class Disk : public TriMesh
{
public:
    Disk(int nvertices=20,int ndisk=6);
    virtual ~Disk();
};

#endif // DISK_H
