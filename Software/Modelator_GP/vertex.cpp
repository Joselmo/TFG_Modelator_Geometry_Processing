#include <vertex.h>


int Vertex::getId() const{
    return id;
}

void Vertex::setId(int _value){
    id = _value;
}

Vertex::Vertex() {}
Vertex::Vertex(const  QVector3D &_position)
    : m_position(_position) {}
Vertex::Vertex(const  QVector3D &_position,const   QVector3D &_color)
    : m_position(_position), m_color(_color) {}


const  QVector3D& Vertex::position()  const {
    return m_position;
}

const  QVector3D& Vertex::color()  const {
    return m_color;
}

void   Vertex::setPosition(const  QVector3D& _position) {
    m_position = _position;
}

void   Vertex::setColor(const QVector3D &_color) {
    m_color = _color;
}

void Vertex::addHalfEdgeIn(HalfEdge *_half_edge){
    half_edges_in.push_back(_half_edge);
}


HalfEdge* Vertex::getHalfEdgeIn(int _index) {
    QLinkedList<HalfEdge*>::iterator it_he;
    it_he = half_edges_in.begin() + _index;
    return *it_he;
}

QLinkedList<HalfEdge*> Vertex::getAllHalfEdgesIn() {
    return half_edges_in;
}

QLinkedList<HalfEdge*> *Vertex::getAllHalfEdgesInPtr() {
    return &half_edges_in;
}

void Vertex::removeHalfEdgeIn(int _index){
    half_edges_in.erase(half_edges_in.begin() + _index);
}

void Vertex::removeHalfEdgeIn(HalfEdge *_half_edge){

    half_edges_in.removeAll(_half_edge);
}

void   Vertex::addHalfEdgeOut(HalfEdge *_half_edge) {
    half_edges_out.push_back(_half_edge);
}

HalfEdge* Vertex::getHalfEdgeOut( int _index) {
    QLinkedList<HalfEdge*>::iterator it_he;
    it_he = half_edges_out.begin() + _index;
    return *it_he;
}

QLinkedList<HalfEdge*> Vertex::getAllHalfEdgesOut() {
    return half_edges_out;
}

QLinkedList<HalfEdge*> *Vertex::getAllHalfEdgesOutPtr() {
    return &half_edges_out;
}

void Vertex::removeHalfEdgeOut(int _index){
    half_edges_out.erase(half_edges_out.begin() + _index);
}

void Vertex::removeHalfEdgeOut(HalfEdge *_half_edge){
    half_edges_out.removeAll(_half_edge);
}

int Vertex::positionOffset() {
    return offsetof(Vertex, m_position);
}

int Vertex::colorOffset() {
    return offsetof(Vertex, m_color);
}

int Vertex::stride() {
    return sizeof(Vertex);
}
