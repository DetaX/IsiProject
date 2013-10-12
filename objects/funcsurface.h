/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines mathematical functions to make 3D surfaces
 *
 *
 */
#ifndef FUNCSURFACE_H
#define FUNCSURFACE_H

#include "triMesh.h"

class FuncSurface:public TriMesh
{
public:
    FuncSurface(int nbx, int nby, float minx, float maxx,
                float miny, float maxy, float(*func)(float, float)=NULL);
    void normalize();

protected:
    float _min[3];
    float _max[3];
};

#endif // FUNCSURFACE_H
