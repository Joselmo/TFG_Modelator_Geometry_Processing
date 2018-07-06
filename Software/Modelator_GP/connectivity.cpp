#include "connectivity.h"



Connectivity::Connectivity(){

}


void Connectivity::angleVector(QVector3D &_u, QVector3D &_v, float &_result){

    float top = _u[0]*_v[0]+_u[1]*_v[1]+_u[2]*_v[2];

    float root_u = qSqrt(_u[0]*_u[0] + _u[1]*_u[1] + _u[2]*_u[2]);
    float root_v = qSqrt(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]);

    _result = qAcos(top / (root_u * root_v));

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

    //TESTTT
    QVector3D a = fh->getNormal();
    QVector3D b = fo->getNormal();
    float r;
    angleVector(a,b,r);
    std::cout<<"Angulo entre a("<<a[0]<<","
            <<a[1]<<","
            <<a[2]<<") y b("<<b[0]<<","<<
            b[1]<<","<<
            b[2]<<") es = "<<r<<std::endl;


    //TEST FIN


    QVector<Face>::iterator it_f;
    for(it_f = _mesh->indices.begin(); it_f == _mesh->indices.end();++it_f){
        if(it_f->getId() == fh->getId())
            _mesh->indices.erase(it_f);
    }
    for(it_f = _mesh->indices.begin(); it_f == _mesh->indices.end();++it_f){
        if(it_f->getId() == o->getId())
            _mesh->indices.erase(it_f);
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
        if(it->getId() == h.getId())
            _he->erase(it);
    }
    for(it = _he->begin(); it == _he->end();++it){
        if(it->getId() == o->getId())
            _he->erase(it);
    }

    // Recorro todas las semi-aristas que inciden en el vértice vo(origen)
    // ahora inciden sobre vh(destino)
    for(HalfEdge hivo:vo->getAllHalfEdgesIn()){
        //Nivel Indices y vértices
        hivo.getFace()->remplaceVertex((*vo),(*vh));
        std::cout<<"check face="<<hivo.getFace()->getId()<<"\t";
        std::cout<<hivo.getId()<<std::endl;
        //Nivel Semi-aristas
        hivo.setVertex_in(vh);
    }

    // Recorro todas las semi-aristas que salen en el vértice vo(origen)
    // ahora salen de vh(destino)
    // Ajusto los indices, ahora donde era vo es vh
    for(HalfEdge hovo:vo->getAllHalfEdgesOut()){
        //Nivel Indices y vértices
        hovo.getFace()->remplaceVertex((*vo),(*vh));

        // Nivel semi-aristas
        hovo.setVertex_out(vh);

    }

    //TODO: Eliminar Vertice y los indices
    // Eliminamos el vértice collapsado
    std::cout<<"colapso vértice "<<vo->getId()<<" en "<<vh->getId()<<std::endl;
    _mesh->vertices.remove(vo->getId());
    QVector<Vertex>::iterator it_v;
    for(it_v = _mesh->vertices.begin(); it_v == _mesh->vertices.end();++it_v){
        if(it_v->getId() == vo->getId())
            _mesh->vertices.erase(it_v);
    }

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


        QVector<HalfEdge>::iterator it;
        for(it = _he->begin(); it == _he->end();++it){
            if(it->getId()==h0.getId() || it->getId() == o0->getId())
                _he->erase(it);
        }
    }

}






















