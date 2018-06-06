#include "connectivity.h"

Connectivity::Connectivity()
{

}

void Connectivity::collapse(HalfEdge _h, QVector<HalfEdge> *_he)
{
    // Inicializo las variables necesarias
    HalfEdge  h  = _h;
    HalfEdge  hn = _he->at(h.getNext_halfedge());
    HalfEdge  hp = _he->at(h.getPrevious());

    HalfEdge  o  = _he->at(h.getOposite());
    HalfEdge  on = _he->at(o.getNext_halfedge());
    HalfEdge  op = _he->at(o.getPrevious());

    int *fh = h.getFace();
    int *fo = o.getFace();

    Vertex  *vh = h.getVertex_in();
    Vertex  *vo = h.getVertex_out();

    //TODO completar esto
  //  for (VertexIHalfedgeIter vih_it(vih_iter(vo)); vih_it.is_valid(); ++vih_it)
  //      set_vertex_handle(*vih_it, vh);

    // Recorro todas las semi-aristas que inciden en el vértice vo
    // ahora inciden sobre vh
    //for()

}
