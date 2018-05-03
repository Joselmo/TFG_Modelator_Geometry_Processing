#include "mainwindow.h"
#include "infodialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setTitle("Test QT5 OpenGL");
    w.resize(640,480);
    w.show();



    return a.exec();
}
