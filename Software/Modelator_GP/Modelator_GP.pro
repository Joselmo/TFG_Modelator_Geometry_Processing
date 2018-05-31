#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T22:30:22
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -lglut -glu32
LIBS += \
    /usr/local/lib/libOpenMeshCore.so  \
    /usr/local/lib/libOpenMeshTools.so

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Modelator_GP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        ejes.cpp \
        malla.cpp \
        cubo.cpp \
        input.cpp \
    plyreader.cpp \
    halfedge.cpp \
    sphere.cpp \
    transform3d.cpp \
    camera3d.cpp \
    window.cpp

HEADERS += \
        ejes.h \
        malla.h \
        cubo.h \
        input.h \
    plyreader.h \
    halfedge.h \
    sphere.h \
    transform3d.h \
    camera3d.h \
    vertex.h \
    window.h

FORMS +=

RESOURCES += \
    resources.qrc
