
#include "malla.h"

QLinkedList<HalfEdge> *Malla::getHalfEdgesPtr() {
    return &half_edges;
}

QLinkedList<HalfEdge> Malla::getHalfEdges(){
    return half_edges;
}

Malla::Malla(){}

/** Constructor parametrizado
* Crea una malla dados un vector de vertices y uno de triangulos
*/
Malla::Malla(QLinkedList<Vertex> _vertex, QLinkedList<Face> _index){
    vertices = _vertex;
    indices  = _index;
    generateGeometry();
}


/**
* Sobrecarga del operador asignación
* Copia los vectores de triangulos y vertices
*/
Malla& Malla::operator=(const Malla& _malla){
    //std::cout << "copiando malla" << std::endl;
    if(this != &_malla){
        vertices.clear();
        indices.clear();
        vertices = _malla.vertices;
        indices  = _malla.indices;
        generateGeometry();
    }
    return *this;
}


QVector<Vertex> Malla::getSgVertexes(){
    return sg_vertices;
}

void Malla::setSgVertexes(QVector<Vertex> &_value){
    sg_vertices = _value;
}

QLinkedList<Vertex> Malla::getVertices(){
    return vertices;
}

QLinkedList<Vertex> *Malla::getVerticesPtr() {
    return &vertices;
}

void Malla::setVertices( QLinkedList<Vertex> &_value){
    vertices = _value;
}

QLinkedList<Face> Malla::getIndices(){
    return indices;
}

QLinkedList<Face> *Malla::getIndicesPtr(){
    return &indices;
}

void Malla::setIndices(QLinkedList<Face> &_value){
    indices = _value;
}

Vertex* Malla::getPointSgVertexes(){
    return &sg_vertices.first();
}

int Malla::getSizeOfGeometry(){
    return (indices.size() * 3 * sizeof(Vertex));
}

void Malla::initGeometry(std::string _filename){
    MyMesh  mesh;
    IO::Options ropt;
    // -------------------- read mesh
    if ( ! IO::read_mesh(mesh,"../PLY/"+_filename))
    {
        std::cerr << "Error loading mesh from file " << std::endl;
        //return 1;
    }
    // -------------------- show options

    // -------------------- mesh stats
    std::cout << "# Vertices: " << mesh.n_vertices() << std::endl;
    std::cout << "# Edges   : " << mesh.n_faces() << std::endl;
    std::cout << "# Faces   : " << mesh.n_faces() << std::endl;
    std::cout << "# HalfEdges   : " << mesh.n_halfedges() << std::endl;

    // iterate over all vertices
    Vertex point;
    point.setColor(QVector3D(1.0f,1.0f,1.0f));
    for (MyMesh::VertexIter v_it=mesh.vertices_begin(); v_it!=mesh.vertices_end(); ++v_it){
        point.setPosition(QVector3D(mesh.point( *v_it )[0],
                                    mesh.point( *v_it )[1],
                                    mesh.point( *v_it )[2]));
        point.setId(  vertices.size() );
        vertices.push_back(point);
    }

    // iterate over all faces
    Face face;
    MyMesh::ConstFaceIter f_it,f_end(mesh.faces_end());
    MyMesh::ConstFaceVertexIter fv_it;
    QLinkedList<Vertex>::iterator it_vertices = vertices.begin();
    // Itero sobre el handle de caras
    for (f_it = mesh.faces_sbegin(); f_it!=f_end; ++f_it){
        //dentro de cada cara itero sobre sus referencias
        face.clear();

        for (fv_it = mesh.fv_iter(*f_it);fv_it.is_valid();++fv_it){
            //std::cout<<fv_it->idx()<<"\t";
            it_vertices = vertices.begin() + fv_it->idx();
            face.addVertex(*it_vertices);

        }

        face.setId((*f_it).idx());

        face.generateSurfaceNormal();

        indices.push_back(face);
    }
    std::cout<<std::endl;

    HalfEdge he;

    for (MyMesh::HalfedgeIter h_it=mesh.halfedges_begin(); h_it!=mesh.halfedges_end(); ++h_it){


        he.setId((*h_it).idx());
        it_vertices = vertices.begin() + mesh.to_vertex_handle(*h_it).idx();
        he.setVertexIn(&*it_vertices);
        it_vertices = vertices.begin() + mesh.from_vertex_handle(*h_it).idx();
        he.setVertexOut(&*it_vertices);

        QLinkedList<Face>::iterator it_indices = indices.begin();
        if(mesh.face_handle(*h_it).idx() != -1){
            it_indices = indices.begin() + mesh.face_handle(*h_it).idx();
            he.setFace(it_indices.operator ->());
            half_edges.push_back(he);

            //Conexiones desde el vértice
            it_vertices = vertices.begin() + mesh.to_vertex_handle(*h_it).idx();
            it_vertices->addHalfEdgeIn(&half_edges.back());

            it_vertices = vertices.begin() + mesh.from_vertex_handle(*h_it).idx();
            it_vertices->addHalfEdgeOut(&half_edges.back());

        }else{
            std::cout<<"Cara vacía:"<<mesh.face_handle(*h_it).idx()<<std::endl;
        }
    }

    //Añado las referencias a siguiente, anterior y opuesta
    QLinkedList<HalfEdge>::iterator it_halfedge,it_otherHE;
    for (MyMesh::HalfedgeIter h_it=mesh.halfedges_begin(); h_it!=mesh.halfedges_end(); ++h_it){

        it_halfedge = half_edges.begin() + (*h_it).idx();
        it_otherHE = half_edges.begin() + mesh.next_halfedge_handle(*h_it).idx();
        it_halfedge->setNextHalfedge(&*it_otherHE);

        it_otherHE = half_edges.begin() + mesh.opposite_halfedge_handle(*h_it).idx();
        it_halfedge->setOposite(&*it_otherHE);

        it_otherHE = half_edges.begin() + mesh.prev_halfedge_handle(*h_it).idx();
        it_halfedge->setPrevious(&*it_otherHE);


   }

    std::cout<<std::endl;
    Connectivity con;

   std::cout<< "número de caras totales antes="<<indices.size()<<std::endl;
   con.decimation(this,0.25f);
   std::cout<< "número de caras totales después="<<indices.size()<<std::endl;
   generateGeometry();


}

void Malla::generateSurfaceNormals(){

    for(Face face:indices){
        face.generateSurfaceNormal();
    }
}

void Malla::generateGeometry(){

    if(indices.empty() || vertices.empty()){
        printf("ERROR: no se puede genera la geometria sin los vertices o indices");
    }else{
        sg_vertices.clear();
        for(Face j: indices){
            for(Vertex i:j.getVertices()){
                sg_vertices.push_back(i);
            }

        }
    }
}
