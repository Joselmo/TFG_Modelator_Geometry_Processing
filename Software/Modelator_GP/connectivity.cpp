#include "connectivity.h"

Connectivity::Connectivity(){

}

void Connectivity::collapse(HalfEdge _h, QVector<HalfEdge> *_he,Malla *_mesh){
    // Inicializo las variables necesarias
    HalfEdge  h  = _h;
    HalfEdge  *hn = h.getNext_halfedge();
    HalfEdge  *hp = h.getPrevious();

    HalfEdge  *o  = h.getOposite();
    HalfEdge  *on = o->getNext_halfedge();
    HalfEdge  *op = o->getPrevious();

    Face     *fh = h.getFace();
    Face     *fo = o->getFace();

    Vertex  *vh = h.getVertex_in();
    Vertex  *vo = h.getVertex_out();

    //Eliminamos las caras adyacentes a h
    std::cout<<"elimitar cara="<<fh->getId()<<std::endl;
    std::cout<<"elimitar cara="<<fo->getId()<<std::endl;

    int i = 0;
    for(Face f:_mesh->indices){
        if(f.getId() == fh->getId() || f.getId() == fo->getId()){
            _mesh->indices.removeAt(i);
        }else{
            i++;
        }
    }

    for(Face f:_mesh->indices){
        std::cout<<f.getId()<<" ";
    }
    std::cout<<" nºfaces="<<_mesh->indices.size()<<std::endl;

    // Elimino la semi-arista de vh
    vh->removeHalfEdgeIn(h);
    vh->removeHalfEdgeOut((*o));


    // Elimino la semi-arista de vo
    vo->removeHalfEdgeOut(h);
    vo->removeHalfEdgeIn((*o));

    //Actualizo las conexiones de h
    // Ahora la semi-arista siguiente de la anterior es la siguiente
    hp->setNext_halfedge(hn);
    // Ahora la semi-arista anterior de la siguiente es la anterior
    hn->setPrevious(hp);

    //Elimino las semi-aristas implicadas
    QVector<HalfEdge>::iterator it;
    for(it = _he->begin(); it == _he->end();++it){
        if(it->getId()==h.getId() || it->getId() == o->getId())
            _he->erase(it);
    }
//    _he->removeAll(h);
//    _he->removeAll((*o));

    // Recorro todas las semi-aristas que inciden en el vértice vo(origen)
    // ahora inciden sobre vh(destino)
    for(HalfEdge hivo:vo->getAllHalfEdgesIn()){
        //Nivel Indices y vértices


        //Nivel Semi-aristas
        hivo.setVertex_in(vh);
    }

    // Recorro todas las semi-aristas que salen en el vértice vo(origen)
    // ahora salen de vh(destino)
    // Ajusto los indices, ahora donde era vo es vh
    for(HalfEdge hovo:vo->getAllHalfEdgesOut()){

        // Nivel semi-aristas
        hovo.setVertex_out(vh);

    }

    //TODO: Eliminar Vertice y los indices
    // Eliminamos el vértice collapsado
    std::cout<<"colapso vértice "<<vo->getId()<<" en "<<vh->getId()<<std::endl;
    _mesh->vertices.remove(vo->getId());


    //Eliminar elementos de vh,vo y h* que ya no sirvan
//    for(Face faces: _mesh.indices){
//        std::cout<<"cara"<< _mesh.indices.indexOf(faces)<<" - ";
//        for(int &i:faces){
//            if(i==vo->getId()){
//                i=vh->getId();
//                std::cout<<"("<<i<<")";
//            }else if(i > vo->getId()) {
//                i--;
//            }
//            std::cout<<","<<i;
//        }
//        std::cout<<std::endl;
//    }

    //eliminar ciclos creados
    // Si la siguiente de la siguiente es la misma, es un ciclo
    if( hn->getNext_halfedge()->getNext_halfedge()->getId() == hn->getId())
        collapse_loop((*hn),_he);

    // Si la siguiente de la siguiente de la opuesta es la misma es un ciclo
    if( on->getNext_halfedge()->getNext_halfedge()->getId() == on->getId())
        collapse_loop((*on),_he);

}

void Connectivity::collapse_loop(HalfEdge _h, QVector<HalfEdge> *_he){

    HalfEdge  h0 = _h;
    HalfEdge  *h1 = h0.getNext_halfedge();

    HalfEdge  *o0 = h0.getOposite();
    //HalfEdge  o1 = _he->at(h1.getOposite());

    Vertex   *v0 = h0.getVertex_in();
    Vertex   *v1 = h1->getVertex_in();

    //(next_halfedge_handle(h1) == h0) && (h1 != o0)
    // Comprobamos si es un ciclo
    if( h1->getNext_halfedge()->getId() == h0.getId() &&
            h1->getId() != o0->getId()){

        // Re-asignamos las semi-aristas
        h1->setNext_halfedge(o0->getNext_halfedge());
        o0->getPrevious()->setNext_halfedge(h1);

        //Re-asignamos semi-aristas de los vértices
        v0->removeHalfEdgeOut((*o0));
        v0->removeHalfEdgeIn(h0);

        v1->removeHalfEdgeOut(h0);
        v1->removeHalfEdgeIn((*o0));


//        _he->removeAll(h0);
//        _he->removeAll((*o0));
        QVector<HalfEdge>::iterator it;
        for(it = _he->begin(); it == _he->end();++it){
            if(it->getId()==h0.getId() || it->getId() == o0->getId())
                _he->erase(it);
        }
    }

}






















