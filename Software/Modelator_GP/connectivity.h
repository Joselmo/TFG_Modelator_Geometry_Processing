#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "halfedge.h"
#include "malla.h"
#include "QtMath"

class Malla;
class Connectivity{

private:

    void angleVector(QVector3D &_u, QVector3D &_v, float &_result);

public:
    Connectivity();

    /**
     * @brief Colapsa un vértice Va sobre Vb,
     * mediante la semi-arista que incide sobre Va desde Vb
     *
     * @param _h semi-arista que representa el colapso
     */
    void collapse(HalfEdge _h, QVector<HalfEdge> *_he, Malla *_mesh);

    void collapse_loop(HalfEdge _h, QVector<HalfEdge> *_he);



};

#endif // CONNECTIVITY_H
