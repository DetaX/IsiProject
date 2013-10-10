#include "cone.h"

Cone::Cone(int nvertices)
    : TriMesh()
{
    _name = "Cone";


    // origin of disk
        this->addVertex(0,0,-1);
    for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
        this->addVertex(cos(i),sin(i),-1);

    // top vertex
        this->addVertex(0,0,1);
    // disk
    for (int j=1; j<nvertices+1; ++j)
      this->addTriangle(0,j%nvertices+1,j);
    // side
    for (int j=1; j<nvertices+1; ++j)
        this->addTriangle(nvertices+1,j%nvertices+1,(j+1)%nvertices+1);

    computeNormalsT();  // to be fixed
    computeNormalsV();  // to be fixed

}

Cone::~Cone()
{}
