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

int HalfEdge::getFace()
{
    return face;
}

void HalfEdge::setFace(int value)
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

int HalfEdge::getNext_halfedge()
{
    return next_halfedge;
}

void HalfEdge::setNext_halfedge(int value)
{
    next_halfedge = value;
}

int HalfEdge::getOposite()
{
    return oposite;
}

void HalfEdge::setOposite(int value)
{
    oposite = value;
}

int HalfEdge::getPrevious()
{
    return previous;
}

void HalfEdge::setPrevious(int value)
{
    previous = value;
}


