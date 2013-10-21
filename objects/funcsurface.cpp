#include "funcsurface.h"
#include <iostream>
#include <cmath>

FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,
                         float (*func)(float,float))

{
    _min[0]=minx;
    _min[1]=miny;
    _max[0]=maxx;
    _max[1]=maxy;
    _name="FuncSurface";

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
    _min[2]=zMin;
    _max[2]=zMax;
    std::cout<<zMax;
    this->normalize();
    computeNormalsT();
    computeNormalsV();
}

void FuncSurface::normalize()
{
    float factor, average, offset;
    for(int coord=0; coord<3; ++coord)
    {
        if(std::abs(_max[coord])>std::abs(_min[coord]))
            factor = std::abs(_max[coord]);
        else
            factor = std::abs(_min[coord]);
        average = (std::abs(_max[coord])/factor + std::abs(_min[coord])/factor)/2;
        offset = (1. - average);
        for(unsigned int i=0;i<_vertices.size();++i)
        {
            _vertices[i][coord]/=factor;
            _vertices[i][coord]+=offset;
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
