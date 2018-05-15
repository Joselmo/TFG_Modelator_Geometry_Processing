#include "plyreader.h"

PLYReader::PLYReader()
{

}

void PLYReader::readPLY(Malla &malla){

    MyMesh  mesh;
    IO::Options ropt;
    // -------------------- read mesh
    if ( ! IO::read_mesh(mesh,"../PLY/beethoven.ply"))
    {
        std::cerr << "Error loading mesh from file " << std::endl;
        //return 1;
    }
    // -------------------- show options

    // -------------------- mesh stats
    std::cout << "# Vertices: " << mesh.n_vertices() << std::endl;
    std::cout << "# Edges   : " << mesh.n_faces() << std::endl;
    std::cout << "# Faces   : " << mesh.n_faces() << std::endl;

    // iterate over all vertices
    glm::vec3 point;
    vector<glm::vec3> local_vertices;
    local_vertices.reserve(mesh.n_vertices());
    for (MyMesh::VertexIter v_it=mesh.vertices_begin(); v_it!=mesh.vertices_end(); ++v_it){
        //std::cout << "Vertex #" << *v_it << ": " << mesh.point( *v_it )[0]<<std::endl;
        point[0] = mesh.point( *v_it )[0];
        point[1] = mesh.point( *v_it )[1];
        point[2] = mesh.point( *v_it )[2];
        local_vertices.push_back(point);
    }

    malla.setVertexes(local_vertices);

    // iterate over all faces
    glm::ivec3 vertex;
    vector<glm::ivec3> local_faces;
    local_faces.reserve(mesh.n_faces());
    MyMesh::ConstFaceIter f_it,f_end(mesh.faces_end());
    MyMesh::ConstFaceVertexIter fv_it;
    int cont=0;
    for (f_it = mesh.faces_sbegin(); f_it!=f_end; ++f_it){
        //std::cout<<"Faces:";
        cont = 0;
        for (fv_it = mesh.fv_iter(*f_it);fv_it.is_valid();++fv_it){
            //std::cout<<fv_it->idx()<<"\t";
            vertex[cont] = fv_it->idx();
            cont++;
        }
        //std::cout<< "$$"<<std::endl;
        local_faces.push_back(vertex);
    }
    malla.setTriangles(local_faces);


    // -------------------- Pasar de Mesh a mi malla

}
