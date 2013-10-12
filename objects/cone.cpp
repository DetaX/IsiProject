#include "cone.h"

Cone::Cone(int nvertices,int ndisk)
    : TriMesh()
{
    _name = "Cone";

    //vertices
    for (int i=0;i<ndisk-1;++i) {
        float z = 1-i*2/((float)ndisk-1);
        float radius = 1-i/((float)ndisk-1);
        this->addVertex(0,0,z);
        for (float i=0; i<2*M_PI ; i+=(2/(float)nvertices)*M_PI)
            this->addVertex(radius*cos(i),radius*sin(i),z);
    }
    this->addVertex(0,0,-1);
    //bottom disk
    for (int j=1; j<nvertices+1; ++j)
        this->addTriangle(0,j,j%nvertices+1);


    //side triangles
    for(int i=0;i<ndisk-2;++i) {
        for (int j=1; j<nvertices+1; ++j)
            this->addTriangle(1+j%nvertices+i*(nvertices+1),j+i*(nvertices+1),j+1+nvertices+i*(nvertices+1));
        for (int j=1; j<nvertices+1; ++j)
            this->addTriangle(j%nvertices+2+nvertices+i*(nvertices+1),j%nvertices+1+i*(nvertices+1),nvertices+j+1+i*(nvertices+1));
    }
    for (int j=1; j<nvertices+1; ++j)
        this->addTriangle(1+j%nvertices+(ndisk-2)*(nvertices+1),j+(ndisk-2)*(nvertices+1),(ndisk-1)*(nvertices+1));
    computeNormalsT();  // to be fixed
    computeNormalsV();  // to be fixed

}

Cone::~Cone()
{}
