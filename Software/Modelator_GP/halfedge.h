#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <vertex.h>
#include <QVector3D>

/**
 * @brief The HalfEdge class
 * @author Jose Luis Martínez Ortiz
 *
 * Clase para al gestión de una semi-arista alada
 * asociada al array de semi-aristas aladas de una malla
 */
class Vertex;

class HalfEdge{
private:

    //References
    int id;             // Index in the array
    Vertex *vertex_in;  // Vertex Incident
    Vertex *vertex_out; // Vertex Source
    int face;          // Face incident
    int next_halfedge;  // Next HalfEdge inside of face
    int oposite;        // Oposite halfedge
    int previous;       // Previous halfedge inside of face


public:
    HalfEdge();


    /**
     * @brief getFace
     * @return devuelve la posición de la cara incidente
     */
    int getFace();

    /**
     * @brief setFace
     * @param value referencia a la posición de la cara incidente
     */
    void setFace(int value);

    /**
     * @brief getVertex_in
     * @return devuelve la posición del vértice al que apunta.
     */
    Vertex *getVertex_in();

    /**
     * @brief setVertex_in
     * @param value referencia a la posición del vértice al que apunta
     */
    void setVertex_in(Vertex *value);

    /**
     * @brief getVertex_out
     * @return devuelve la posición del vértice del que procede.
     */
    Vertex *getVertex_out();

    /**
     * @brief setVertex_out
     * @param value referencia a la posición del vértice del que procede
     */
    void setVertex_out(Vertex *value);

    /**
     * @brief getNext_halfedge
     * @return la posición del array de la siguiente semi-arista
     */
    int getNext_halfedge();

    /**
     * @brief setNext_halfedge
     * @param value posición del array de semi-aristas aladas de la siguiente semi-arista.
     */
    void setNext_halfedge(int value);

    /**
     * @brief getOposite
     * @return la posición del array de la semi-arista opuesta.
     */
    int getOposite();

    /**
     * @brief setOposite
     * @param value posición del array de semi-aristas aladas de la semi-arista opuesta.
     */
    void setOposite(int value);

    /**
     * @brief getPrevious
     * @return la posición del array de semi-aristas aladas de la anterior semi-arista
     */
    int getPrevious();

    /**
     * @brief setPrevious
     * @param value posición del array de semi-aristas aladas de la semi-arista anterior.
     */
    void setPrevious(int value);


    int getId() const;
    void setId(int value);
};

#endif // HALFEDGE_H
