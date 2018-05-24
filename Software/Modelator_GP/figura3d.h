#ifndef FIGURA3D_H
#define FIGURA3D_H

using namespace std;

#define N_EJES 3  // Nº de ejes

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "malla.h"

/** CLASE FIGURA 3D
* Genera una figura 3D mediante una malla de puntos y una topología
* Se puede personalizar la forma de visualización y el color de la misma
*
*/

class Figura3D : protected QOpenGLFunctions{

private:
  Malla mesh;   // Malla de puntos
  GLenum mode[3]; // Modo de visualización

  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;

  void initGeometry();


public:
  /**
  * Constructor con parametros
  */
    Figura3D();

    ~Figura3D();


  /**
  * Cambia la vista de la figura según la opción
  */
    void changeView();

  /** Dibuja una figura 3D
  * @param face indica que parte se dibuja
  * @param mode_view indica la Topologia, si se visualiza en puntos,lineas,
  *                   o ajedrez
  * @param color indica el color con el que se dibuja la figura
  *
  */
    void draw(GLenum face,int mode_view,GLfloat n);

    /*
    * Dibuja la figura utilizando glDrawElements
    */
    void drawShapeGeometry(QOpenGLShaderProgram *m_program, int mode_view);


  /**
  * Translación
  */
  void translation(GLfloat x,GLfloat y, GLfloat z);

  /** Rotación
  *
  */

  /** Escalado
  * Realiza un escalado a cada coordenada o a todas el mismo
  */
  void scale(GLfloat x,GLfloat y,GLfloat z);
  void scale(GLfloat n);


  void setColorAll(float r, float g, float b);

  int getNumVertices();
  int getNumFaces();

  /**
  * Métodos de acceso a la malla
  */
  void setMesh(Malla malla);

protected:
  /**
  * Crea la figura 3d de forma virtual, con lo que el hijo es quien se encarga de realizarla
  vector<float> vertex, vector<unsigned int> triangle
  */
  virtual void createGeometry(){};

  Malla getMesh();



};
#endif // FIGURA3D_H
