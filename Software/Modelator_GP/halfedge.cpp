#include "halfedge.h"

int HalfEdge::getId() const
{
    return id;
}

void HalfEdge::setId(int _value)
{
    id = _value;
}

float HalfEdge::getErrorRemove() const
{
    return error_remove;
}

void HalfEdge::setErrorRemove(float _value)
{
    error_remove = _value;
}

HalfEdge::HalfEdge(){
    
}

Face *HalfEdge::getFace()
{
    return face;
}

void HalfEdge::setFace(Face *_value)
{
    face = _value;
}

Vertex *HalfEdge::getVertexIn()
{
    return vertex_in;
}

void HalfEdge::setVertexIn(Vertex *_value)
{
    vertex_in = _value;
}

Vertex *HalfEdge::getVertexOut()
{
    return vertex_out;
}

void HalfEdge::setVertexOut(Vertex *_value)
{
    vertex_out = _value;
}

HalfEdge *HalfEdge::getNextHalfedge()
{
    return next_halfedge;
}

void HalfEdge::setNextHalfedge(HalfEdge *_value)
{
    next_halfedge = _value;
}

HalfEdge *HalfEdge::getOposite()
{
    return oposite;
}

void HalfEdge::setOposite(HalfEdge *_value)
{
    oposite = _value;
}

HalfEdge *HalfEdge::getPrevious()
{
    return previous;
}

void HalfEdge::setPrevious(HalfEdge *_value)
{
    previous = _value;
}


