#include "connectivity.h"

Connectivity::Connectivity(){

}

void Connectivity::collapse(HalfEdge _h, QVector<HalfEdge> *_he,Malla &_mesh){
    // Inicializo las variables necesarias
    HalfEdge  h  = _h;
    HalfEdge  hn = _he->at(h.getNext_halfedge());
    HalfEdge  hp = _he->at(h.getPrevious());

    HalfEdge  o  = _he->at(h.getOposite());
    HalfEdge  on = _he->at(o.getNext_halfedge());
    HalfEdge  op = _he->at(o.getPrevious());

    int      fh = h.getFace();
    int      fo = o.getFace();

    Vertex  *vh = h.getVertex_in();
    Vertex  *vo = h.getVertex_out();

    // Recorro todas las semi-aristas que inciden en el vértice vo(origen)
    // ahora inciden sobre vh(destino)
    for(int hivo:vo->getAllHalfEdgesIn()){
        (*_he)[hivo].setVertex_in(vh);
    }

    //Eliminamos las caras adyacentes a h
    _mesh.indices.remove(fh);
    _mesh.indices.remove(fo);

    // Elimino la semi-arista de las entradas de vh
    vh->removeHalfEdgeIn(h.getId());
    vh->removeHalfEdgeOut(o.getId());


    // Elimino la semi-arista de las salidas de vo
    vo->removeHalfEdgeOut(h.getId());
    vo->removeHalfEdgeIn(o.getId());

    //Actualizo las conexiones de h
    // Ahora la semi-arista siguiente de la anterior es la siguiente
    hp.setNext_halfedge(hn.getId());
    // Ahora la semi-arista anterior de la siguiente es la anterior
    hn.setPrevious(hp.getId());

    //TODO: Checkear
    // Recorro todas las semi-aristas que salen en el vértice vo(origen)
    // ahora salen de vh(destino)
    // Ajusto los indices, ahora donde era vo es vh
    int pos;
    int stride;
    for(int hovo:vo->getAllHalfEdgesOut()){
        pos= (*_he)[hovo].getFace();
        stride = _mesh.indices.at(pos).indexOf(vo->getId());
        //Cambiamos los indice de la cara
        std::cout<<"pos="<<pos<<" Indice"<<stride<<std::endl;
        if(stride>=0)
            _mesh.indices[pos].replace(_mesh.indices.at(pos).indexOf(vo->getId()),vh->getId());


        vh->addHalfEdgeOut((*_he)[hovo].getId());
    }


    //Eliminar elementos de vh,vo y h* que ya no sirvan



    //TODO: Eliminar Vertice y los indices
    // Eliminamos el vértice collapsado
    //_mesh.vertices.remove(vo->getId());



    _he->remove(h.getId());
    _he->remove(o.getId());

    //eliminar ciclos creados
    // Si la siguiente de la siguiente es la misma, es un ciclo
    if( (*_he)[hn.getNext_halfedge()].getNext_halfedge() == hn.getId() )
        collapse_loop(hn,_he);

    // Si la siguiente de la siguiente de la opuesta es la misma es un ciclo
    if( (*_he)[on.getNext_halfedge()].getNext_halfedge() == on.getId() )
        collapse_loop(on,_he);

}

void Connectivity::collapse_loop(HalfEdge _h, QVector<HalfEdge> *_he){

    HalfEdge  h0 = _h;
    HalfEdge  h1 = _he->at(h0.getNext_halfedge());

    HalfEdge  o0 = _he->at(h0.getOposite());
    //HalfEdge  o1 = _he->at(h1.getOposite());

    Vertex   *v0 = h0.getVertex_in();
    Vertex   *v1 = h1.getVertex_in();

    //(next_halfedge_handle(h1) == h0) && (h1 != o0)
    // Comprobamos si es un ciclo
    if(h1.getNext_halfedge() == h0.getId() && h1.getId() != o0.getId() ){

        // Re-asignamos las semi-aristas
        h1.setNext_halfedge(o0.getNext_halfedge());
        (*_he)[o0.getPrevious()].setNext_halfedge(h1.getId());

        //Re-asignamos semi-aristas de los vértices
        v0->removeHalfEdgeOut(o0.getId());
        v0->removeHalfEdgeIn(h0.getId());

        v1->removeHalfEdgeOut(h0.getId());
        v1->removeHalfEdgeIn(o0.getId());


        _he->remove(h0.getId());
        _he->remove(o0.getId());
    }

}






















