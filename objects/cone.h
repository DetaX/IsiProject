/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines 3D cone
 *
 *
 */

#ifndef CONE_H
#define CONE_H

#include "triMesh.h"

/**
 * Cone Object
 *
 */
class Cone : public TriMesh
{
public:
    Cone(int nvertices=20,int ndisk=6);
    virtual ~Cone();
};

#endif // CONE_H
