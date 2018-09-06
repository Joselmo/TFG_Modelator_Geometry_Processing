#ifndef MALLA_H
#define MALLA_H

#include <QVector2D>
#include <QVector3D>
#include <QLinkedList>
#include "vertex.h"
#include <vector>
#include "halfedge.h"
#include "connectivity.h"
#include "face.h"
#include <functional>
#include <queue>
#include <vector>

#include <iostream>
#include <iterator>
#include <string>
// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <OpenMesh/Core/Mesh/PolyConnectivity.hh>
// ----------------------------------------------------------------------------
using namespace OpenMesh;
// ----------------------------------------------------------------------------
typedef TriMesh_ArrayKernelT<>  MyMesh;
typedef  std::priority_queue<HalfEdge, QVector<HalfEdge>, std::less<QVector<HalfEdge>::value_type> > priority_q;

// ----------------------------------------------------------------------------

/**
* @brief Estructura que contiene la malla basica en 3 dimensiones.
* La malla contiene vértices, un array de indices para las caras y un array
* de semi-aristas aladas.
* @author Jose Luis Martínez Ortiz
*/
class Connectivity;


class Malla{

private:
    friend Connectivity;
    QLinkedList<Vertex> vertices;       // Array de vértices
    QVector<Vertex> sg_vertices;    // Array de vértices ordenados por indices
    QLinkedList<Face> indices;// Array de los indices de las caras, van de 3 en 3
    QLinkedList<HalfEdge> half_edges;   // Array de semi-aristas


public:
    Malla();
    Malla(QLinkedList<Vertex> _vertex, QLinkedList<Face> _index);

    Malla& operator=(const Malla& _malla);

    /**
     * @brief getSg_vertexes
     * @return devuelve el QVector<Vertex> de vértices ordenados por indices
     */
    QVector<Vertex> getSgVertexes();
    /**
     * @brief setSg_vertexes
     * @param value array de vértices ordenados para dibujar.
     */
    void setSgVertexes(QVector<Vertex> &_value);

    /**
     * @brief getVertices
     * @return devuelve el QVector<Vertex> del listado de vértices.
     */
    QLinkedList<Vertex> getVertices();

    QLinkedList<Vertex> *getVerticesPtr();


    /**
     * @brief setVertices
     * @param value array de vértices de la malla
     */
    void setVertices(QLinkedList<Vertex> &_value);

    /**
     * @brief getIndices
     * @return devuelve el QVector<int> de indices de la malla.
     */
    QLinkedList<Face> getIndices();

    QLinkedList<Face> *getIndicesPtr();

    /**
     * @brief setIndices
     * @param value array de indices de la malla
     */
    void setIndices(QLinkedList<Face> &_value);

    /**
     * @brief getPointSg_vertexes
     * @return devuelve un puntero a la primera posición del array de vértices ordenados
     */
    Vertex *getPointSgVertexes();

    /**
     * @brief getSizeOfGeometry
     * @return el tamaño del vector de  indices.
     */
    int getSizeOfGeometry();

    /**
     * @brief initGeometry lee una malla ply e inicializa la malla
     * @param filename fichero PLY donde está la malla
     */
    void initGeometry(std::string _filename);

    /**
     * @brief generateGeometry genera el array de vértices ordenados
     * requiere que la malla tenga inicializados los vértices e indices
     */
    void generateGeometry();

    /**
      * @brief generateSurfaceNormals genera todas las normales de cara
      * en cada cara.
      */
    void generateSurfaceNormals();

    /**
     * @brief getHalf_edges devuelve un puntero al vector de semi-aristas
     * @return
     */
    QLinkedList<HalfEdge> *getHalfEdgesPtr();

    QLinkedList<HalfEdge> getHalfEdges();

};

#endif // MALLA_H
