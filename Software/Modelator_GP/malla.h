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
* Estructura que contiene la malla basica en 3 dimensiones.
* Funciona con Triangulos.
*/
class Malla{

private:

    QVector<Vertex> vertices;
    QVector<Vertex> sg_vertices;
    QVector<int> indices;
    QVector<HalfEdge> half_edges;


public:
    Malla();
    Malla(QVector<Vertex> vertex_n, QVector<int> indices_n);

    Malla& operator=(const Malla& malla_nueva);

    QVector<Vertex> getSg_vertexes() const;
    void setSg_vertexes(const QVector<Vertex> &value);

    QVector<Vertex> getVertices() const;
    void setVertices(const QVector<Vertex> &value);

    QVector<int> getIndices() const;
    void setIndices(const QVector<int> &value);

    Vertex *getPointSg_vertexes();

    int getSizeOfGeometry();

    void initGeometry(std::string filename);
    void generateGeometry();


};

#endif // MALLA_H
