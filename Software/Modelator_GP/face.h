#ifndef FACE_H
#define FACE_H

#include <QVector>
#include <vertex.h>

class Vertex;

class Face{

private:
    QVector<Vertex> vertices;
    static const int MAX_POSITION = 3;
    int id;


public:
    Face();

    QVector<Vertex> getVertices() const;
    void setVertices(const QVector<Vertex> &_value);

    Vertex getVertices(int _index);
    void addVertex(Vertex &_value);
    void addVertex(int _index,Vertex &_value);
    void remplaceVertex(Vertex &_vertexOld, Vertex &_vertexNew);
    void clear();

    int getId() const;
    void setId(int value);
};

#endif // FACE_H
