#include "funcsurface.h"
#include <iostream>
#include <cmath>

FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,
                         float (*func)(float,float))

{
    _name="FuncSurface";

    //Saving max and min for x and y
    _min[0]=minx;
    _min[1]=miny;
    _max[0]=maxx;
    _max[1]=maxy;


    //Computing steps.
    float xStep = (maxx-minx)/nbx;
    float yStep = (maxy-miny)/nby;

    float zMax = 0;
    float zMin=0;
    int nbLine, nbVertex = 0;
    float z=0;

    //Main loop. We step forward following
    //x and compute for each step all the vertex (with differents
    //y) the z value.
    for(float x=minx; x<maxx; x+=xStep)
    {
        nbLine = 0;
        for(float y=miny; y<maxy; y+=yStep)
        {
            z=(*func)(x,y);
            if(z>zMax)
                zMax=z;
            if(z<zMin)
                zMin=z;
            this->addVertex(x,y,z);
            if(x>minx && nbLine!=0)
            {
                this->addTriangle(nbVertex-nby-1,nbVertex-1,nbVertex-nby);
                this->addTriangle(nbVertex-1,nbVertex,nbVertex-nby);
            }

            nbVertex++;
            nbLine++;
        }
    }
    _min[2]=zMin;
    _max[2]=zMax;
    //Normalising the function.
    this->normalize();
    computeNormalsT();
    computeNormalsV();
}

/*
  First we compute the offset and the dimention
  factor. Then we apply this factor and offset to
  all the vertexes of the mesh
  */
void FuncSurface::normalize()
{
    float factor, offset;
    for(int coord=0; coord<3; ++coord)
    {
        offset = (_max[coord]+_min[coord])/2;
        factor = _max[coord]-offset;
        for(unsigned int i=0;i<_vertices.size();++i)
        {
            _vertices[i][coord]-=offset;
            _vertices[i][coord]/=factor;
        }
    }
}

float FuncSurface::func_expcos(float x, float y)
{
    return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}
float FuncSurface::func_sqrt(float x, float y)
{
    return sqrt(x*x+y*y);
}
float FuncSurface::func_cosi(float x, float y)
{
    return cos(x)-sin(y);
}
