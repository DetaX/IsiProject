#include "cubecorner.h"

CubeCorner::CubeCorner()
{
    _name = "CubeCorner";
    // vertex coordinates
    //The corner is on the right up side
    static const GLfloat v[13][3] = {
        //bottom vertexes
        {-1,-1,1},{-1,-1,-1},{1,-1,1},{1,-1,-1},
        //top vertexes
        {-1,1, 1},{-1,1,-1},{1,1,-1},
        //corner vertexes
        {0,1,1},{1,1,0},{1,0,1},
        //front center
        {0,0,1},
        //right center
        {1,0,0},
        //top center
        {0,1,0}
    };

    // triangles vertex indices
    static const GLint t[19][3] = {
        {0,1,2},{3,2,1},  // bottom triangles
        {1,0,4},{4,5,1},  // cornerless left side triangles
        {1,5,3},{3,5,6},        // Back triangles
        {4,0,2},{7,4,10},{9,10,2},{9,7,10},       // front face
        {6,2,3},{11,9,2},{11,6,8},{9,11,8},   // right face
        {5,4,6},{12,4,7},{12,8,6},{12,7,8},//top face
        {8,7,9} //corner triangle
    };

    //--- Fill vertices and triangles vectors

    // Fill vertices vector
    for (int i=0; i<13 ; ++i)
        this->addVertex(v[i][0], v[i][1], v[i][2]);

    // Fill triangles vector
    for (int i=0; i<19; ++i)
        this->addTriangle(t[i][0], t[i][1], t[i][2]);

    computeNormalsT();
    computeNormalsV();
}

CubeCorner::~CubeCorner(){}
