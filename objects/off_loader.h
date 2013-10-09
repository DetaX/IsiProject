#ifndef OFF_LOADER_H
#define OFF_LOADER_H

#include "triMesh.h"
#include <QString>

class OffLoader: public TriMesh
{
public:
    OffLoader();

    void loadFile(QString fileName);
protected:
    QString _fileLoaded;


};

#endif // OFF_LOADER_H
