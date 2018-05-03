#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{

    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);

    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(4,4);
    setFormat(format);

    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    openGLFuncions = context->functions();


    rotation = 10;
    cubo.createGeometry();
    cubo.setColorAll(1,0.65,0,0,1);

    Observer_angle_x+=30;
    Observer_angle_y-=10;

    mesh_scale = 1.0;

}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{

    glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
    glEnable(GL_CULL_FACE);   // Habilita la cara frontal solo

    this->change_projection();
    Width=this->width()/10;
    Height=this->height()/10;
    glViewport(0,0,this->width(),this->height());
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    resizeGL(this->width(),this->height());

}

void MainWindow::resizeGL(int w, int h)
{
    change_projection();
    Width=w/10;
    Height=h/10;
    glViewport(0,0,w,h);
}

void MainWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

    change_observer();
    // Draw axis
    ejes.draw();
    // Draw Objects

    cubo.draw(GL_FRONT,2,mesh_scale);



}



void MainWindow::update()
{
  // Update input
  Input::update();

  // Camera Transformation

  if (Input::buttonReleased(Qt::RightButton))
  {
    std::cout<< "pulsado click derecho"<<std::endl;
    static const float transSpeed = 0.5f;
    static const float rotSpeed   = 0.5f;

    // Handle rotations
   // m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
   // m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());

    // Handle translations
    QVector3D translation;
    if (Input::keyPressed(Qt::Key_W))
    {
      //translation += m_camera.forward();
    }

  }

  // Update instance information
  //m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

  // Schedule a redraw
  QOpenGLWindow::update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyPress(event->key());
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyRelease(event->key());
  }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  std::cout<< "pulsado ratón"<<event->button()<<std::endl;

  Input::registerMousePress(event->button());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  Input::registerMouseRelease(event->button());
}



void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(),this->height());
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    paintGL();

}


void MainWindow::change_projection(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}

void MainWindow::change_observer() {

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);
}

