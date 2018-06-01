#ifndef HALFEDGE_H
#define HALFEDGE_H

#include "vertex.h"
#include <QVector3D>


class HalfEdge{
public:
    HalfEdge();


    /**
     * @brief getFace
     * @return
     */
    int *getFace();
    void setFace(int *value);

    /**
     * @brief getVertex_in
     * @return
     */
    Vertex *getVertex_in();
    void setVertex_in(Vertex *value);

    /**
     * @brief getVertex_out
     * @return
     */
    Vertex *getVertex_out();
    void setVertex_out(Vertex *value);

    /**
     * @brief getNext_halfedge
     * @return
     */
    int getNext_halfedge();
    void setNext_halfedge(int value);

    /**
     * @brief getOposite
     * @return
     */
    int getOposite();
    void setOposite(int value);

    /**
     * @brief getPrevious
     * @return
     */
    int getPrevious();
    void setPrevious(int value);

private:

    //References
    Vertex *vertex_in;  // Vertex Incident
    Vertex *vertex_out; // Vertex Source
    int *face;   // Face
    int next_halfedge;    // Next HalfEdge inside of face
    int oposite;  // Oposite halfedge
    int previous; // Previous halfedge inside of face


};

#endif // HALFEDGE_H
