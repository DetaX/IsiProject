#include "diskhole.h"

DiskHole::DiskHole(int nvertices, float radius, int ndisk)
    : TriMesh()
{
    _name = "Disk Hole";

    //vertices
    for (int i=0;i<ndisk;++i) {
        float r = 1-(1-radius)*i/((float)ndisk-1);
        this->addVertex(0,0,0);
        for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
            this->addVertex(r*cos(i),r*sin(i),0);
    }



    //side triangles
    for(int i=0;i<ndisk-1;++i) {
        for (int j=1; j<nvertices+1; ++j)
            this->addTriangle(1+j%nvertices+i*(nvertices+1),j+i*(nvertices+1),j+1+nvertices+i*(nvertices+1));
        for (int j=1; j<nvertices+1; ++j)
            this->addTriangle(j%nvertices+2+nvertices+i*(nvertices+1),j%nvertices+1+i*(nvertices+1),nvertices+j+1+i*(nvertices+1));
    }


    computeNormalsT();  // to be fixed
    computeNormalsV();  // to be fixed
}

DiskHole::~DiskHole()
{
}
