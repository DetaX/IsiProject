#include <iostream>
#include <QTextStream>
#include <QStringList>
#include <string>

#include "off_loader.h"
#include "QFile"

OffLoader::OffLoader(std::string fileName)
{
    this->loadFile(QString::fromStdString(fileName));
}

void OffLoader::loadFile(QString fileName)
{
    _fileLoaded=fileName;
    double vertexNumber, triangleNumber;
    QFile file(fileName);
    QString line;
    QStringList stringList;
    QTextStream textStream(&file);
    qint64 pos;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "Cannot open file";
    else{
        line = textStream.readLine();
        if(line != "OFF")
        {
            file.close();
            throw "The file is not in the off format.";
        }
        line = textStream.readLine();
        stringList=line.split(" ");
        vertexNumber=stringList[0].toDouble();
        triangleNumber=stringList[1].toDouble();

        do
        {
            pos=textStream.pos();
            stringList = textStream.readLine().split(" ");
        }while(stringList.size()!=3);
        textStream.seek(pos);

        for(double i=0; i<vertexNumber; ++i)
        {
            line = textStream.readLine();
            stringList=line.split(" ");
            stringList.removeAll("");
            this->addVertex(stringList[0].toDouble(),
                    stringList[1].toDouble(),
                    stringList[2].toDouble());
        }

        for(double i=0;i<triangleNumber; ++i)
        {
            line = textStream.readLine();
            stringList=line.split(" ");
            stringList.removeAll("");
            if(stringList[0].toInt()!=3)
                throw "Only triangles please!!!!!!!!!!";
            this->addTriangle(stringList[1].toInt(),
                    stringList[2].toInt(),
                    stringList[3].toInt());
        }
        file.close();
        this->computeNormalsT();
        this->computeNormalsV();
        this->normalize();
    }
}
