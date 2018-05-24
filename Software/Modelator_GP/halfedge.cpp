#include "halfedge.h"

HalfEdge::HalfEdge(){

}

HalfEdge *HalfEdge::getNext(){
    return next_halfedge;
}

HalfEdge *HalfEdge::getPrevious(){
    return previous;
}

HalfEdge *HalfEdge::getOposite(){
    return oposite;
}

glm::vec3 *HalfEdge::getVertex() const
{
    return vertex;
}

void HalfEdge::setVertex(glm::vec3 *value)
{
    vertex = value;
}

glm::ivec3 *HalfEdge::getFace() const
{
    return face;
}

void HalfEdge::setFace(glm::ivec3 *value)
{
    face = value;
}
