#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "halfedge.h"
#include "malla.h"
#include "QtMath"
#include <functional>
#include <queue>
#include <vector>
#include <cmath>

#include <QLinkedListIterator>

typedef  std::priority_queue<HalfEdge, QVector<HalfEdge>, std::less<QVector<HalfEdge>::value_type> > priority_q;

class Malla;

/**
 * @brief The Connectivity class
 * @author Jose Luis Martínez Ortiz
 *
 * Procesado geometrico de una malla, clase que contiene la funcionalidad
 * de algoritmos de procesado geometrico, algoritmos que contiene:
 * - Collapse
 * - Decimation
 */
class Connectivity{

private:

    /**
     * @brief Calcula el angulo entre dos vectores
     *
     * @param _u primer vector.
     * @param _v segundo vector.
     * @param _result angulo que forman los vectores _u y _v
     */
    void angleVector(const QVector3D &_u, const QVector3D &_v, float &_result);

    /**
     * @brief Calcula el error que produce si se elimina la semi-aristas
     * _he y lo actualiza en su atributo
     *
     * @param _he referncia a la semi-arista que se va a calcular el error.
     */
    void calcOneRingError(HalfEdge *_he);

public:
    Connectivity();

    /**
     * @brief Colapsa un vértice Va sobre Vb,
     * mediante la semi-arista que incide sobre Va desde Vb
     *
     * @param _h referencia a la semi-arista que representa el colapso de vértices
     * @param _mesh referencia a la malla.
     */
    void collapse(HalfEdge *_h, Malla *_mesh);

    /**
     * @brief Genera una priority queue de HalfEdge
     * la queue está priorizara por el error más bajo de las
     * semi-aristas.
     *
     * @param _mesh referencia a la malla
     * @param _pq referencia a la priority queue que se va a rellenar.
     */
    void generateLowerErrorQueue(Malla *_mesh, priority_q &_pq);

    /**
     * @brief Reduce la malla siguiendo un porcentaje de reducción a aplicar,
     * siempre reduce de forma que se generan los menos errores posibes.
     *
     * @param _mesh referencia a la malla
     * @param _reduction porcentaje de reducción a aplicar, se indica en valor de 0 a 1.
     */
    void decimation(Malla *_mesh, float _reduction);





};

#endif // CONNECTIVITY_H
