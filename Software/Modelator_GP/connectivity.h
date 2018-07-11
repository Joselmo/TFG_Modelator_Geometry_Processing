#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "halfedge.h"
#include "malla.h"
#include "QtMath"
#include <functional>
#include <queue>
#include <vector>

typedef  std::priority_queue<float, std::vector<float>, std::greater<float>> priority_q;

class Malla;
class Connectivity{

private:

    void angleVector(const QVector3D &_u, const QVector3D &_v, float &_result);

    void generateLowerErrorQueue(Malla &_mesh);

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

    void generateLowerErrorQueue(Malla *_mesh, priority_q &_pq);





};

#endif // CONNECTIVITY_H
