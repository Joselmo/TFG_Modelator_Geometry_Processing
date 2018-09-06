#ifndef QVERTEX_H
#define QVERTEX_H

#include <QVector3D>
#include <QVector>
#include <QLinkedList>
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
  QLinkedList<HalfEdge*> half_edges_in;
  QLinkedList<HalfEdge*> half_edges_out;
  int id;

public:
  // Constructors
   Vertex();
   explicit Vertex(const QVector3D &_position);
   Vertex(const QVector3D &_position, const QVector3D &_color);

  // Accessors / Mutators
  /**
   * @brief Devuelve el vector con la posición del vértice.
   *
   */
  const QVector3D& position() const;

  /**
   * @brief devulve el color del vértice en formato vector, donde
   * la primera posición es el valor de Red,
   * la segunda posición es el valor de Green,
   * la tercera posición es el valor de Blue,
   *
   */
  const QVector3D& color() const;

  /**
   * @brief Establece la posición del vértice mediante un vector.
   *
   * @param _position vector con la posición del vértice.
   */
  void setPosition(const QVector3D & _position);

  /**
   * @brief Establece el color del vértice, en formato vector RGB.
   *
   * @param _color vector con el color del vértice.
   */
  void setColor(const QVector3D& _color);

  /**
   * @brief añade una semi-arista al vector de semi-aristas que
   * inciden sobre el vértice.
   *
   * @param _half_edge referencia a la semi-arista que incide sobre el vértice.
   */
  void addHalfEdgeIn(HalfEdge *_half_edge);

  /**
   * @brief obtiene una referencia de la semi-arista  que
   * incide sobre el vértice según el indice.
   *
   * @param _index posición de la semi-arista que desemaos obtener.
   */
  HalfEdge *getHalfEdgeIn(int _index);

  /**
   * @brief obtiene una lista enlaza de semi-aristas que
   * inciden sobre el vértice.
   *
   */
  QLinkedList<HalfEdge*> getAllHalfEdgesIn();

  /**
   * @brief obtiene una referencia a la lista enlaza de semi-aristas que
   * inciden sobre el vértice.
   *
   */
  QLinkedList<HalfEdge*> *getAllHalfEdgesInPtr();

  /**
   * @brief elimina una semi-arista de su listado de semi-aristas
   * que inciden en el vértice.
   *
   * @param _index posición de la semi-arista que desemaos eliminar.
   */
  void removeHalfEdgeIn(int _index);

  /**
   * @brief elimina una semi-arista de su listado de semi-aristas
   * que inciden en el vértice.
   *
   * @param _half_edge referencia de la semi-arista que desemaos eliminar.
   */
  void removeHalfEdgeIn(HalfEdge *_half_edge);

  /**
   * @brief añade una semi-arista al vector de semi-aristas que
   * salen del vértice.
   *
   * @param _half_edge referencia a la semi-arista que sale del vértice.
   */
  void addHalfEdgeOut(HalfEdge *_half_edge);

  /**
   * @brief obtiene una referencia de la semi-arista  que
   * sale del vértice según el indice.
   *
   * @param _index posición de la semi-arista que desemaos obtener.
   */
  HalfEdge *getHalfEdgeOut(int _index);

  /**
   * @brief obtiene una lista enlaza de semi-aristas que
   * salen del vértice.
   *
   */
  QLinkedList<HalfEdge*> getAllHalfEdgesOut();

  /**
   * @brief obtiene una referencia a la lista enlaza de semi-aristas que
   * salen del vértice.
   *
   */
  QLinkedList<HalfEdge*> *getAllHalfEdgesOutPtr();

  /**
   * @brief elimina una semi-arista de su listado de semi-aristas
   * que salen del vértice.
   *
   * @param _index posición de la semi-arista que desemaos eliminar.
   */
  void removeHalfEdgeOut(int _index);

  /**
   * @brief elimina una semi-arista de su listado de semi-aristas
   * que salen del vértice.
   *
   * @param _half_edge referencia de la semi-arista que desemaos eliminar.
   */
  void removeHalfEdgeOut(HalfEdge *_half_edge);


  /**
   * @brief Devuelve el Id del Vértice.
   *
   */
  int getId() const;

  /**
   * @brief asigna el Id al vértice
   *
   * @param _value id que se le asigna al vértice.
   */
  void setId(int _value);


  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 3;
  static  int positionOffset();
  static  int colorOffset();
  static  int stride();

  bool operator==(const Vertex &rhs) const {
         return rhs.id == this->id;
  }


};


#endif // QVERTEX_H
