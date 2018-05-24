#ifndef PLYREADER_H
#define PLYREADER_H



#include <iostream>
#include <iterator>
#include <string>
// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <malla.h>
#include <QVector3D>
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



class PLYReader{


public:
    PLYReader();
    void readPLY(Malla &malla, string file);
};

#endif // PLYREADER_H
