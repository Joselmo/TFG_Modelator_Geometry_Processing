#include <vertex.h>


/*******************************************************************************
 * Constructor
 ******************************************************************************/
 inline Vertex::Vertex() {}
 inline Vertex::Vertex(const QVector3D &_position)
    : m_position(_position) {}
 inline Vertex::Vertex(const QVector3D &_position, const QVector3D &_color)
    : m_position(_position), m_color(_color) {}


/*******************************************************************************
 * Accessors / Mutators
 ******************************************************************************/
 inline const QVector3D& Vertex::position() const {
    return m_position;
}

 inline const QVector3D& Vertex::color() const {
    return m_color;
}

void inline Vertex::setPosition(const QVector3D& _position) {
    m_position = _position;
}

void inline Vertex::setColor(const QVector3D& _color) {
    m_color = _color;
}

void inline Vertex::addHalfEdgeIn(const int _half_edge_index) {
    half_edges_in.push_back(_half_edge_index);
}

void inline Vertex::setHalfEdgeIn(const QVector<int> _half_edges) {
    half_edges_in = _half_edges;
}

int inline Vertex::getHalfEdgeIn(const int _index) {
    return half_edges_in.at(_index);
}

QVector<int> inline Vertex::getAllHalfEdgesIn() {
    return half_edges_in;
}

void inline Vertex::addHalfEdgeOut(const int _half_edge_index) {
    half_edges_out.push_back(_half_edge_index);
}

void inline Vertex::setHalfEdgeOut(const QVector<int> _half_edges) {
    half_edges_out = _half_edges;
}

int inline Vertex::getHalfEdgeOut(const int _index) {
    return half_edges_out.at(_index);
}

QVector<int> inline Vertex::getAllHalfEdgesOut() {
    return half_edges_out;
}


/*******************************************************************************
 * OpenGL Helpers
 ******************************************************************************/
 inline int Vertex::positionOffset() {
    return offsetof(Vertex, m_position);
}

 inline int Vertex::colorOffset() {
    return offsetof(Vertex, m_color);
}

 inline int Vertex::stride() {
    return sizeof(Vertex);
}
