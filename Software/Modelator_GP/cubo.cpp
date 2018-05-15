
#include "cubo.h"
/**
*   Constructores
*/
Cubo::Cubo(){

}

/**
* Construcción de la geometria del tetraedro
*/
void Cubo::createGeometry(){
  // geometria del Cubo (+-1,+-1,+-1)
  // El vertice i corresponde con su interpretación en binario, suponiendo
  // -1 = 0 y 1 = 1;
  vector<glm::vec3> vertices;
  glm::vec3 vertice;

  //            X               Y               Z
  // Vertice 0 base atras izquierda
  vertice[0]= -30;  vertice[1]= -30; vertice[2]=  -30;
  vertices.push_back(vertice);

 // Vertice 1 base delante izquierda
 vertice[0]=  -30;  vertice[1]= -30;vertice[2]=  30;
 vertices.push_back(vertice);

 // Vertice 2 tapa atras izquierda
 vertice[0]=  -30;  vertice[1]= 30; vertice[2]= -30;
 vertices.push_back(vertice);

 // Vertice 3 tapa delante izquierda
 vertice[0]=   -30; vertice[1]= 30; vertice[2]= 30;
 vertices.push_back(vertice);

 // Vertice 4 base atras derecha
 vertice[0]=   30; vertice[1]= -30; vertice[2]= -30;
 vertices.push_back(vertice);

 // Vertice 5 base delante derecha
 vertice[0]=   30; vertice[1]= -30; vertice[2]= 30;
 vertices.push_back(vertice);

 // Vertice 6 tapa atras derecha
 vertice[0]=   30; vertice[1]= 30; vertice[2]= -30;
 vertices.push_back(vertice);

 // Vertice 7 tapa delante derecha
 vertice[0]=   30; vertice[1]= 30; vertice[2]= 30;
 vertices.push_back(vertice);

  vector<glm::ivec3> triangulos;
  glm::ivec3 triangulo;

  // Vertice del triangulo
  //            #                  #                #
  // frontal abajo
  triangulo[0]= 1;  triangulo[1]= 5;  triangulo[2]= 3;
  triangulos.push_back(triangulo);

  // frontal arriba
  triangulo[0]= 5;  triangulo[1]= 7;  triangulo[2]= 3;
  triangulos.push_back(triangulo);

  // lateral derecho abajo
  triangulo[0]= 5;  triangulo[1]= 4;  triangulo[2]= 7;
  triangulos.push_back(triangulo);

  // lateral derecho arriba
  triangulo[0]= 4;  triangulo[1]= 6;  triangulo[2]= 7;
  triangulos.push_back(triangulo);

  // trasera abajo
  triangulo[0]= 6;  triangulo[1]= 4;  triangulo[2]= 0;
  triangulos.push_back(triangulo);

  // trasera arriba
  triangulo[0]= 2;  triangulo[1]= 6;  triangulo[2]= 0;
  triangulos.push_back(triangulo);

  // lateral izquierdo abajo
  triangulo[0]= 0;  triangulo[1]= 1;  triangulo[2]= 2;
  triangulos.push_back(triangulo);

  // lateral izquierdo arriba
  triangulo[0]= 1;  triangulo[1]= 3;  triangulo[2]= 2;
  triangulos.push_back(triangulo);

  // tapa abajo
  triangulo[0]= 3;  triangulo[1]= 7;  triangulo[2]= 2;
  triangulos.push_back(triangulo);

  // tapa arriba
  triangulo[0]= 2;  triangulo[1]= 7;  triangulo[2]= 6;
  triangulos.push_back(triangulo);

  // base abajo
  triangulo[0]= 0;  triangulo[1]= 4;  triangulo[2]= 1;
  triangulos.push_back(triangulo);

  // base arriba
  triangulo[0]= 4;  triangulo[1]= 5;  triangulo[2]= 1;
  triangulos.push_back(triangulo);

  Malla miMalla(vertices,triangulos);
  setMesh(miMalla);

}
