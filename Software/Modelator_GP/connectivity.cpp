#include "connectivity.h"



Connectivity::Connectivity(){

}


void Connectivity::angleVector(QVector3D const &_u, QVector3D const &_v, float &_result){

    float top = _u[0]*_v[0]+_u[1]*_v[1]+_u[2]*_v[2];

    float root_u = qSqrt(_u[0]*_u[0] + _u[1]*_u[1] + _u[2]*_u[2]);
    float root_v = qSqrt(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]);

    _result = qAcos(top / (root_u * root_v));

    if(std::isnan(_result))
        _result=10000;

}

void Connectivity::calcOneRingError(HalfEdge *_he){
    float error_calculated = 0;
    float angle = 0;
    Face *face_source = _he->getFace();
    Face *face;
    for(HalfEdge heo: _he->getVertexOut()->getAllHalfEdgesIn()){

        face = heo.getFace();
        if( face_source->getId() != face->getId()){
            angleVector(face_source->getNormal(),face->getNormal(),angle);
            error_calculated += angle;
//            std::cout<<"face_source="<<face_source->getId()<<"-"<<face->getId()<<"="<<angle<<std::endl;;
        }

    }

    if(std::isnan(error_calculated))
        error_calculated=10000;

    _he->setErrorRemove(error_calculated);

}

void Connectivity::generateLowerErrorQueue(Malla *_mesh, priority_q &_pq){


    // Genero las Normales de cara por si han cambiado
    _mesh->generateSurfaceNormals();

    float error_calculated = 0;
    //Calculamos el error producido por cada HE si se elimina
    // Se extrae las he y sus caras implicadas en el cálculo
//    for(HalfEdge *he:_mesh->getHalf_edges()){
    QVector<HalfEdge>::iterator he;
    for(he=_mesh->getHalfEdges()->begin();
        he != _mesh->getHalfEdges()->end(); ++he){
        error_calculated = 0;
//        std::cout<<he->getId()<<"#"<<face_source->getId()<<"-";
        calcOneRingError(he);
//        std::cout<<"&&"<<error_calculated<<std::endl;
        _pq.push(*he);

    }


}

void Connectivity::decimation(Malla *_mesh, float _reduction){

    int n_triangles = _mesh->getIndices().size();
    int n_triangles_final = n_triangles * _reduction;
    int reductions = (n_triangles - n_triangles_final) / 2;

    std::cout<<"ntf="<<n_triangles_final
            <<"nt="<<n_triangles
            <<"_red="<<_reduction
            <<std::endl;

    std::cout<<"Nº of reductions="<<reductions<<std::endl;

    priority_q pq,pq1;
    generateLowerErrorQueue( _mesh, pq);

    pq1 = pq;


    std::cout<<"Priority QUEUE: "<<std::endl;
    while(!pq1.empty()) {
           std::cout << pq1.top().getId() << "("<< pq1.top().getErrorRemove()<<") - " ;
           pq1.pop();
       }
    std::cout << '\n';

    HalfEdge _he;
    for(int i=0; i < reductions; i++){
        _he = pq.top();
        // Simplified the lower error half edge

        std::cout<<"reduction "<<_he.getId()<<"&&"<<_he.getFace()->getId()<<"-"<<_he.getOposite()->getFace()->getId()<<std::endl;
        if(_he.getFace()->getId() != _he.getOposite()->getFace()->getId()){
            if(!std::isnan(_he.getErrorRemove())){
                collapse(_he,_mesh->getHalfEdges(),_mesh);
            }else{
                std::cout<<"valor no valido"<<std::endl;
            }
        }

        // Remove from the list
        pq.pop();
        //generateLowerErrorQueue( _mesh, pq);
    }




}


void Connectivity::collapse(HalfEdge _h, QVector<HalfEdge> *_he,Malla *_mesh){
    // Inicializo las variables necesarias
    HalfEdge  h  = _h;
    HalfEdge  *hn = h.getNextHalfedge();
    HalfEdge  *hp = h.getPrevious();

    HalfEdge  *o  = h.getOposite();
    HalfEdge  *on = o->getNextHalfedge();
    HalfEdge  *op = o->getPrevious();

    Face     *fh = h.getFace();
    Face     *fo = o->getFace();

    Vertex  *vh = h.getVertexIn();
    Vertex  *vo = h.getVertexOut();

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
    for(it_f = _mesh->indices.begin(); it_f != _mesh->indices.end();++it_f){
//        std::cout<<" "<<it_f->getId();
        if(it_f->getId() == fh->getId()){
            _mesh->indices.erase(it_f);
//            std::cout<<"cara="<<it_f->getId()<<" eliminada"<<std::endl;
        }
    }
    for(it_f = _mesh->indices.begin(); it_f != _mesh->indices.end();++it_f){
        if(it_f->getId() == fo->getId())
            _mesh->indices.erase(it_f);
//            std::cout<<"cara="<<it_f->getId()<<" eliminada"<<std::endl;
    }

//    for(Face f:_mesh->indices){
//        std::cout<<f.getId()<<" ";
//    }
    std::cout<<" nºfaces="<<_mesh->indices.size()<<std::endl;

    // Elimino la semi-arista de vh
    vh->removeHalfEdgeIn(h);
    vh->removeHalfEdgeOut((*o));


    // Elimino la semi-arista de vo
    vo->removeHalfEdgeOut(h);
    vo->removeHalfEdgeIn((*o));

    //Actualizo las conexiones de h
    // Ahora la semi-arista siguiente de la anterior es la siguiente
    hp->setNextHalfedge(hn);
    // Ahora la semi-arista anterior de la siguiente es la anterior
    hn->setPrevious(hp);

    //Elimino las semi-aristas implicadas
    QVector<HalfEdge>::iterator it;
    for(it = _he->begin(); it != _he->end();++it){
        if(it->getId() == h.getId())
            _he->erase(it);
    }
    for(it = _he->begin(); it != _he->end();++it){
        if(it->getId() == o->getId())
            _he->erase(it);
    }

    // Recorro todas las semi-aristas que inciden en el vértice vo(origen)
    // ahora inciden sobre vh(destino)
    for(HalfEdge hivo:vo->getAllHalfEdgesIn()){
        //Nivel Indices y vértices
        hivo.getFace()->remplaceVertex((*vo),(*vh));
        hivo.getFace()->generateSurfaceNormal();
//        std::cout<<"check face="<<hivo.getFace()->getId()<<"\t";
//        std::cout<<hivo.getId()<<std::endl;
        //Nivel Semi-aristas
        hivo.setVertexIn(vh);
    }

    // Recorro todas las semi-aristas que salen en el vértice vo(origen)
    // ahora salen de vh(destino)
    // Ajusto los indices, ahora donde era vo es vh
    for(HalfEdge hovo:vo->getAllHalfEdgesOut()){
        //Nivel Indices y vértices
        hovo.getFace()->remplaceVertex((*vo),(*vh));
        hovo.getFace()->generateSurfaceNormal();
        // Nivel semi-aristas
        hovo.setVertexOut(vh);

    }

    //TODO: Eliminar Vertice y los indices
    // Eliminamos el vértice collapsado
    std::cout<<"colapso vértice "<<vo->getId()<<" en "<<vh->getId()<<std::endl;
    _mesh->vertices.remove(vo->getId());
    QVector<Vertex>::iterator it_v;
    for(it_v = _mesh->vertices.begin(); it_v != _mesh->vertices.end();++it_v){
        if(it_v->getId() == vo->getId())
            _mesh->vertices.erase(it_v);
    }

    //eliminar ciclos creados
    // Si la siguiente de la siguiente es la misma, es un ciclo
    if( hn->getNextHalfedge()->getNextHalfedge()->getId() == hn->getId())
        collapse_loop((*hn),_he);

    // Si la siguiente de la siguiente de la opuesta es la misma es un ciclo
    if( on->getNextHalfedge()->getNextHalfedge()->getId() == on->getId())
        collapse_loop((*on),_he);



}

void Connectivity::collapse_loop(HalfEdge _h, QVector<HalfEdge> *_he){

    HalfEdge  h0 = _h;
    HalfEdge  *h1 = h0.getNextHalfedge();

    HalfEdge  *o0 = h0.getOposite();
    //HalfEdge  o1 = _he->at(h1.getOposite());

    Vertex   *v0 = h0.getVertexIn();
    Vertex   *v1 = h1->getVertexIn();

    //(next_halfedge_handle(h1) == h0) && (h1 != o0)
    // Comprobamos si es un ciclo
    if( h1->getNextHalfedge()->getId() == h0.getId() &&
            h1->getId() != o0->getId()){

        // Re-asignamos las semi-aristas
        h1->setNextHalfedge(o0->getNextHalfedge());
        o0->getPrevious()->setNextHalfedge(h1);

        //Re-asignamos semi-aristas de los vértices
        v0->removeHalfEdgeOut((*o0));
        v0->removeHalfEdgeIn(h0);

        v1->removeHalfEdgeOut(h0);
        v1->removeHalfEdgeIn((*o0));


        QVector<HalfEdge>::iterator it;
        for(it = _he->begin(); it != _he->end();++it){
            if(it->getId()==h0.getId() || it->getId() == o0->getId())
                _he->erase(it);
        }
    }

}






















