#ifndef CUBO_H
#define CUBO_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>


using namespace std;

class Cubo : protected QOpenGLFunctions
{
public:
    Cubo();
    virtual ~Cubo();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
    void initCubeGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};
#endif // CUBO_H
