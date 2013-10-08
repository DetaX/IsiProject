#include "funcsurface.h"

FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,
                         float (*func)(float,float))
{
    _name="FuncSurface";

    //Computation of steps
    float xStep = (maxx-minx)/nbx;
    float yStep = (maxy-miny)/nby;

    int nbLine, nbVertex = -1;
    float z;

    for(float x=minx; x<maxx; x+=xStep)
    {
        nbLine = 0;
        for(float y=miny; y<maxy; y+=yStep)
        {
            z=(*func)(x,y);
            this->addVertex(x,y,z);
            nbVertex++;
            if(x>minx && nbLine!=0)
            {
                this->addTriangle(nbVertex-nby-1,nbVertex-1,nbVertex-nby);
                this->addTriangle(nbVertex-1,nbVertex,nbVertex-nby);
            }
            nbLine++;
        }
    }
    this->normalize();

    computeNormalsT();
    computeNormalsV();
}
