#include "window.h"
#include <QDebug>

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/

Window::Window()
{
  m_transform.translate(0.0f, 0.0f, -5.0f);

  cubo.initGeometry("cube.ply");
  esfera.initGeometry("esfera.ply");
  solidmode = false;

}

void Window::initializeGL()
{

  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
  //connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));


  // Set global information
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Application-specific initialization
  {
    // Create Shader (Do not release until VAO is created)
    m_program = new QOpenGLShaderProgram();

    // Compile vertex shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert")){
        printf("ERROR: cargando vertex shader.");
        close();
    }

    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    m_program->link();
    m_program->bind();

        // Cache Uniform Locations
        u_modelToWorld = m_program->uniformLocation("modelToWorld");
        u_worldToCamera = m_program->uniformLocation("worldToCamera");
        u_cameraToView = m_program->uniformLocation("cameraToView");

        // Create Buffer (Do not release until VAO is created)
        vbo->create();
        vbo->bind();
        //vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo->allocate(cubo.getPointSg_vertexes(), cubo.getSizeOfGeometry());

    // Create Vertex Array Object
    m_object.create();
    m_object.bind();
    int vertexLocation = m_program->attributeLocation("position");
    m_program->enableAttributeArray(vertexLocation);
    //m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(vertexLocation, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    //m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    m_object.release();
    vbo->release();
    m_program->release();

  }
}

void Window::resizeGL(int width, int height)
{
  m_projection.setToIdentity();
  m_projection.perspective(60.0f, width / float(height), 0.1f, 1000.0f);
}

void Window::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render using our shader
  m_program->bind();
  m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
  m_program->setUniformValue(u_cameraToView, m_projection);
  {
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
    m_object.bind();
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
   // glPolygonMode(GL_FRONT,GL_LINE);
    if(solidmode){
        glDrawArrays(GL_TRIANGLES, 0, cubo.getIndices().size());
    }else{
        for(int i = 0; i <  cubo.getIndices().size(); i += 3)
          glDrawArrays(GL_LINE_LOOP, i, 3);
    }

    m_object.release();

  }
  m_program->release();
}

void Window::teardownGL()
{
  // Actually destroy our OpenGL information
  m_object.destroy();
  vbo->destroy();
  delete m_program;
}

void Window::update()
{
  // Update input
  Input::update();

  if(Input::keyReleased(Qt::Key_F1)){
      std::cout << "Pulsada F1"<<std::endl;
      solidmode != solidmode;
  }
  // Camera Transformation
  if (Input::buttonPressed(Qt::RightButton))
  {
    static const float transSpeed = 0.3f;
    static const float rotSpeed   = 0.3f;

    // Handle rotations
    m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
    m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());

    // Handle translations
    QVector3D translation;
    if (Input::keyPressed(Qt::Key_W))
    {
      translation += m_camera.forward();
    }
    if (Input::keyPressed(Qt::Key_S))
    {
      translation -= m_camera.forward();
    }
    if (Input::keyPressed(Qt::Key_A))
    {
      translation -= m_camera.right();
    }
    if (Input::keyPressed(Qt::Key_D))
    {
      translation += m_camera.right();
    }
    if (Input::keyPressed(Qt::Key_Q))
    {
      translation -= m_camera.up();
    }
    if (Input::keyPressed(Qt::Key_E))
    {
      translation += m_camera.up();
    }
    m_camera.translate(transSpeed * translation);
  }

  // Update instance information
  //m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

  // Schedule a redraw
  QOpenGLWindow::update();
}

void Window::keyPressEvent(QKeyEvent *event)
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

void Window::keyReleaseEvent(QKeyEvent *event)
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

void Window::mousePressEvent(QMouseEvent *event)
{
  Input::registerMousePress(event->button());
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
  Input::registerMouseRelease(event->button());
}

