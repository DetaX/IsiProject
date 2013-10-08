#include "cylinder.h"

Cylinder::Cylinder(int nvertices)
{
    _name="Cylinder";
    // origin of top disk
    this->addVertex(0,0,1);
    for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
        this->addVertex(cos(i),sin(i),1);

    // origin of bot disk
        this->addVertex(0,0,-1);
    for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
        this->addVertex(cos(i),sin(i),-1);

    //top disk
    for (int j=0; j<nvertices+1; ++j)
      this->addTriangle(j,0,j%nvertices+1);
    //bot disk
    for (int j=0; j<nvertices; ++j)
      this->addTriangle(nvertices+1,j+nvertices+2,(j+1)%nvertices+2+nvertices);

    //side triangles
    for (int j=1; j<nvertices+1; ++j)
      this->addTriangle(j,1+j%nvertices,j+1+nvertices);
    for (int j=1; j<nvertices+1; ++j)
      this->addTriangle(j%nvertices+1,j%nvertices+2+nvertices,nvertices+j+1);

    computeNormalsT();
    computeNormalsV();
}


Cylinder::~Cylinder()
{}
