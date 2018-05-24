
#include "cubo.h"
/**
*   Constructores
*/
Cubo::Cubo() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

Cubo::~Cubo()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Cubo::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    QVector3D vertices[] = {

        {QVector3D(-1.0f, -1.0f,  -1.0f)},  // v0
        {QVector3D(-1.0f, -1.0f,   1.0f)},  // v1
        {QVector3D(-1.0f,  1.0f,  -1.0f)},  // v2
        {QVector3D(-1.0f,  1.0f,   1.0f)},  // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v4
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v5
        {QVector3D( 1.0f,  1.0f, -1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f,  1.0f)}, // v7
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         1, 5, 3, // frontal abajo
         5, 7, 3, // frontal arriba
         5, 4, 7, // lateral derecho abajo
         4, 6, 7, // lateral derecho arriba
         6, 4, 0,  // trasera abajo
         2, 6, 0, // trasera arriba
         0, 1, 2, // lateral izquierdo abajo
         1, 3, 2,// lateral izquierdo arriba
         3, 7, 2,// tapa abajo
         2, 7, 6,// tapa arriba
         0, 4, 1,// base abajo
         4, 5, 1// base arriba
    };

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 8 * sizeof(QVector3D));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 36 * sizeof(GLushort));
//! [1]
}

//! [2]
void Cubo::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}
//! [2]
