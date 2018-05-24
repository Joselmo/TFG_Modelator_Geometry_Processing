#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <glm/glm.hpp>


class HalfEdge{
public:
    HalfEdge();

    /**
     * @brief getNext HalfEdge
     * @return reference of next half-edge inside of face
     */
    HalfEdge * getNext();

    /**
     * @brief getPrevious HalfEdge.
     * @return reference of a previous half-edge inside of face
     */
    HalfEdge * getPrevious();

    /**
     * @brief getOpposite HalfEdge
     * @return reference of a oposite half-edge.
     */
    HalfEdge *getOposite();

    /**
     * @brief getVertex
     * @return
     */
    glm::vec3 *getVertex() const;
    void setVertex(glm::vec3 *value);

    /**
     * @brief getFace
     * @return
     */
    glm::ivec3 *getFace() const;
    void setFace(glm::ivec3 *value);

private:

    //References
    glm::vec3 *vertex;  // Vertex Incident
    glm::ivec3 *face;   // Face
    HalfEdge *next_halfedge;    // Next HalfEdge inside of face
    HalfEdge *oposite;  // Oposite halfedge
    HalfEdge *previous; // Previous halfedge inside of face


};

#endif // HALFEDGE_H
