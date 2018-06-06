#include <vertex.h>


/*******************************************************************************
 *  ructor
 ******************************************************************************/
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

void Vertex::addHalfEdgeIn(int _half_edge)
{
    half_edges_in.push_back(_half_edge);
}

void   Vertex::setHalfEdgeIn(QVector<int> _half_edges) {
    half_edges_in = _half_edges;
}

int   Vertex::getHalfEdgeIn(  int _index) {
    return half_edges_in.at(_index);
}

QVector<int>   Vertex::getAllHalfEdgesIn() {
    return half_edges_in;
}

void   Vertex::addHalfEdgeOut(  int _half_edge) {
    half_edges_out.push_back(_half_edge);
}

void   Vertex::setHalfEdgeOut(QVector<int> _half_edges) {
    half_edges_out = _half_edges;
}

int Vertex::getHalfEdgeOut(  int _index) {
    return half_edges_out.at(_index);
}

QVector<int> Vertex::getAllHalfEdgesOut() {
    return half_edges_out;
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
