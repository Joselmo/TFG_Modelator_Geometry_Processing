#ifndef QVERTEX_H
#define QVERTEX_H

#include <QVector3D>
#include <QVector>
#include <halfedge.h>

/**
 * @brief The Vertex class
 * @author Jose Luis Martínez Ortiz
 * @author http://www.trentreed.net/blog/qt5-opengl-part-3b-camera-control/
 *
 */

class HalfEdge;

class Vertex {

private:
  QVector3D m_position;
  QVector3D m_color;
  QVector<int> half_edges_in;
  QVector<int> half_edges_out;
  int id;

public:
  // Constructors
   Vertex();
   explicit Vertex(const QVector3D &_position);
   Vertex(const QVector3D &_position, const QVector3D &_color);

  // Accessors / Mutators
   const QVector3D& position() const;
   const QVector3D& color() const;
  void setPosition(const QVector3D & _position);
  void setColor(const QVector3D& _color);

  void addHalfEdgeIn(int _half_edge);
  void setHalfEdgeIn(QVector<int> _half_edges);
  int getHalfEdgeIn(int _index);
  QVector<int> getAllHalfEdgesIn();
  void removeHalfEdgeIn(int _index);

  void addHalfEdgeOut(int _half_edge);
  void setHalfEdgeOut(QVector<int> _half_edges);
  int getHalfEdgeOut(int _index);
  QVector<int> getAllHalfEdgesOut();
  void removeHalfEdgeOut(int _index);


  int getId() const;
  void setId(int value);


  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 3;
  static  int positionOffset();
  static  int colorOffset();
  static  int stride();


};


#endif // QVERTEX_H
