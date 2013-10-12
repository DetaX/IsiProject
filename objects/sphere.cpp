#include "sphere.h"

/*
 * Let's be honest: I didn't find out how to draw
 * a geodesic sphere by myself…
 * The following algorithm is explained in this page:
 * http://www.opengl.org.ru/docs/pg/0208.html and can be divided in steps:
 *
 * 1- draw a basic shape of the sphere (an Icosahedron with 6 vertex)
 * 2- subdivise the triangles of the basic shape
 * 3- stop when the desired depth is reached and draw the triangle generated.
 */

Sphere::Sphere(int depth)
{
    _name="Sphere";

    //Step 1
    addVertex(1.0, 0., 0.);
    addVertex(0., 0., -1);
    addVertex(-1., 0., 0.);
    addVertex(0., 0., 1.);
    addVertex(0., 1., 0.);
    addVertex(0., -1., 0.);

    int vertexId[6];
    for(int i=0;i<6;++i)
        vertexId[i]=i;

    //Step 2

    int id[8][3]={
        {vertexId[0], vertexId[1], vertexId[4]},
        {vertexId[1], vertexId[2], vertexId[4]},
        {vertexId[2], vertexId[3], vertexId[4]},
        {vertexId[3], vertexId[0], vertexId[4]},
        {vertexId[1], vertexId[0], vertexId[5]},
        {vertexId[2], vertexId[1], vertexId[5]},
        {vertexId[3], vertexId[2], vertexId[5]},
        {vertexId[0], vertexId[3], vertexId[5]}
    };
    for(int i=0;i<8;++i)
        _divideTriangle(id[i],depth);

    computeNormalsT();
    computeNormalsV();


}

void Sphere::_divideTriangle(int vertexId[3], int depth)
{
    int midleVertexId[3];
    Vertex midleVertex[3];

    //Step 3
    if(depth == 0)
    {
        addTriangle(vertexId[0],vertexId[1],vertexId[2]);
        return;
    }
    else
    {
        //Let's find the midle of the triangles

        for(int i=0;i<3;++i)
        {
            midleVertex[i]= _vertices[vertexId[i]] +
                    _vertices[vertexId[(i+1)%3]];
            midleVertex[i]=glm::normalize(midleVertex[i]);
            midleVertexId[i]=this->getVertexID(midleVertex[i]);
        }
        //Let's divide the triangles
        int id[4][3]={
            {vertexId[0],midleVertexId[0],midleVertexId[2]},
            {vertexId[1],midleVertexId[1],midleVertexId[0]},
            {vertexId[2],midleVertexId[2],midleVertexId[1]},
            {midleVertexId[0],midleVertexId[1],midleVertexId[2]}
        };
        for(int i=0;i<4;++i)
            _divideTriangle(id[i],depth-1);
    }

}

int Sphere::getVertexID(Vertex vertex)
{
    for(int i=0;i<_vertices.size();++i)
    {
        if(_vertices[i]==vertex)
            return i;
    }
    this->addVertex(vertex);
    return(_vertices.size() - 1);
}
