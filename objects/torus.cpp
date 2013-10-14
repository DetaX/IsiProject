#include "torus.h"

#include <cmath>
#include <iostream>

Torus::Torus(int nbVertexLong, int nbVertexCircle)
{

    _name="Torus";
    _vertices.clear();
    double x,y,z;
    double circleStep=(2*M_PI)/nbVertexCircle;
    double longStep=(2*M_PI)/nbVertexLong;

    for(double i=0;i<2*M_PI;i+=longStep)
    {

        for(double j=0;j<2*M_PI;j+=circleStep)
        {
            x=((2./3.)+(1./3.)*cos(j))*cos(i);
            y=((2./3.)+(1./3.)*cos(j))*sin(i);
            z=(1./3.)*sin(j);
            addVertex(x,y,z);
            if(i>0)
            {
                addTriangle(_vertices.size()-1,
                            _vertices.size(),
                            _vertices.size()-nbVertexCircle);
                addTriangle(_vertices.size()-nbVertexCircle,
                            _vertices.size()-1-nbVertexCircle,
                            _vertices.size()-1);

            }
        }



    }

    computeNormalsT();
    computeNormalsV();
}


