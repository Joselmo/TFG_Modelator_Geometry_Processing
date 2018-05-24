
#include "malla.h"

Malla::Malla(){}

/** Constructor parametrizado
* Crea una malla dados un vector de vertices y uno de triangulos
*/
Malla::Malla(vector<QVector3D> vertex_n, vector<glm::ivec3> triangle_n){
  setVertexes(vertex_n);
  setTriangles(triangle_n);
}


/**
* Sobrecarga del operador asignación
* Copia los vectores de triangulos y vertices
*/
Malla& Malla::operator=(const Malla& malla_nueva){
    cout << "copiando malla" << endl;
      if(this != &malla_nueva){
        setVertexes(malla_nueva.vertexes);
        setTriangles(malla_nueva.triangles);

        //color_vectex.clear();
        //color_vectex_odd.clear();
        //color_vectex.resize(vertexes.size());
        //color_vectex_odd.resize(vertexes.size());

        //generateSurfaceNormal();
        //generateVertexNormal();

        //texture_mapping.clear();
        //texture_mapping = malla_nueva.texture_mapping;

        //center_vertex = malla_nueva.center_vertex;
        //boundingVertex = malla_nueva.boundingVertex;
        //boundingTriangles = malla_nueva.boundingTriangles;
      }
      return *this;
}

/******************************************************************************
**********               MANEJO DE VERTICES                     ***************
*******************************************************************************/
void Malla::setVertexes(vector<QVector3D> vertex_n){
  vertexes.clear();
  vertexes=vertex_n;
  cout<<" Nº vertices="<<vertexes.size();
  for(int i=0; i < vertexes.size(); i++){
      //cout<<"V["<<i<<"] = ["<<vertexes.at(i)[0]<<",";
      //cout<<vertexes.at(i)[1]<<",";
      //cout<<vertexes.at(i)[2]<<"]"<<endl;
  }
}

QVector3D * Malla::getVertexes(){
  return &(vertexes.at(0));
}

vector<QVector3D> Malla::getVertexesV(){
  return vertexes;
}

int Malla::getNumVertexes(){
  return vertexes.size();
}

/******************************************************************************
**********               MANEJO DE TRIANGULOS                   ***************
*******************************************************************************/

void Malla::setTriangles(vector<glm::ivec3> triangle_n){
  triangles.clear();
  triangles = triangle_n;
  cout<<"Nº triangulos="<<triangle_n.size()<<endl;
  for(uint i=0; i < triangle_n.size(); i++){
      //cout<<"F["<<i<<"] = ["<<triangle_n.at(i)[0]<<",";
      //cout<<triangle_n.at(i)[1]<<",";
      //cout<<triangle_n.at(i)[2]<<"]"<<endl;
  }
}

glm::ivec3 *Malla::getTriangles(){
  return &(triangles.at(0));
}

vector<glm::ivec3> Malla::getTrianglesV(){
   return triangles;
}
/*
vector<glm::ivec3> Malla::getTrianglesEven(){
  vector<glm::ivec3> trianglesEven;

  for(int i=0; i<triangles.size();i+=2){
    trianglesEven.push_back(triangles.at(i));
  }

  return trianglesEven;
}

vector<glm::ivec3> Malla::getTrianglesOdd(){
  vector<glm::ivec3> trianglesOdd;

  for(int i=1; i<triangles.size();i+=2){
    trianglesOdd.push_back(triangles.at(i));
  }

  return trianglesOdd;
}
*/

int Malla::getNumTriangles(){
   return triangles.size();
}
