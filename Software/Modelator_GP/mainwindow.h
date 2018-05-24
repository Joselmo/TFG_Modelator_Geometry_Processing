#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QtOpenGL>
#include <QtGui/QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include <QMatrix4x4>
#include <QQuaternion>

// Internal Classes
#include <ejes.h>
#include <cubo.h>
#include <input.h>
#include <sphere.h>
#include "plyreader.h"
#include "camera3d.h"
#include <transform3d.h>

// tamano de los ejes
#define AXIS_SIZE 5000

class QOpenGLShaderProgram;

class MainWindow : public QOpenGLWindow,protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    Cubo cubo;
    // Sphere sphere;
    //Figura3D object;



public slots:
    //void UpdateAnimation();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

   // void resizeEvent(QResizeEvent *event);
   // void paintEvent(QPaintEvent *event);

/*
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
*/
    void initShaders();

private:

    QOpenGLContext *context;

    QOpenGLFunctions *openGLFuncions;


    // OpenGL State Information
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

    // Shader Information
    int u_modelToWorld;
    int u_worldToCamera;
    int u_cameraToView;
    QMatrix4x4 m_projection;
    Camera3D m_camera;
    Transform3D m_transform;

    // Private Helpers
    void printVersionInformation();
/*
    //Transformacion de camara
    void change_projection();
    void change_observer();

    //Mode Picker
    void setModePicket();

    //Interaccion con la escena
    void ratonRueda(int direction);
    void ratonMovido(int x,int y);
    void clickRaton(int boton, bool estado, int x, int y);
    float rotation;
    Ejes ejes;
*/

/*
    Camera camara_1;
    Camera camara_2;
    Camera camara_3;
    Camera camaras[3];
    int camaraActiva;
    GLdouble pos_cam_x;
    GLdouble pos_cam_z;
    GLdouble pos_cam_y;

    int MOVIENDO_CAMARA_FIRSTPERSON = 0;
    int MODO_EXAMINAR = 1;
    int estadoRaton = -1;
*/
    int xant,yant;

    // Variables de control
    int mode_view;
    GLfloat mesh_scale;
    int MODE;
    int PICKER = 1;
    int MOUSE_RIGHT_BUTTON = 0;
    int MOUSE_LEFT_BUTTON = 1;

    // variables que definen la posicion de la camara en coordenadas polares
/*    GLfloat Observer_distance;
    GLfloat Observer_position_x;
    GLfloat Observer_position_y;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width,Height,Front_plane,Back_plane;
*/

};

#endif // MAINWINDOW_H
