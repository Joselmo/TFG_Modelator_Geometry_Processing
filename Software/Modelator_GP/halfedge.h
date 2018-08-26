#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <vertex.h>
#include <QVector3D>
#include <face.h>

/**
 * @brief The HalfEdge class
 * @author Jose Luis Martínez Ortiz
 *
 * Clase para al gestión de una semi-arista alada
 * asociada al array de semi-aristas aladas de una malla
 */
class Vertex;
class Face;
class HalfEdge{
private:

    //References
    int id;             // Index in the array
    Vertex *vertex_in;  // Vertex Incident
    Vertex *vertex_out; // Vertex Source
    Face *face;         // Face incident
    HalfEdge *next_halfedge;  // Next HalfEdge inside of face
    HalfEdge *oposite;        // Oposite halfedge
    HalfEdge *previous;       // Previous halfedge inside of face

    float error_remove;




public:
    HalfEdge();


    /**
     * @brief getFace
     * @return devuelve la posición de la cara incidente
     */
    Face* getFace();

    /**
     * @brief setFace
     * @param value referencia a la posición de la cara incidente
     */
    void setFace(Face *_value);

    /**
     * @brief getVertex_in
     * @return devuelve la posición del vértice al que apunta.
     */
    Vertex *getVertexIn();

    /**
     * @brief setVertex_in
     * @param value referencia a la posición del vértice al que apunta
     */
    void setVertexIn(Vertex *_value);

    /**
     * @brief getVertex_out
     * @return devuelve la posición del vértice del que procede.
     */
    Vertex *getVertexOut();

    /**
     * @brief setVertex_out
     * @param value referencia a la posición del vértice del que procede
     */
    void setVertexOut(Vertex *_value);

    /**
     * @brief getNext_halfedge
     * @return la posición del array de la siguiente semi-arista
     */
    HalfEdge *getNextHalfedge();

    /**
     * @brief setNext_halfedge
     * @param value posición del array de semi-aristas aladas de la siguiente semi-arista.
     */
    void setNextHalfedge(HalfEdge *_value);

    /**
     * @brief getOposite
     * @return la posición del array de la semi-arista opuesta.
     */
    HalfEdge *getOposite();

    /**
     * @brief setOposite
     * @param value posición del array de semi-aristas aladas de la semi-arista opuesta.
     */
    void setOposite(HalfEdge *_value);

    /**
     * @brief getPrevious
     * @return la posición del array de semi-aristas aladas de la anterior semi-arista
     */
    HalfEdge* getPrevious();

    /**
     * @brief setPrevious
     * @param value posición del array de semi-aristas aladas de la semi-arista anterior.
     */
    void setPrevious(HalfEdge *_value);


    int getId() const;
    void setId(int _value);
    float getErrorRemove() const;
    void setErrorRemove(float _value);

    //Overload the < operator.
    friend bool operator< (const HalfEdge& _he1, const HalfEdge &_he2)
    {
        return _he1.error_remove > _he2.error_remove;
    }
    //Overload the > operator.
    friend bool operator> (const HalfEdge& _he1, const HalfEdge &_he2)
    {
        return _he1.error_remove < _he2.error_remove;
    }

};

#endif // HALFEDGE_H
