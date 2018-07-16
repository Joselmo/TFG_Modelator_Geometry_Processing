#include "face.h"

Face::Face()
{

}

int Face::getId() const{
    return id;
}

void Face::setId(int value){
    id = value;
}

//QVector3D Face::getNormal() const{
//    return normal;
//}

QVector3D Face::getNormal(){
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
//    generateSurfaceNormal();
}

Vertex Face::getVertices(int _index){
    return vertices[_index];

}

void Face::addVertex(Vertex &_value){

    if(vertices.size()!= MAX_POSITION){
        vertices.push_back(_value);
//        generateSurfaceNormal();
    }
}

void Face::addVertex(int _index, Vertex &_value){
    if(_index<MAX_POSITION && _index>=0){
        vertices[_index]= _value;
//        generateSurfaceNormal();
    }
}

void Face::remplaceVertex(Vertex &_vertexOld, Vertex &_vertexNew)
{
    for(int i = 0; i< vertices.size(); i++){
        if(vertices[i].getId() ==_vertexOld.getId()){
            vertices[i] = _vertexNew;
        }
    }
//    generateSurfaceNormal();

}


void Face::generateSurfaceNormal(){

    QVector3D a = vertices[0].position();
    QVector3D b = vertices[2].position();
    QVector3D c = vertices[1].position();

    // V0 - V1
    a[0] -= c[0];
    a[1] -= c[1];
    a[2] -= c[2];

    // V2 - V1
    b[0] -= c[0];
    b[1] -= c[1];
    b[2] -= c[2];

    // Escalado para evitar errores de decimales
    a[0]*=  1000;
    a[1]*=  1000;
    a[2]*=  1000;

    b[0]*=  1000;
    b[1]*=  1000;
    b[2]*=  1000;

    // Cálculo
    normal[0] = a[1]*b[2] - (a[2]*b[1]);
    normal[1] = a[2]*b[0] - (a[0]*b[2]);
    normal[2] = a[0]*b[1] - (a[1]*b[0]);

    // Normalización
    double aux = sqrt(normal[0]*normal[0] +
                        normal[1]*normal[1] +
                        normal[2]*normal[2]);

    normal[0] /= aux;
    normal[1] /= aux;
    normal[2] /= aux;

    //Ajuste de ejes
    normal[0] *= -1;
    normal[1] *= -1;
    normal[2] *= -1;
}

void Face::clear()
{
    vertices.clear();
}


