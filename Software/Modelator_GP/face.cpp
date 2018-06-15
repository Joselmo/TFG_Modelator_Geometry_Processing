#include "face.h"

int Face::getId() const
{
    return id;
}

void Face::setId(int value)
{
    id = value;
}

Face::Face()
{
    
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

void Face::addVertex(int _index, Vertex &_value)
{
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

