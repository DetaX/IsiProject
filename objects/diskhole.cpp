#include "diskhole.h"
#include "disk.h"

DiskHole::DiskHole(double nbVectrices)
{
    _name= "DiskHole";
    Disk internDisk(0.5,nbVectrices);
    Disk externDisk(1,nbVectrices);
    int offset=0;
    this->addVertex(internDisk.getVertex(1));
    this->addVertex(externDisk.getVertex(1));
    for(int i=1;i<nbVectrices+2;++i)
    {
        this->addVertex(internDisk.getVertex(i));
        this->addVertex(externDisk.getVertex(i));
        offset=(i*2)+1;
        this->addTriangle(offset, offset-1, offset-3);
        this->addTriangle(offset-2,offset, offset-3);
    }


    computeNormalsT();
    computeNormalsV();
}

DiskHole::~DiskHole()
{
}
