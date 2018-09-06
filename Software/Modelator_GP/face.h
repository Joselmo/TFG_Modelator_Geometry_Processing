#ifndef FACE_H
#define FACE_H

#include <QVector>
#include <vertex.h>
#include <iostream>


class Vertex;

/**
 * @brief The Face class
 * @author Jose Luis Martínez Ortiz
 *
 * Clase para al gestión de una cara
 * La cara está compuesta de 3 Vertex que la definen.
 */
class Face{

private:
    QVector<Vertex> vertices;
    static const int MAX_POSITION = 3;
    int id;
    QVector3D normal;


public:
    Face();

    /**
     * @brief Devuelve el Id de la cara.
     *
     */
    int getId() const;

    /**
     * @brief Establece el Id de la cara.
     */
    void setId(int _value);

    /**
     * @brief Devuelve el vector de la normal de cara.
     *
     */
    QVector3D getNormal();

    /**
     * @brief Establece la normal de cara mediante un vector.
     *
     * @param _value vector de la normal de cara.
     */
    void setNormal(const QVector3D &_value);

    /**
     * @brief establece la normal de cara mediante las coordenadas del
     * vector que la forma.
     *
     * @param _posx coordenada X.
     * @param _posy coordenada Y.
     * @param _posz coordenada Z.
     */
    void setNormal(float _posx, float _posy, float _posz);

    /**
     * @brief Obtiene los vértices que forman la cara.
     *
     */
    QVector<Vertex> getVertices() const;

    /**
     * @brief Establece los vértices que forman la cara
     *
     * @param _value vector de vertex que forman la cara.
     */
    void setVertices(const QVector<Vertex> &_value);

    /**
     * @brief Obtiene el vértice indicado de entre los que
     * forman la cara.
     *
     * @param _index indica la posición del vértice a obtener
     * de entre los tres posibles.
     */
    Vertex getVertices(int _index);

    /**
     * @brief Añade un vértice al vector de vértices de la cara
     * para así formar la cara.
     *
     * @param _value vértice a añadir
     */
    void addVertex(Vertex &_value);

    /**
     * @brief Añade un vértice al vector de vértices de la cara
     * para así formar la cara y su posición.
     *
     * @param _index posición donde se va a añadir el vértice
     * @param _value vértice a añadir
     */
    void addVertex(int _index,Vertex &_value);

    /**
     * @brief Encuentra el vértice _vertexOld y lo reemplaza por
     * _vertexNew si existe.
     *
     * @param _vertexOld vértice a reemplazar.
     * @param _vertexNew vértice nuevo que sustituirá a _vertexOld
     */
    void remplaceVertex(Vertex &_vertexOld, Vertex &_vertexNew);

    /**
     * @brief Calcula la normal de cara de la cara.
     *
     */
    void generateSurfaceNormal();

    /**
     * @brief Limpia el vector de vértices.
     */
    void clear();

    /**
     * @brief Sobrecarga del operador comparación, dos caras son iguales
     * si tienen la misma id.
     *
     * @param rhs cara con la que comparar.
     */
    bool operator==(const Face &rhs) const {
           return rhs.id == this->id;
    }
};

#endif // FACE_H
