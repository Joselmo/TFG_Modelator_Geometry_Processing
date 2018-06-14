#include "halfedge.h"

int HalfEdge::getId() const
{
    return id;
}

void HalfEdge::setId(int value)
{
    id = value;
}

HalfEdge::HalfEdge(){

}

Face *HalfEdge::getFace()
{
    return face;
}

void HalfEdge::setFace(Face *value)
{
    face = value;
}

Vertex *HalfEdge::getVertex_in()
{
    return vertex_in;
}

void HalfEdge::setVertex_in(Vertex *value)
{
    vertex_in = value;
}

Vertex *HalfEdge::getVertex_out()
{
    return vertex_out;
}

void HalfEdge::setVertex_out(Vertex *value)
{
    vertex_out = value;
}

HalfEdge *HalfEdge::getNext_halfedge()
{
    return next_halfedge;
}

void HalfEdge::setNext_halfedge(HalfEdge *value)
{
    next_halfedge = value;
}

HalfEdge *HalfEdge::getOposite()
{
    return oposite;
}

void HalfEdge::setOposite(HalfEdge *value)
{
    oposite = value;
}

HalfEdge *HalfEdge::getPrevious()
{
    return previous;
}

void HalfEdge::setPrevious(HalfEdge *value)
{
    previous = value;
}


