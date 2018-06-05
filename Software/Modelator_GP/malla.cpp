
#include "malla.h"

Malla::Malla(){}

/** Constructor parametrizado
* Crea una malla dados un vector de vertices y uno de triangulos
*/
Malla::Malla(QVector<Vertex> vertex_n, QVector<int> indices_n){
    vertices = vertex_n;
    indices  = indices_n;
    generateGeometry();
}


/**
* Sobrecarga del operador asignación
* Copia los vectores de triangulos y vertices
*/
Malla& Malla::operator=(const Malla& malla_nueva){
    //std::cout << "copiando malla" << std::endl;
    if(this != &malla_nueva){
        vertices.clear();
        indices.clear();
        vertices = malla_nueva.vertices;
        indices  = malla_nueva.indices;
        generateGeometry();
    }
    return *this;
}


QVector<Vertex> Malla::getSg_vertexes() const
{
    return sg_vertices;
}

void Malla::setSg_vertexes(const QVector<Vertex> &value)
{
    sg_vertices = value;
}

QVector<Vertex> Malla::getVertices() const
{
    return vertices;
}

void Malla::setVertices(const QVector<Vertex> &value)
{
    vertices = value;
}

QVector<int> Malla::getIndices() const
{
    return indices;
}

void Malla::setIndices(const QVector<int> &value)
{
    indices = value;
}

Vertex* Malla::getPointSg_vertexes()
{
    return &(sg_vertices[0]);
}

int Malla::getSizeOfGeometry()
{
    return (indices.size() * sizeof(Vertex));
}



void Malla::initGeometry(std::string filename)
{
    MyMesh  mesh;
    IO::Options ropt;
    // -------------------- read mesh
    if ( ! IO::read_mesh(mesh,"../PLY/"+filename))
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
        vertices.push_back(point);
    }

    // iterate over all faces
    indices.reserve(mesh.n_faces());
    MyMesh::ConstFaceIter f_it,f_end(mesh.faces_end());
    MyMesh::ConstFaceVertexIter fv_it;

    // Itero sobre el handle de caras
    for (f_it = mesh.faces_sbegin(); f_it!=f_end; ++f_it){
        //std::cout<<"Faces:";
        //dentro de cada cara itero sobre sus referencias
        for (fv_it = mesh.fv_iter(*f_it);fv_it.is_valid();++fv_it){
            //std::cout<<fv_it->idx()<<"\t";
            indices.push_back(fv_it->idx());

        }

    }


    half_edges.reserve(mesh.n_halfedges());
    HalfEdge he;
    for (MyMesh::HalfedgeIter h_it=mesh.halfedges_begin(); h_it!=mesh.halfedges_end(); ++h_it){
/*
        std::cout<< (*h_it);
        std::cout<<"-to_vertex_hadle=" << mesh.to_vertex_handle(*h_it).idx() << "\t";
        std::cout<<"from_vertex_handle=" << mesh.from_vertex_handle(*h_it).idx() << "\t";
        std::cout<<"face_handle=" << mesh.face_handle(*h_it).idx() << "\t";
        std::cout<<"next_halfedge_handle=" << mesh.next_halfedge_handle(*h_it).idx() << "\t";
        std::cout<<"prev_halfedge_handle=" << mesh.prev_halfedge_handle(*h_it).idx() << "\t";
        std::cout<<"opposite_halfedge_handle=" << mesh.opposite_halfedge_handle(*h_it).idx() <<std::endl;
*/
        he.setVertex_in(&vertices[mesh.to_vertex_handle(*h_it).idx()]);
        he.setVertex_out(&vertices[mesh.from_vertex_handle(*h_it).idx()]);
        he.setFace(&indices[mesh.to_vertex_handle(*h_it).idx()]);
        he.setNext_halfedge(mesh.next_halfedge_handle(*h_it).idx());
        he.setPrevious(mesh.prev_halfedge_handle(*h_it).idx());
        he.setOposite(mesh.opposite_halfedge_handle(*h_it).idx());
        half_edges.push_back(he);
    }


    generateGeometry();
}

void Malla::generateGeometry()
{
    if(indices.isEmpty() || vertices.isEmpty()){
        printf("ERROR: no se puede genera la geometria sin los vertices o indices");
    }else{
        sg_vertices.clear();
        for(int& i:indices){
            sg_vertices.push_back(vertices.at(i));
        }
    }
}
