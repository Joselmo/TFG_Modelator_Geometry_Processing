#ifndef MALLA_H
#define MALLA_H


#ifndef _MALLA_H
#define _MALLA_H

#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <QVector3D>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

/**   Representa una malla de puntos en el espacio 3D, utilizando los ejes
*     cartesianos X Y Z
*
*/


/**
* Estructura que contiene la malla basica en 3 dimensiones.
* Funciona con Triangulos.
*/
class Malla{

 private:

  vector<glm::vec3> vertexes;
  vector<glm::ivec3> triangles;


 public:
   Malla();
   Malla(vector<glm::vec3> vertex_n,vector<glm::ivec3> triangle_n);

   Malla& operator=(const Malla& malla_nueva);

/******************************************************************************
**********               MANEJO DE VERTICES                     ***************
*******************************************************************************/
   void setVertexes(vector<glm::vec3> vertex_n);

   /**
   * Devuelve un puntero a la primera posición del vector de vertices
   */
   glm::vec3 *getVertexes();

   /**
   * Devuelve una copia del vector de vertices.
   */
   vector<glm::vec3> getVertexesV();

   /**
   *  Devuelve el número de Vertices de la malla
   */
   int getNumVertexes();

/******************************************************************************
**********               MANEJO DE TRIANGULOS                   ***************
*******************************************************************************/
   void setTriangles(vector<glm::ivec3> triangle_n);

   /**
   * Devuelve un puntero a la primera posición del vector de triangulos
   */
   glm::ivec3 *getTriangles();

   /**
   *  Devuelve una copia del vector de Triangulos
   */
   vector<glm::ivec3> getTrianglesV();

   /**
   * Devuelve los triangulos pares de la malla
   */
   //vector<glm::ivec3> getTrianglesEven();

   /**
   *  Devuelve los triangulos impares de la malla
   */
   //vector<glm::ivec3> getTrianglesOdd();

   /**
   *  Devuelve el número de Triangulos de la malla
   */
   int getNumTriangles();


};
#endif

#endif // MALLA_H
