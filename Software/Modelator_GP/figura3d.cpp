
#include "figura3d.h"
#include <iostream>
/**
*   Constructores
*/

Figura3D::Figura3D():indexBuf(QOpenGLBuffer::IndexBuffer){
    mode[0]=GL_FILL;
    mode[1]=GL_POINT;
    mode[2]=GL_LINE; // 0 = Relleno   1 = Puntos   2 = Lineas

    //Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // transfers geometry to VBOs
    initGeometry();

}

Figura3D::~Figura3D(){
    arrayBuf.destroy();
    indexBuf.destroy();
}


void Figura3D::initGeometry()
{
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(mesh.getVertexes(),sizeof(mesh.getVertexesV()));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(mesh.getTriangles(), mesh.getNumTriangles() * sizeof(QVector3D));
}


/******************************************************************************
*********                 MANEJO DE LA MALLA                     **************
*******************************************************************************/
void Figura3D::setMesh(Malla malla){
    mesh = malla;
    //color_vector.resize(mesh.getVertexes().size());

}
/******************************************************************************/
Malla Figura3D::getMesh(){
    return mesh;
}

/******************************************************************************
*********             DIBUJADO DE LA FIGURA 3D                   **************
*******************************************************************************/
void Figura3D::drawShapeGeometry(QOpenGLShaderProgram *m_program, int mode_view)
{

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = m_program->attributeLocation("position");
    m_program->enableAttributeArray(vertexLocation);
    m_program->setAttributeBuffer(vertexLocation,
                                  GL_FLOAT,
                                  0,
                                  3,
                                  sizeof(QVector3D));

    // Tell OpenGL programmable pipeline how to locate vertex color data
/*    int colorLocation = m_program->attributeLocation("color");
    m_program->enableAttributeArray(colorLocation);
    m_program->setAttributeBuffer(colorLocation,
                                  GL_FLOAT,
                                  Vertex::colorOffset(),
                                  Vertex::ColorTupleSize,
                                  Vertex::stride());
*/
    // Draw geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 3*mesh.getNumTriangles(), GL_UNSIGNED_SHORT, 0);
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


void Figura3D::setColorAll(float r,float g,float b){
   /* QVector3D rgb;
    //color_vector.clear();
    rgb[0]= r;
    rgb[1]= g;
    rgb[2]= b;
    for(int i=0; i < color_vector.size(); i++){
        color_vector[i] = rgb;
    }*/
}

int Figura3D::getNumVertices()
{
    return mesh.getNumVertexes();
}

int Figura3D::getNumFaces()
{
    return mesh.getNumTriangles();
}
