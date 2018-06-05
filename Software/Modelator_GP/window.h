#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "transform3d.h"
#include "camera3d.h"
#include "cubo.h"
#include "malla.h"
#include "input.h"
#include "vertex.h"
#include <QString>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>


class QOpenGLShaderProgram;

/**
 * @brief The Window class, clase princpial que gestiona la escena
 * donde se renderizan los objetos.
 * basada en el código de:  http://www.trentreed.net/blog/qt5-opengl-part-3b-camera-control/
 */
class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
  Q_OBJECT

private:
  // OpenGL State Information
  QOpenGLBuffer m_vertex;
  QOpenGLVertexArrayObject m_object;
  QOpenGLShaderProgram *m_program;
  QOpenGLBuffer *vbo =new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

  QOpenGLVertexArrayObject m_object_cube;
  QOpenGLBuffer *vbo_cube = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);



  // Shader Information
  int u_modelToWorld;
  int u_worldToCamera;
  int u_cameraToView;
  QMatrix4x4 m_projection;
  Camera3D m_camera;
  Transform3D m_transform;

  Malla cubo;
  Malla esfera;
  //Malla bethoven;

  //Control Attributes
  bool solidmode;



// OpenGL Events
public:
  Window();
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
protected slots:
  void teardownGL();
  void update();

protected:
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);



};

#endif // WINDOW_H
