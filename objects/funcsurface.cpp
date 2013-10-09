#include "funcsurface.h"
#include <iostream>
FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,
                         float (*func)(float,float))
{
    _name="FuncSurface";

    //Computation of steps
    float xStep = (maxx-minx)/nbx;
    float yStep = (maxy-miny)/nby;
    float zMax = 0;
    float zMin=0;
    int nbLine, nbVertex = 0;
    float z=0;

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
    std::cerr<<zMin;
    this->normalize();
    float zFactor = (zMax-zMin)/2;
    for(unsigned int i=0;i<_vertices.size();++i)
        _vertices[i][2]/=zFactor;

    computeNormalsT();
    computeNormalsV();
}
