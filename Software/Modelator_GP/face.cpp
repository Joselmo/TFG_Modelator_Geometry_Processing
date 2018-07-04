#include "face.h"



void Face::generateSurfaceNormal(){
    MyMesh::Normal normal_temp = MyMesh.calc_face_normal(vertices[0],
            vertices[1],vertices[2]);
    setNormal(normal_temp[0],normal_temp[1],normal_temp[2]);
}

Face::Face()
{
    
}

int Face::getId() const{
    return id;
}

void Face::setId(int value){
    id = value;
}

QVector3D Face::getNormal() const{
    return normal;
}

void Face::setNormal(const QVector3D &value){
    normal = value;
}

void Face::setNormal(float posx, float posy, float posz){
    normal = QVector3D(posx,posy,posz);
}


QVector<Vertex> Face::getVertices() const
{
    return vertices;
}

void Face::setVertices(const QVector<Vertex> &_value)
{
    vertices = _value;
}

Vertex Face::getVertices(int _index){
    return vertices[_index];

}

void Face::addVertex(Vertex &_value){

    if(vertices.size()!= MAX_POSITION)
        vertices.push_back(_value);
}

void Face::addVertex(int _index, Vertex &_value){
    if(_index<MAX_POSITION && _index>=0)
        vertices[_index]= _value;
}

void Face::remplaceVertex(Vertex &_vertexOld, Vertex &_vertexNew)
{
    for(int i = 0; i< vertices.size(); i++){
        if(vertices[i].getId() ==_vertexOld.getId()){
            vertices[i] = _vertexNew;
        }
    }

}

void Face::clear()
{
    vertices.clear();
}

