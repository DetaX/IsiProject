/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines 3D cylinder
 *
 *
 */

#ifndef CYLINDER_H
#define CYLINDER_H

#include "triMesh.h"
/**
 * Cylinder Object
 *
 */
class Cylinder : public TriMesh
{
public:
    Cylinder(int nvertices = 20, int ndisk = 6);
    virtual ~Cylinder();
};

#endif // CYLINDER_H
