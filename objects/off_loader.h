/**
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 *  Defines a .off loader making 3D objects
 *
 *
 */
#ifndef OFF_LOADER_H
#define OFF_LOADER_H

#include "triMesh.h"
#include <QString>

class OffLoader: public TriMesh
{
public:
    OffLoader(std::string fileName);

    void loadFile(QString fileName);
protected:
    QString _fileLoaded;


};

#endif // OFF_LOADER_H