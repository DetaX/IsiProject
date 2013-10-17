#include "off_loader.h"
#include "QFile"
#include "QList"

#include <QChar>

OffLoader::OffLoader(std::string fileName) throw(std::logic_error, std::ios_base::failure)
{
    this->loadFile(QString::fromStdString(fileName));
}

void OffLoader::loadFile(QString fileName) throw(std::logic_error, std::ios_base::failure)
{
    _fileLoaded=fileName;
    double vertexNumber, polygonNumber;
    QFile file(fileName);
    QString line;
    QStringList stringList;
    QTextStream textStream(&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::ios_base::failure("Cannot open file");
    else{
        line = textStream.readLine();
        if(line != "OFF")
        {
            file.close();
            throw std::logic_error("The file is not in the off format.");
        }
        stringList = readLine(textStream);
        vertexNumber=stringList[0].toDouble();
        polygonNumber=stringList[1].toDouble();
        for(double i=0; i<vertexNumber; ++i)
        {
            stringList = readLine(textStream);
            this->addVertex(stringList[0].toDouble(),
                            stringList[1].toDouble(),
                            stringList[2].toDouble());
        }

        for(double i=0;i<polygonNumber; ++i)
        {
            stringList=readLine(textStream);
            QList<int> sommet;
            Color color;
            for (unsigned int j =1;j<=stringList[0].toInt();++j)
                sommet.push_back(stringList[j].toInt());
            for (unsigned int j =stringList[0].toInt()+1;j<stringList.size();++j)
                color.push_back(stringList[j].toFloat());
            triangulate(sommet,color);
        }
        file.close();
        this->computeNormalsT();
        this->computeNormalsV();
        this->normalize();
    }
}

QStringList OffLoader::readLine(QTextStream &stream)
{
    QString line;
    QStringList list;
    do{
        line = stream.readLine();
        line.replace(QString("\t"),QString(" "));
        list=line.split(" ");
        list.removeAll("");
    }while(list.size()==0 || list[0].contains("#") || list[0]=="");
    return list;
}
