#include "diskhole.h"

DiskHole::DiskHole(int nvertices, float radius)
    : TriMesh()
{
    _name = "Disk Hole";

    // ext circle
    for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
        this->addVertex(cos(i),sin(i),0);
    // int circle
    for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
        this->addVertex(radius*cos(i),radius*sin(i),0);

    for (int j=0; j<nvertices; ++j)
    {
      this->addTriangle(j,(j+1)%nvertices,j+nvertices);
      this->addTriangle((j+1)%nvertices,(j+1)%nvertices+nvertices,j+nvertices);
    }
    computeNormalsT();  // to be fixed
    computeNormalsV();  // to be fixed
}

DiskHole::~DiskHole()
{
}
