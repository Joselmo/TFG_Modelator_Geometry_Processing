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
     * @brief devuelve una referencia a la cara de la
     * que forma parte la semi-arista.
     * @return referencia a la cara.
     */
    Face* getFace();

    /**
     * @brief establece la cara de la que forma parte la semi-arista.
     * @param _value referencia a la cara de la que forma parte.
     */
    void setFace(Face *_value);

    /**
     * @brief Obtiene el vértice sobre el que incide la semi-arista
     * @return devuelve una referencia del vértice al que apunta.
     */
    Vertex *getVertexIn();

    /**
     * @brief establece el vértice sobre el que indice la semi-arista
     * @param _value referencia del vértice al que apunta.
     */
    void setVertexIn(Vertex *_value);

    /**
     * @brief Obtiene el vértice del que sale la semi-arista
     * @return devuelve una referencia del vértice del que sale la semi-arista.
     */
    Vertex *getVertexOut();

    /**
     * @brief establece el vértice origen de la semi-arista
     * @param _value referencia del vértice origen de la semi-arista.
     */
    void setVertexOut(Vertex *_value);

    /**
     * @brief Obtiene la siguiente semi-arista, dentro de la misma cara.
     * @return devuelve una referencia de la siguiente semi-arista.
     */
    HalfEdge *getNextHalfedge();

    /**
     * @brief establece la siguiente semi-arista.
     * @param _value referencia de la siguiente semi-arista.
     */
    void setNextHalfedge(HalfEdge *_value);

    /**
     * @brief obtiene la semi-arista opuesta.
     * @return devuelve una referencia de la semi-arista opuesta.
     */
    HalfEdge *getOposite();

    /**
     * @brief establece la semi-arista opuesta
     * @param _value referencia de la semi-arista opuesta.
     */
    void setOposite(HalfEdge *_value);

    /**
     * @brief obtiene la semi-arista anterior, dentro de la misma cara.
     * @return devuelve una referencia de la anterior semi-arista.
     */
    HalfEdge* getPrevious();

    /**
     * @brief establece la semi-arista anterior.
     * @param _value referencia de la semi-arista anterior.
     */
    void setPrevious(HalfEdge *_value);

    /**
     * @brief obtiene el Id de la semi-arista
     */
    int getId() const;

    /**
     * @brief establece el Id de la semi-arista
     * @param _value id de la semi-arista.
     */
    void setId(int _value);

    /**
     * @brief obtiene el error que produce en la malla si se elimina la semi-arista
     *
     */
    float getErrorRemove() const;

    /**
     * @brief establece el error que se produce en la malla si se
     * elimina la semi-arista.
     *
     * @param _value error de eliminar la semi-arista.
     */
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

    bool operator==(const HalfEdge &rhs) const {
           return rhs.id == this->id;
    }

};

#endif // HALFEDGE_H
