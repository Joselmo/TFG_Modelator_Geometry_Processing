#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "halfedge.h"

class Connectivity
{

private:


public:
    Connectivity();

    /**
     * @brief Colapsa un vértice Va sobre Vb,
     * mediante la semi-arista que incide sobre Va desde Vb
     *
     * @param _h semi-arista que representa el colapso
     */
    void collapse(HalfEdge _h, QVector<HalfEdge> *_he);

};

#endif // CONNECTIVITY_H
