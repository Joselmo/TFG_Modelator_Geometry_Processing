#include "connectivity.h"

Connectivity::Connectivity()
{

}

void Connectivity::collapse(HalfEdge _h)
{
    // Inicializo las variables necesarias
    HalfEdge  h  = _h;
    HalfEdge  hn = h.getNext_halfedge();
    HalfEdge  hp = h.getPrevious();

    HalfEdge  o  = h.getOposite();
    HalfEdge  on = o.getNext_halfedge();
    HalfEdge  op = o.getPrevious();

    int *fh = h.getFace();
    int *fo = o.getFace();

    Vertex  *vh = h.getVertex_in();
    Vertex  *vo = h.getVertex_out();

    //TODO completar esto
    for (VertexIHalfedgeIter vih_it(vih_iter(vo)); vih_it.is_valid(); ++vih_it)
        set_vertex_handle(*vih_it, vh);

    // Recorro todas las semi-aristas que inciden en el vértice vo
    // ahora inciden sobre vh
    for()

}
