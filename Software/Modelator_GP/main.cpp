#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::cout<<"Main:.. inicio"<<std::endl;
        MainWindow w;
        std::cout<<"Main:.. inicio"<<std::endl;

        w.setTitle("Test QT5 OpenGL");
        w.resize(640,480);
        w.show();

    return a.exec();
}
