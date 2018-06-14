#include <vertex.h>


/*******************************************************************************
 *  ructor
 ******************************************************************************/
int Vertex::getId() const
{
    return id;
}

void Vertex::setId(int value)
{
    id = value;
}

Vertex::Vertex() {}
Vertex::Vertex(const  QVector3D &_position)
    : m_position(_position) {}
Vertex::Vertex(const  QVector3D &_position,const   QVector3D &_color)
    : m_position(_position), m_color(_color) {}


/*******************************************************************************
 * Accessors / Mutators
 ******************************************************************************/
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

void Vertex::addHalfEdgeIn(HalfEdge &_half_edge){
    half_edges_in.push_back(_half_edge);
}

void   Vertex::setHalfEdgeIn(QVector<HalfEdge> &_half_edges) {
    half_edges_in = _half_edges;
}

HalfEdge Vertex::getHalfEdgeIn(int _index) {
    return half_edges_in.at(_index);
}

QVector<HalfEdge>  Vertex::getAllHalfEdgesIn() {
    return half_edges_in;
}

void Vertex::removeHalfEdgeIn(int _index){
    half_edges_in.removeAt(_index);
}

void Vertex::removeHalfEdgeIn(HalfEdge &_half_edge){

    QVector<HalfEdge>::iterator it;
    for(it = half_edges_in.begin(); it == half_edges_in.end();++it){
        if(it->getId()==_half_edge.getId())
            half_edges_in.erase(it);
    }
}

void   Vertex::addHalfEdgeOut(HalfEdge &_half_edge) {
    half_edges_out.push_back(_half_edge);
}

void   Vertex::setHalfEdgeOut(QVector<HalfEdge> &_half_edges) {
    half_edges_out = _half_edges;
}

HalfEdge Vertex::getHalfEdgeOut( int _index) {
    return half_edges_out.at(_index);
}

QVector<HalfEdge> Vertex::getAllHalfEdgesOut() {
    return half_edges_out;
}

void Vertex::removeHalfEdgeOut(int _index){
    half_edges_out.removeAt(_index);
}

void Vertex::removeHalfEdgeOut(HalfEdge &_half_edge){
    QVector<HalfEdge>::iterator it;
    for(it = half_edges_out.begin(); it == half_edges_out.end();++it){
        if(it->getId()==_half_edge.getId())
            half_edges_out.erase(it);
    }
}


/*******************************************************************************
 * OpenGL Helpers
 ******************************************************************************/
int Vertex::positionOffset() {
    return offsetof(Vertex, m_position);
}

int Vertex::colorOffset() {
    return offsetof(Vertex, m_color);
}

int Vertex::stride() {
    return sizeof(Vertex);
}
