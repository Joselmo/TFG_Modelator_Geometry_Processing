#ifndef MALLA_H
#define MALLA_H

#include <QVector2D>
#include <QVector3D>
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
    QVector<Vertex> vertices;       // Array de vértices
    QVector<Vertex> sg_vertices;    // Array de vértices ordenados por indices
    QVector<Face> indices;// Array de los indices de las caras, van de 3 en 3
    QVector<HalfEdge> half_edges;   // Array de semi-aristas


public:
    Malla();
    Malla(QVector<Vertex> _vertex, QVector<Face> _index);

    Malla& operator=(const Malla& _malla);

    /**
     * @brief getSg_vertexes
     * @return devuelve el QVector<Vertex> de vértices ordenados por indices
     */
    QVector<Vertex> getSgVertexes() const;
    /**
     * @brief setSg_vertexes
     * @param value array de vértices ordenados para dibujar.
     */
    void setSgVertexes(const QVector<Vertex> &_value);

    /**
     * @brief getVertices
     * @return devuelve el QVector<Vertex> del listado de vértices.
     */
    QVector<Vertex> getVertices() const;


    /**
     * @brief setVertices
     * @param value array de vértices de la malla
     */
    void setVertices(const QVector<Vertex> &_value);

    /**
     * @brief getIndices
     * @return devuelve el QVector<int> de indices de la malla.
     */
    QVector<Face> getIndices() const;

    /**
     * @brief setIndices
     * @param value array de indices de la malla
     */
    void setIndices(const QVector<Face > &_value);

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
    QVector<HalfEdge> *getHalfEdges();
};

#endif // MALLA_H
