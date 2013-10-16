#include "torus.h"

#include <cmath>
#include <iostream>

Torus::Torus(int nbCircles, int nbVertexCircle)
{

    _name="Torus";
    _vertices.clear();
    double x,y,z;
    double circleStep=(2.*M_PI)/nbVertexCircle;
    double longStep=(2.*M_PI)/nbCircles;

    //Adding Vertex
    for(double i=0.;i<2.*M_PI;i+=longStep)
    {

        for(double j=0.;j<2.*M_PI;j+=circleStep)
        {
            x=((2./3.)+(1./3.)*cos(j))*cos(i);
            y=((2./3.)+(1./3.)*cos(j))*sin(i);
            z=(1./3.)*sin(j);
            addVertex(x,y,z);
        }

    }

    //Adding triangles
    for(int i=0;i<nbCircles;++i)
        for(int j=0;j<nbVertexCircle;++j)
        {
            addTriangle(i*nbVertexCircle+j+1,
                        i*nbVertexCircle+j,
                        (i+1)*nbVertexCircle+j);
            addTriangle((i+1)*nbVertexCircle+j,
                        (i+1)*nbVertexCircle+j+1,
                        i*nbVertexCircle+j+1);
        }

    computeNormalsT();
    computeNormalsV();
}


