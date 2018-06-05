#ifndef MALLA_H
#define MALLA_H

#include <QVector2D>
#include <QVector3D>
#include "vertex.h"
#include <QVector>
#include "halfedge.h"

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
// ----------------------------------------------------------------------------
#define CHKROPT( Option ) \
  std::cout << "  provides " << #Option \
            << (ropt.check(IO::Options:: Option)?": yes\n":": no\n")
#define CHKWOPT( Option ) \
  std::cout << "  write " << #Option \
            << (wopt.check(IO::Options:: Option)?": yes\n":": no\n")
#define MESHOPT( msg, tf ) \
  std::cout << "  " << msg << ": " << ((tf)?"yes\n":"no\n")


/**
* @brief Estructura que contiene la malla basica en 3 dimensiones.
* La malla contiene vértices, un array de indices para las caras y un array
* de semi-aristas aladas.
* @author Jose Luis Martínez Ortiz
*/
class Malla{

private:

    QVector<Vertex> vertices;       // Array de vértices
    QVector<Vertex> sg_vertices;    // Array de vértices ordenados por indices
    QVector<int> indices;           // Array de los indices de las caras, van de 3 en 3
    QVector<HalfEdge> half_edges;   // Array de semi-aristas


public:
    Malla();
    Malla(QVector<Vertex> vertex_n, QVector<int> indices_n);

    Malla& operator=(const Malla& malla_nueva);

    /**
     * @brief getSg_vertexes
     * @return devuelve el QVector<Vertex> de vértices ordenados por indices
     */
    QVector<Vertex> getSg_vertexes() const;
    /**
     * @brief setSg_vertexes
     * @param value array de vértices ordenados para dibujar.
     */
    void setSg_vertexes(const QVector<Vertex> &value);

    /**
     * @brief getVertices
     * @return devuelve el QVector<Vertex> del listado de vértices.
     */
    QVector<Vertex> getVertices() const;
    /**
     * @brief setVertices
     * @param value array de vértices de la malla
     */
    void setVertices(const QVector<Vertex> &value);

    /**
     * @brief getIndices
     * @return devuelve el Qvector<int> de indices de la malla.
     */
    QVector<int> getIndices() const;

    /**
     * @brief setIndices
     * @param value array de indices de la malla
     */
    void setIndices(const QVector<int> &value);

    /**
     * @brief getPointSg_vertexes
     * @return devuelve un puntero a la primera posición del array de vértices ordenados
     */
    Vertex *getPointSg_vertexes();

    /**
     * @brief getSizeOfGeometry
     * @return el tamaño del vector de  indices.
     */
    int getSizeOfGeometry();

    /**
     * @brief initGeometry lee una malla ply e inicializa la malla
     * @param filename fichero PLY donde está la malla
     */
    void initGeometry(std::string filename);

    /**
     * @brief generateGeometry genera el array de vértices ordenados
     * requiere que la malla tenga inicializados los vértices e indices
     */
    void generateGeometry();


};

#endif // MALLA_H
