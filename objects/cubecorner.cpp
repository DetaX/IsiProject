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
      {0,1,2},{2,3,1},  // bottom triangles
      {0,1,4},{5,4,1},  // cornerless left side triangles
      {5,1,3},{5,3,6},        // Back triangles
      {4,0,2},{4,7,10},{9,10,2},{7,9,10},       // front face
      {2,6,3},{9,11,2},{11,6,8},{11,9,8},   // right face
      {5,4,6},{12,4,7},{8,12,6},{12,7,8},//top face
      {7,8,9} //corner triangle
    };

    // triangle normals
    static const GLint nt[13][3] = {
      {0,0,-1},{0,0,-1}, // bottom triangle normals
      {0,1,0},{0,1,0},{1,0,0},{1,0,0},{0,-1,0},{0,-1,0},{-1,0,0},{-1,0,0}, // side triangle normals
      {0,0,1},{0,0,1}    // top triangle normals
    };

    // triangle vertex normals
    static const GLint nv[36][3] = {
      {0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1}, // bottom triangle vertex normals

      {0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},       // side triangle vertex normals
      {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
      {0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},
      {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},

      {0,0,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}        // top triangle vertex normals
    };


    //--- Fill vertices and triangles vectors

    // Fill vertices vector
    for (int i=0; i<13 ; ++i)
      this->addVertex(v[i][0], v[i][1], v[i][2]);

    // Fill triangles vector
    for (int i=0; i<19; ++i)
      this->addTriangle(t[i][0], t[i][1], t[i][2]);

    // Fill normals vectors
    bool use_computed_normals = false;

    if (use_computed_normals) {

        computeNormalsT();  // to be fixed
        computeNormalsV();  // to be fixed

      } else { // use manually defined normals

        // set triangle normals
        for (int i=0; i<12; ++i) {
            Normal nT(nt[i][0], nt[i][1], nt[i][2]);
            this->addNormalT(nT);
          }
        // set triangle vertex normals
        for (int i=0; i<36; ++i) {
            Normal nV(nv[i][0], nv[i][1], nv[i][2]);
            this->addNormalV(nV);
          }
      }


}

CubeCorner::~CubeCorner(){}
