
#include "malla.h"

QVector<HalfEdge> *Malla::getHalf_edges() {
    return &half_edges;
}

Malla::Malla(){}

/** Constructor parametrizado
* Crea una malla dados un vector de vertices y uno de triangulos
*/
Malla::Malla(QVector<Vertex> _vertex, QVector<QVector<int>> _index){
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


QVector<Vertex> Malla::getSg_vertexes() const
{
    return sg_vertices;
}

void Malla::setSg_vertexes(const QVector<Vertex> &_value)
{
    sg_vertices = _value;
}

QVector<Vertex> Malla::getVertices() const
{
    return vertices;
}

void Malla::setVertices(const QVector<Vertex> &_value)
{
    vertices = _value;
}

QVector<QVector<int>> Malla::getIndices() const
{
    return indices;
}

void Malla::setIndices(const QVector<QVector<int>> &_value)
{
    indices = _value;
}

Vertex* Malla::getPointSg_vertexes()
{
    return &(sg_vertices[0]);
}

int Malla::getSizeOfGeometry()
{
    return (indices.size() * sizeof(Vertex));
}



void Malla::initGeometry(std::string _filename)
{
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
    vertices.reserve(mesh.n_vertices());
    for (MyMesh::VertexIter v_it=mesh.vertices_begin(); v_it!=mesh.vertices_end(); ++v_it){
        //std::cout << "Vertex #" << *v_it << ": " << mesh.point( *v_it )[0]<<std::endl;
        point.setPosition(QVector3D(mesh.point( *v_it )[0],
                          mesh.point( *v_it )[1],
                mesh.point( *v_it )[2]));
        point.setId(  vertices.length() );
        vertices.push_back(point);
    }

    // iterate over all faces
    indices.reserve(mesh.n_faces());
    QVector<int> tupla;
    tupla.resize(3);
    MyMesh::ConstFaceIter f_it,f_end(mesh.faces_end());
    MyMesh::ConstFaceVertexIter fv_it;

    // Itero sobre el handle de caras
    for (f_it = mesh.faces_sbegin(); f_it!=f_end; ++f_it){
        //std::cout<<"Faces:";
        //dentro de cada cara itero sobre sus referencias
        tupla.clear();
        for (fv_it = mesh.fv_iter(*f_it);fv_it.is_valid();++fv_it){
            //std::cout<<fv_it->idx()<<"\t";
            tupla.push_back(fv_it->idx());

        }
        indices.push_back(tupla);
    }


    half_edges.reserve(mesh.n_halfedges());
    HalfEdge he;
    for (MyMesh::HalfedgeIter h_it=mesh.halfedges_begin(); h_it!=mesh.halfedges_end(); ++h_it){

        std::cout<< (*h_it)<<" ";
//        std::cout<<"-to_vertex_hadle=" << mesh.to_vertex_handle(*h_it).idx() << "\t";
//        std::cout<<"from_vertex_handle=" << mesh.from_vertex_handle(*h_it).idx() << "\t";
        std::cout<<"face_handle=" << mesh.face_handle(*h_it).idx() << "\t";
        std::cout<<indices[mesh.face_handle(*h_it).idx()].at(0)<<",";
        std::cout<<indices[mesh.face_handle(*h_it).idx()].at(1)<<",";
        std::cout<<indices[mesh.face_handle(*h_it).idx()].at(2)<<std::endl;
//        std::cout<<"next_halfedge_handle=" << mesh.next_halfedge_handle(*h_it).idx() << "\t";
//        std::cout<<"prev_halfedge_handle=" << mesh.prev_halfedge_handle(*h_it).idx() << "\t";
//        std::cout<<"opposite_halfedge_handle=" << mesh.opposite_halfedge_handle(*h_it).idx() <<std::endl;

        he.setId((*h_it).idx());
        he.setVertex_in(&vertices[mesh.to_vertex_handle(*h_it).idx()]);
        he.setVertex_out(&vertices[mesh.from_vertex_handle(*h_it).idx()]);
        he.setFace(mesh.face_handle(*h_it).idx());
        he.setNext_halfedge(mesh.next_halfedge_handle(*h_it).idx());
        he.setPrevious(mesh.prev_halfedge_handle(*h_it).idx());
        he.setOposite(mesh.opposite_halfedge_handle(*h_it).idx());
        half_edges.push_back(he);

        //Conexiones desde el vértice
        vertices[mesh.to_vertex_handle(*h_it).idx()].addHalfEdgeIn((*h_it).idx());
        vertices[mesh.from_vertex_handle(*h_it).idx()].addHalfEdgeOut((*h_it).idx());
    }

    Connectivity con;
    // Collapse V2 en V1


    for(Vertex i:vertices){
        printf("V:%f \n",i.position().x());
    }
    con.collapse(half_edges[7],&half_edges, *this);
    for(Vertex i:vertices){
        printf("2V:%f \n",i.position().x());
    }

    generateGeometry();
}

void Malla::generateGeometry()
{

    if(indices.isEmpty() || vertices.isEmpty()){
        printf("ERROR: no se puede genera la geometria sin los vertices o indices");
    }else{
        sg_vertices.clear();
        for(QVector<int> j: indices)
            for(int& i:j){
                sg_vertices.push_back(vertices.at(i));
            }
    }
}
