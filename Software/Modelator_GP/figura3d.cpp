
#include "figura3d.h"
#include <iostream>
/**
*   Constructores
*/
Figura3D::Figura3D(){
    mode[0]=GL_FILL;
    mode[1]=GL_POINT;
    mode[2]=GL_LINE; // 0 = Relleno   1 = Puntos   2 = Lineas
}


/******************************************************************************
*********                 MANEJO DE LA MALLA                     **************
*******************************************************************************/
void Figura3D::setMesh(Malla malla){
    mesh = malla;
    color_vector.resize(mesh.getVertexesV().size());
    mesh_even = Malla(mesh.getVertexesV(),mesh.getTrianglesEven());
    mesh_odd = Malla(mesh.getVertexesV(),mesh.getTrianglesOdd());

}
/******************************************************************************/
Malla Figura3D::getMesh(){
    return mesh;
}

/******************************************************************************
*********             DIBUJADO DE LA FIGURA 3D                   **************
*******************************************************************************/

void Figura3D::drawElements(GLenum face,int mode_view,Malla mesh_draw){
    // especificar que tiene un vector de colores
    glEnableClientState(GL_COLOR_ARRAY);
    // especificar el vector de colores
    glColorPointer(3, GL_FLOAT, 0, &(color_vector.at(0)));
    // especificar que tiene un vector de vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    // especificar puntero a tabla de coords. de vértices
    glVertexPointer(3,GL_FLOAT, 0, mesh_draw.getVertexes());
    // Dibuja la Topologia
    glPolygonMode(face,mode[mode_view]);
    // dibuja usando vértices indexados
    glDrawElements( GL_TRIANGLES, 3*mesh_draw.getNumTriangles(), GL_UNSIGNED_INT, mesh_draw.getTriangles());

}

/******************************************************************************/

void Figura3D::draw(GLenum face,int mode_view,GLfloat n){
    glScalef(n,n,n);

    drawElements(face,mode_view,mesh);
}

/******************************************************************************
*********          TRANSFORMACION DE LA FIGURA 3D                **************
*******************************************************************************/

void Figura3D::scale(GLfloat x,GLfloat y,GLfloat z){
    glScalef(x,y,z);
}

void Figura3D::scale(GLfloat n){
    std::cout << "Escalando \n";
    glScalef(n,n,n);
}


void Figura3D::setColorAll(float r,float g,float b,int inicio,int inc){
    Tupla3r rgb;
    //color_vector.clear();
    rgb[0]= r;
    rgb[1]= g;
    rgb[2]= b;
    for(int i=inicio; i < color_vector.size(); i+=inc){
        color_vector[i] = rgb;
    }
}

int Figura3D::getNumVertices()
{
    return mesh.getNumVertexes();
}

int Figura3D::getNumFaces()
{
    return mesh.getNumTriangles();
}
