#include "cylinder.h"

Cylinder::Cylinder(double nbVectrices)
{
    _name="Cylinder";
    double x,y=0;
    const double pi = 3.14159265358979323846;
    double offset=0;
    this->addVertex(0.,0.,1.);
    this->addVertex(0.,0.,-1.);
    this->addVertex(1.,0.,1.);
    this->addVertex(1.,0.,-1.);

    for(double i=1; i<nbVectrices+1; ++i)
    {
        x=cos(i* (2.*pi/nbVectrices) );
        y=sin(i* (2.*pi/nbVectrices) );
        offset=(i*2.);
        this->addVertex(x,y,1.);
        this->addVertex(x,y,-1.);
        //Disks
        this->addTriangle(0.,offset,offset+2);
        this->addTriangle(1.,offset+1,offset+3);
        //H
        this->addTriangle(offset,offset+3,offset+2);
        this->addTriangle(offset,offset+1,offset+3);
    }

    computeNormalsT();
    computeNormalsV();
}


Cylinder::~Cylinder()
{}
