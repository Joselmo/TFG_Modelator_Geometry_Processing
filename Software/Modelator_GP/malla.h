#ifndef MALLA_H
#define MALLA_H


#ifndef _MALLA_H
#define _MALLA_H

#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <QVector

using namespace std;

/**   Representa una malla de puntos en el espacio 3D, utilizando los ejes
*     cartesianos X Y Z
*
*/

/** TUPLA DE REALES
*   Tupla de Coordenadas(x,y,z) de reales.
*/
struct Tupla3r{
private:
  GLfloat coords[3];  // X=0  Y=1   Z=2

public:
  inline GLfloat& operator[](int eje){
      return coords[eje];
  }
};

/** TUPLA DE NATURALES
*   Indica los vertices que forma un triangulo con de naturales.
*/
struct Tupla3n{
private:
  GLuint coords[3];

public:
  inline GLuint& operator[](int eje){
      return coords[eje];
  }
};

/**
* Estructura que contiene la malla basica en 3 dimensiones.
* Funciona con Triangulos.
*/
class Malla{

 private:

  vector<Tupla3r> vertexes;
  vector<Tupla3n> triangles;


 public:
   Malla();
   Malla(vector<Tupla3r> vertex_n,vector<Tupla3n> triangle_n);

   Malla& operator=(const Malla& malla_nueva);

/******************************************************************************
**********               MANEJO DE VERTICES                     ***************
*******************************************************************************/
   void setVertexes(vector<Tupla3r> vertex_n);

   /**
   * Devuelve un puntero a la primera posición del vector de vertices
   */
   Tupla3r *getVertexes();

   /**
   * Devuelve una copia del vector de vertices.
   */
   vector<Tupla3r> getVertexesV();

   /**
   *  Devuelve el número de Vertices de la malla
   */
   int getNumVertexes();

/******************************************************************************
**********               MANEJO DE TRIANGULOS                   ***************
*******************************************************************************/
   void setTriangles(vector<Tupla3n> triangle_n);

   /**
   * Devuelve un puntero a la primera posición del vector de triangulos
   */
   Tupla3n *getTriangles();

   /**
   *  Devuelve una copia del vector de Triangulos
   */
   vector<Tupla3n> getTrianglesV();

   /**
   * Devuelve los triangulos pares de la malla
   */
   vector<Tupla3n> getTrianglesEven();

   /**
   *  Devuelve los triangulos impares de la malla
   */
   vector<Tupla3n> getTrianglesOdd();

   /**
   *  Devuelve el número de Triangulos de la malla
   */
   int getNumTriangles();


};
#endif

#endif // MALLA_H
