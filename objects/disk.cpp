#include "disk.h"

#include <cmath>

Disk::Disk(double r, double nbVectrices)
{
    _name= "Disk";
    const double pi = 3.14159265358979323846;
    double x,y=0.;
    if(nbVectrices<3)
        nbVectrices = 3;

    //Center and first vertex
    this->addVertex(0.,0.,0.);
    this->addVertex(r,0.,0.);

    for(double i=1; i<nbVectrices+1; ++i)
    {
        x=r*cos(i* (2*pi/nbVectrices) );
        y=r*sin(i* (2*pi/nbVectrices) );
        this->addVertex(x,y,0.);
        this->addTriangle(0,i,i+1);
    }

    //last triangle
    this->addTriangle(0,nbVectrices+1,1);

    computeNormalsT();
    computeNormalsV();
}

Disk::~Disk()
{
}
