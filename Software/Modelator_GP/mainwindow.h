#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <ejes.h>
#include <cubo.h>
#include <QKeyEvent>
#include <input.h>
#include <iostream>


// tama�o de los ejes
#define AXIS_SIZE 5000


class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    //void UpdateAnimation();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);


    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


protected slots:
    void update();



private:
    QOpenGLContext *context;

    QOpenGLFunctions *openGLFuncions;

    //Transformaci�n de c�mara
    void change_projection();
    void change_observer();

    float rotation;
    Ejes ejes;
    Cubo cubo;

    // Variables de control
    int mode_view;
    char figura;
    GLfloat mesh_scale;

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width,Height,Front_plane,Back_plane;


};

#endif // MAINWINDOW_H
