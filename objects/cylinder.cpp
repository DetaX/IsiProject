#include "cylinder.h"

Cylinder::Cylinder(int nvertices, int ndisk)
{
    _name="Cylinder";
    //vertices
    for (int i=0;i<ndisk;++i) {
        float z = 1-i*2/(float(ndisk)-1);
        this->addVertex(0,0,z);
        for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
            this->addVertex(cos(i),sin(i),z);
    }

    //top disk
    for (int j=1; j<nvertices+1; ++j)
        this->addTriangle(0,j,j%nvertices+1);
    //bottom disk
    for (int j=0; j<nvertices; ++j)
        this->addTriangle(j+(ndisk-1)*nvertices+ndisk,(ndisk-1)*(nvertices+1),(j+1)%nvertices+ndisk+(ndisk-1)*nvertices);


    //side triangles
    for(int i=0;i<ndisk-1;++i) {
        for (int j=1; j<nvertices+1; ++j)
            this->addTriangle(1+j%nvertices+i*(nvertices+1),j+i*(nvertices+1),j+1+nvertices+i*(nvertices+1));
       for (int j=1; j<nvertices+1; ++j)
          this->addTriangle(j%nvertices+2+nvertices+i*(nvertices+1),j%nvertices+1+i*(nvertices+1),nvertices+j+1+i*(nvertices+1));

    }

    computeNormalsT();
    computeNormalsV();
}


Cylinder::~Cylinder()
{}
