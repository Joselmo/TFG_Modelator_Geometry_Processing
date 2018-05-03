
#include "malla.h"

Malla::Malla(){}

/** Constructor parametrizado
* Crea una malla dados un vector de vertices y uno de triangulos
*/
Malla::Malla(vector<glm::vec3> vertex_n, vector<Tupla3n> triangle_n){
  setVertexes(vertex_n);
  setTriangles(triangle_n);
}


/**
* Sobrecarga del operador asignación
* Copia los vectores de triangulos y vertices
*/
Malla& Malla::operator=(const Malla& malla_nueva){
  if(this != &malla_nueva){
    setVertexes(malla_nueva.vertexes);
    setTriangles(malla_nueva.triangles);
  }
  return *this;
}

/******************************************************************************
**********               MANEJO DE VERTICES                     ***************
*******************************************************************************/
void Malla::setVertexes(vector<glm::vec3> vertex_n){
  vertexes=vertex_n;
}

glm::vec3 * Malla::getVertexes(){
  return &(vertexes.at(0));
}

vector<glm::vec3> Malla::getVertexesV(){
  return vertexes;
}

int Malla::getNumVertexes(){
  return vertexes.size();
}

/******************************************************************************
**********               MANEJO DE TRIANGULOS                   ***************
*******************************************************************************/

void Malla::setTriangles(vector<Tupla3n> triangle_n){
  triangles = triangle_n;
}

Tupla3n * Malla::getTriangles(){
  return &(triangles.at(0));
}

vector<Tupla3n> Malla::getTrianglesV(){
   return triangles;
}

vector<Tupla3n> Malla::getTrianglesEven(){
  vector<Tupla3n> trianglesEven;

  for(int i=0; i<triangles.size();i+=2){
    trianglesEven.push_back(triangles.at(i));
  }

  return trianglesEven;
}

vector<Tupla3n> Malla::getTrianglesOdd(){
  vector<Tupla3n> trianglesOdd;

  for(int i=1; i<triangles.size();i+=2){
    trianglesOdd.push_back(triangles.at(i));
  }

  return trianglesOdd;
}


int Malla::getNumTriangles(){
   return triangles.size();
}
