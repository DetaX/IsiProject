#include "triMesh.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

TriMesh::TriMesh()
    : Object3D()
{
    _name="TriMesh";
}

void TriMesh::addVertex(Vertex v){
    extendBoundingBox(v);
    _vertices.push_back(v);
}
void TriMesh::addVertex(double x, double y, double z){
    addVertex(Vertex(x,y,z));
}
void TriMesh::addTriangle(Triangle t){
    _triangles.push_back(t);
}
void TriMesh::addTriangle(int v1, int v2, int v3){
    Triangle t;
    t.push_back(v1);
    t.push_back(v2);
    t.push_back(v3);
    addTriangle(t);
}
void TriMesh::addTriangleColor(Color c){
    _colors.push_back(c);
}
void TriMesh::addNormalT(Normal n){
    _normalsT.push_back(n);
}
void TriMesh::addNormalV(Normal n){
    _normalsV.push_back(n);
}


Vertex TriMesh::getVertex(int i){
    return _vertices[i];
}


void TriMesh::computeBoundingBox(){
    if(_vertices.size()<1) return;

    _bBoxMax=_vertices[0];
    _bBoxMin=_vertices[0];
    for(unsigned int i=0; i<_vertices.size(); ++i)
        extendBoundingBox(_vertices[i]);
}

void TriMesh::computeNormalsT(){
    _normalsT.empty();

    for(unsigned int t=0; t<_triangles.size(); ++t) {
        glm::vec3 vect1, vect2;
        vect1 = this->getVertex(_triangles[t][1]) - this->getVertex(_triangles[t][0]);
        vect2 = this->getVertex(_triangles[t][2]) - this->getVertex(_triangles[t][0]);
        glm::vec3 normal = glm::normalize(glm::cross(vect1,vect2));
        addNormalT(normal);
    }
}


void TriMesh::computeNormalsV(float angle_threshold){
    _normalsV.empty();
    Normal sum;
    int count;

    for (unsigned int i=0;i<_triangles.size(); ++i) {
        for (unsigned int m = 0;m<3;++m) {
            sum = _normalsT[i];
            count = 1;
            for (unsigned int j = 0;j<_triangles.size();++j) {
                if (i!=j && glm::angle(_normalsT[i],_normalsT[j]) < angle_threshold) {
                    for (unsigned int n = 0;n<3;++n) {
                        if(_triangles[i][m]==_triangles[j][n]) {
                            sum += _normalsT[j];
                            count++;
                        }
                    }
                }
            }
            sum /= count;
            addNormalV(sum);
        }
    }
}

double TriMesh::normalize(){
    glm::vec3 size=_bBoxMax-_bBoxMin;
    glm::vec3 c=getBoundingBoxCenter();
    double scale=2/max(size.x, max(size.y,size.z));

    for(unsigned int i=0; i<_vertices.size(); ++i){
        _vertices[i]+=c;
        _vertices[i]*=scale;
    }

    _bBoxMin+=c;
    _bBoxMin*=scale;
    _bBoxMax+=c;
    _bBoxMax*=scale;

    return scale;
}


std::string TriMesh::toString(){
    ostringstream oss;
    oss<< "["<< _name <<" v:"<< _vertices.size() <<", t:"<< _triangles.size() <<"]";
    return oss.str();
}

void TriMesh::toOStream(std::ostream& out) const{
    Object3D::toOStream(out);
    out << "   v: " << _vertices.size()  << std::endl;
    out << "   t: " << _triangles.size() << std::endl;
}



void TriMesh::draw(bool flipnormals){
    unsigned int i,t;
    bool smooth,color;
    Normal n;

    GLint mode[1];
    glGetIntegerv(GL_SHADE_MODEL, mode);
    smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;
    color=_triangles.size()==_colors.size();

    if(smooth){
        glBegin(GL_TRIANGLES);
        for(t=0; t<_triangles.size(); ++t) {
            if (color)
                if(_colors[t].size()==4)
                    glColor4f(_colors[t][0],_colors[t][1],_colors[t][2],_colors[t][3]);
                else
                    glColor3f(_colors[t][0],_colors[t][1],_colors[t][2]);
            for(i=0; i<3; i++){
                n=_normalsV[3*t+i];
                if(flipnormals) n*=-1;
                //        glNormal3fv(&n[0]);
                glNormal3fv(glm::value_ptr(n));
                glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
            }
        }
        glEnd();
    }else{
        glBegin(GL_TRIANGLES);
        for(t=0; t<_triangles.size(); ++t){
            if (color)
                if(_colors[t].size()==4)
                    glColor4f(_colors[t][0],_colors[t][1],_colors[t][2],_colors[t][3]);
                else
                    glColor3f(_colors[t][0],_colors[t][1],_colors[t][2]);
            n=_normalsT[t];
            if(flipnormals) n*=-1;
            glNormal3fv(glm::value_ptr(n));
            for(i=0; i<3; i++)
                glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
        }
        glEnd();
    }
}


void TriMesh::drawNormals(bool flipnormals){
    unsigned int i,t;
    bool smooth;
    glm::vec3 p,n;

    GLint mode[1];
    glGetIntegerv(GL_SHADE_MODEL, mode);
    smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

    glColor3f(1,1,1);
    if(smooth){
        for(i=0; i<_normalsV.size(); ++i){
            n=_normalsV[i];
            if(flipnormals) n*=-1;
            glNormal3fv(glm::value_ptr(n));
            n/=10;
            glBegin(GL_LINES);
            glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]));
            glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]+n));
            glEnd();
        }
    }else{
        for(t=0; t<_triangles.size(); ++t){
            p=  _vertices[_triangles[t][0]]
                    +_vertices[_triangles[t][1]]
                    +_vertices[_triangles[t][2]];
            p/=3;
            n=_normalsT[t];
            if(flipnormals) n*=-1;
            glNormal3fv(glm::value_ptr(n));
            n/=10;
            glBegin(GL_LINES);
            glVertex3fv(glm::value_ptr(p));
            glVertex3fv(glm::value_ptr(p+n));
            glEnd();
        }
    }
}

void TriMesh::drawVertices(){
    glPointSize(3.);
    glBegin(GL_POINTS);
    for(unsigned int i=0; i<_vertices.size(); ++i )
        glVertex3fv(glm::value_ptr(_vertices[i]));
    glEnd();
}


bool TriMesh::pointInTriangle(Vertex A, Vertex B, Vertex C, Vertex vertex) {
    if (sameSide(vertex,A,B,C) && sameSide(vertex,B,A,C) && sameSide(vertex,C,A,B)) {
        glm::vec3 vc1 = glm::cross(A-B,A-C);
        if(glm::abs(glm::dot(A-vertex,vc1)) <= .01f)
            return true;
    }
    return false;
}

bool TriMesh::sameSide(Vertex p1, Vertex p2, Vertex A, Vertex B) {
    glm::vec3 cp1 = glm::cross(B-A,p1-A);
    glm::vec3 cp2 = glm::cross(B-A,p2-A);
    if (glm::dot(cp1,cp2)>=0)
        return true;
    return false;
}

void TriMesh::triangulate(QList<int> sommets, Color color) {
    int offset = 0;
    int size = sommets.size();
    while (sommets.size()>3) {
        bool cut=false;
        Vertex a = getVertex(offset);
        Vertex b = getVertex(1+offset);
        Vertex c = getVertex(2+offset);
        if(glm::angle(b-a,c-b) < 180) {
            unsigned int j;
            while (!cut && j<sommets.size()) {
                cut = pointInTriangle(a,b,c,getVertex(j));
                j++;
            }
            if (!cut) {
                addTriangle(sommets[offset],sommets[offset+1],sommets[offset+2]);
                if (color.size()>=3)
                    addTriangleColor(color);
                sommets.removeAt(offset+1);
            }
            else
                offset=(offset+1)%size;
        }
        else
            offset=(offset+1)%size;
    }
    addTriangle(sommets[0],sommets[1],sommets[2]);
    if (color.size()>=3)
        addTriangleColor(color);
}
