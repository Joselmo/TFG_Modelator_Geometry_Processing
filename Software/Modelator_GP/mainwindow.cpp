#include "mainwindow.h"


MainWindow::MainWindow()
{
    std::cout<<"MainWindows:constructor .. inicio"<<std::endl;
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

}

MainWindow::~MainWindow()
{
    makeCurrent();
    delete m_program;
    doneCurrent();
}


void MainWindow::initializeGL()
{
    std::cout<<"MainWindows:initializeLG .. inicio"<<std::endl;

    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    //connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    //connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    //printVersionInformation();

    glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    initShaders();


    // Set global information

    glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
    glEnable(GL_CULL_FACE);   // Habilita la cara frontal solo


    std::cout<<"MainWindows:initializeLG .. fin"<<std::endl;
}



void MainWindow::paintGL()
{
    std::cout<<"MainWindows:PaintGL .. inicio "<<std::endl;
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    // matrix.rotate(rotation);

    // Set modelview-projection matrix
    m_program->setUniformValue("mvp_matrix", m_projection * matrix);


    cubo.drawCubeGeometry(m_program);

    std::cout<<"MainWindows:PaintLG .. fin"<<std::endl;


    // Render using our shader
    /*  m_program->bind();
      m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
      m_program->setUniformValue(u_cameraToView, m_projection);
      {
        m_object.bind();
        m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
        object.drawShapeGeometry(m_program,mode_view);
        m_object.release();
      }
      m_program->release();
*/



    /*
    glClear(GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    change_observer();
    // Draw axis
    ejes.draw();
    // Draw Objects
    object.draw(GL_FRONT,mode_view,mesh_scale);
    //cubo.draw(GL_FRONT,mode_view,mesh_scale);

    //Draw Mode Picker
    if(MODE == PICKER){
        //sphere.draw(GL_FRONT,0,2);
    }
    */
}


/*
void MainWindow::update()
{
    // Update input
    Input::update();

    // Camera Transformation
      if (Input::buttonPressed(Qt::RightButton))
      {
        static const float transSpeed = 0.2f;
        static const float rotSpeed   = 0.2f;

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
        m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

    if (Input::keyReleased(Qt::Key_1)){
        mode_view = 0;
        std::cout<<"Modo visualización: relleno"<<std::endl;
    }
    if (Input::keyReleased(Qt::Key_2)){
        mode_view = 1;
        std::cout<<"Modo visualización: puntos"<<std::endl;
    }
    if (Input::keyReleased(Qt::Key_3)){
        mode_view = 2;
        std::cout<<"Modo visualización: alambre"<<std::endl;
    }
    if (Input::keyReleased(Qt::Key_Plus)){
        mesh_scale++;
        std::cout<<"Escalado x"<<mesh_scale<<std::endl;
    }
    if (Input::keyReleased(Qt::Key_Minus)){
        mesh_scale--;
        std::cout<<"Escalado x"<<mesh_scale<<std::endl;
    }
    if (Input::keyReleased(Qt::Key_9)){
        //setModePicket();
        std::cout<<"Modo seleccionar"<<std::endl;
    }


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
*/
void MainWindow::initShaders()
{
    std::cout<<"MainWindows:initShaders .. inicio"<<std::endl;
    // Create Shader (Do not release until VAO is created)
    m_program = new QOpenGLShaderProgram();

    // Compile vertex shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert")){
        std::cout<<"ERROR: Loading Vertex Shader."<<std::endl;
        close();
    }
    // Compile Fragment Shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/simple.frag")){
        std::cout<<"ERROR: Loading fragment Shader."<<std::endl;
        close();
    }

    // Link shader pipeline
    if (!m_program->link()){
        std::cout<<"ERROR: link Shader."<<std::endl;
        close();
    }

    // Bind shader pipeline for use
    if(!m_program->bind()){
        std::cout<<"ERROR: Bind Shader."<<std::endl;
        close();
    }

    // Cache Uniform Locations
    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToCamera = m_program->uniformLocation("worldToCamera");
    u_cameraToView = m_program->uniformLocation("cameraToView");
    std::cout<<"MainWindows:initShaders .. fin"<<std::endl;
}


void MainWindow::resizeGL(int w, int h)
{
    std::cout<<"MainWindows:resizeGL .. inicio"<<std::endl;
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    m_projection.setToIdentity();

    // Set perspective projection
    m_projection.perspective(fov, aspect, zNear, zFar);

    std::cout<<"MainWindows:resizeGL.. fin"<<std::endl;
    /*    change_projection();
    Width=w/10;
    Height=h/10;
    glViewport(0,0,w,h);
*/
}
