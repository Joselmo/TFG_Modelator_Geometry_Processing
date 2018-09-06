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

    QLinkedList<HalfEdge*>::iterator it_hivo;
    for(it_hivo = _he->getVertexOut()->getAllHalfEdgesInPtr()->begin();
        it_hivo != _he->getVertexOut()->getAllHalfEdgesInPtr()->end();
        ++it_hivo){

        if( face_source->getId() != (*it_hivo)->getFace()->getId()){
            angleVector(face_source->getNormal(),(*it_hivo)->getFace()->getNormal(),angle);
            error_calculated += angle;
        }
    }

    if(std::isnan(error_calculated))
        error_calculated=10000;

    _he->setErrorRemove(error_calculated);

}

void Connectivity::generateLowerErrorQueue(Malla *_mesh, priority_q &_pq){


    // Genero las Normales de cara por si han cambiado
    _mesh->generateSurfaceNormals();
    while(!_pq.empty())
        _pq.pop();

    //Calculamos el error producido por cada HE si se elimina
    // Se extrae las he y sus caras implicadas en el cálculo
    QLinkedListIterator<HalfEdge> i(_mesh->getHalfEdges());
    HalfEdge semiarista;
    while (i.hasNext()){
        semiarista = i.next();
//        std::cout<<"haldedge="<<semiarista.getId()<<std::endl;
        calcOneRingError(&semiarista);
        _pq.push(semiarista);

    }
}

void Connectivity::decimation(Malla *_mesh, float _reduction){

    int n_triangles = _mesh->getIndices().size();
    int n_triangles_final = n_triangles * _reduction;
    int reductions = (n_triangles - n_triangles_final) / 2;

    std::cout<<"Nº of reductions="<<reductions<<std::endl;

    priority_q pq;
    generateLowerErrorQueue( _mesh, pq);

    HalfEdge *_he;
    bool encontrado = false;
    QLinkedList<HalfEdge>::iterator it_he;
    for(int i=0; i < reductions; i++){
        encontrado = false;
        for(it_he = _mesh->getHalfEdgesPtr()->begin(); it_he != _mesh->getHalfEdgesPtr()->end()
            && !encontrado; ++it_he){
            if(it_he->getId() == ((HalfEdge)pq.top()).getId()){
                _he = &*it_he;
                encontrado = true;
            }
        }
        // Simplified the lower error half edge

        if(_he->getFace()->getId() != _he->getOposite()->getFace()->getId()){
            if(!std::isnan(_he->getErrorRemove())){
                collapse(_he,_mesh);
            }else{
                std::cout<<"valor no valido"<<std::endl;
            }
        }

        // Remove from the list
        pq.pop();

        generateLowerErrorQueue( _mesh, pq);

    }




}


void Connectivity::collapse(HalfEdge *_h, Malla *_mesh){
    // Inicializo las variables necesarias
    HalfEdge  *hn = _h->getNextHalfedge();
    HalfEdge  *hp = _h->getPrevious();

    HalfEdge  *o  = _h->getOposite();

    HalfEdge  *on = o->getNextHalfedge();
    HalfEdge  *op = o->getPrevious();

    Face     *fh = _h->getFace();
    Face     *fo = o->getFace();

    Vertex  *vh = _h->getVertexIn();
    Vertex  *vo = _h->getVertexOut();

    // Eliminamos la cara de la semi-arista implicada
    _mesh->getIndicesPtr()->removeAll(*_h->getFace());
    _h->setFace(NULL);

    //Eliminamos la cara opuesta de la semi-arista implicada
    _mesh->getIndicesPtr()->removeAll(*o->getFace());
    o->setFace(NULL);

    // Re-asignar caras opuestas
    hn->getOposite()->setOposite(hp->getOposite());
    hp->getOposite()->setOposite(hn->getOposite());

    on->getOposite()->setOposite(op->getOposite());
    op->getOposite()->setOposite(on->getOposite());

    // Elimino las referencias de los vértices a las semi-aristas eliminadas
    hn->getVertexIn()->removeHalfEdgeIn(hn);
    hn->getVertexOut()->removeHalfEdgeOut(hn);

    hp->getVertexIn()->removeHalfEdgeIn(hp);
    hp->getVertexOut()->removeHalfEdgeOut(hp);

    _h->getVertexIn()->removeHalfEdgeIn(_h);
    _h->getVertexOut()->removeHalfEdgeOut(_h);

    on->getVertexIn()->removeHalfEdgeIn(on);
    on->getVertexOut()->removeHalfEdgeOut(on);

    op->getVertexIn()->removeHalfEdgeIn(op);
    op->getVertexOut()->removeHalfEdgeOut(op);

    o->getVertexIn()->removeHalfEdgeIn(o);
    o->getVertexOut()->removeHalfEdgeOut(o);



    //Elimino las semi-aristas de la caras eliminadas
    _mesh->getHalfEdgesPtr()->removeOne(*hn);
    _mesh->getHalfEdgesPtr()->removeOne(*hp);
    _mesh->getHalfEdgesPtr()->removeOne(*on);
    _mesh->getHalfEdgesPtr()->removeOne(*op);


    // Recorro todas las semi-aristas que inciden en el vértice vo(origen)
    // ahora inciden sobre vh(destino)
    QLinkedList<HalfEdge*>::iterator it_hivo;
    for(it_hivo = vo->getAllHalfEdgesInPtr()->begin();
        it_hivo != vo->getAllHalfEdgesInPtr()->end();
        ++it_hivo){

        (*it_hivo)->setVertexIn(vh);
        vh->addHalfEdgeIn((*it_hivo) );
    }

    // Recorro todas las semi-aristas que salen del vértice vo(origen)
    // ahora salen de vh(destino)
    QLinkedList<HalfEdge*>::iterator it_hovo;
    for(it_hovo = vo->getAllHalfEdgesOutPtr()->begin();
        it_hovo != vo->getAllHalfEdgesOutPtr()->end();
        ++it_hovo){

        (*it_hovo)->setVertexOut(vh);
        vh->addHalfEdgeOut((*it_hovo) );
    }

    // Remplazo el vértice colapsado de las caras para formar
    // las nuevas caras
    // TODO: mejorar, recorriendo solo las caras adyacentes al vértice collapsado
    QLinkedList<Face>::iterator it_face;
    for(it_face = _mesh->getIndicesPtr()->begin();
        it_face != _mesh->getIndicesPtr()->end();
        ++it_face){

        if(it_face->getVertices().contains(*vo)){
            it_face->remplaceVertex(*vo,*vh);
            it_face->generateSurfaceNormal();
        }
    }


    // Elimino las semi-aristas implicadas
    _mesh->getHalfEdgesPtr()->removeOne(*_h);
    _mesh->getHalfEdgesPtr()->removeOne(*o);


    // Elimino el vértice collapsado
    _mesh->getVerticesPtr()->removeAll(*vo);

}




