/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines 3D cube cut in a corner
 *
 *
 */
#ifndef CUBECORNER_H
#define CUBECORNER_H

#include "triMesh.h"

class CubeCorner : public TriMesh
{
public:
    CubeCorner();
    virtual ~CubeCorner();
};

#endif // CUBECORNER_H
