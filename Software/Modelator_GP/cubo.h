#ifndef CUBO_H
#define CUBO_H
#include <QVector2D>
#include <QVector3D>
#include "vertex.h"
#include <QVector>


using namespace std;

class Cubo{

public:
    Cubo();
    virtual ~Cubo();

    QVector<Vertex> getSg_vertexes();
    void setSg_vertexes(const QVector<Vertex> &value);

    QVector<Vertex> getVertices();
    void setVertices(const QVector<Vertex> &value);

    QVector<int> getIndices();
    void setIndices(const QVector<int> &value);

    Vertex *getPointSg_vertexes();

    int getSizeOfGeometry();

    void initCubeGeometry();
    void generateGeometry();


private:
    QVector<Vertex> vertices;
    QVector<Vertex> sg_vertexes;
    Vertex* sg_vertexes1;
    QVector<int> indices;





};
#endif // CUBO_H
