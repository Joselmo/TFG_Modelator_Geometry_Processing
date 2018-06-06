#ifndef QVERTEX_H
#define QVERTEX_H

#include <QVector3D>
#include <QVector>

/**
 * @brief The Vertex class
 * @author Jose Luis Martínez Ortiz
 * @author http://www.trentreed.net/blog/qt5-opengl-part-3b-camera-control/
 *
 */

class Vertex {

private:
  QVector3D m_position;
  QVector3D m_color;
  QVector<int> half_edges_in;
  QVector<int> half_edges_out;

public:
  // Constructors
   Vertex();
   explicit Vertex(const QVector3D &_position);
   Vertex(const QVector3D &_position, const QVector3D &_color);

  // Accessors / Mutators
   const QVector3D& position() const;
   const QVector3D& color() const;
  void setPosition(const QVector3D& _position);
  void setColor(const QVector3D& _color);
  void addHalfEdgeIn(const int _half_edge_index);
  void setHalfEdgeIn(const QVector<int> _half_edges);
  int getHalfEdgeIn(const int _index);
  QVector<int> getAllHalfEdgesIn();
  void addHalfEdgeOut(const int _half_edge_index);
  void setHalfEdgeOut(const QVector<int> _half_edges);
  int getHalfEdgeOut(const int _index);
  QVector<int> getAllHalfEdgesOut();



  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 3;
  static  int positionOffset();
  static  int colorOffset();
  static  int stride();


};


#endif // QVERTEX_H
