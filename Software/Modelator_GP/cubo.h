#ifndef CUBO_H
#define CUBO_H
#include "figura3d.h"
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class Cubo : public Figura3D {


public:
    Cubo();
  void createGeometry();

};
#endif // CUBO_H
