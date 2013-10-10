#include "disk.h"


Disk::Disk(int nvertices)
    : TriMesh()
{
    _name = "Disk";

        this->addVertex(0,0,0);
    for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
        this->addVertex(cos(i),sin(i),0);

    for (int j=1; j<nvertices+1; ++j)
      this->addTriangle(0,j,j%nvertices+1);

    computeNormalsT();  // to be fixed
    computeNormalsV();  // to be fixed
}


Disk::~Disk()
{
}
