
#include "cubo.h"
/**
*   Constructores
*/
Cubo::Cubo(){

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

Cubo::~Cubo()
{

}

QVector<Vertex> Cubo::getSg_vertexes() const
{
    return sg_vertexes;
}

void Cubo::setSg_vertexes(const QVector<Vertex> &value)
{
    sg_vertexes = value;
}

QVector<Vertex> Cubo::getVertices() const
{
    return vertices;
}

void Cubo::setVertices(const QVector<Vertex> &value)
{
    vertices = value;
}

QVector<int> Cubo::getIndices() const
{
    return indices;
}

void Cubo::setIndices(const QVector<int> &value)
{
    indices = value;
}

Vertex* Cubo::getPointSg_vertexes()
{
    return sg_vertexes1;
}

int Cubo::getSizeOfGeometry()
{
    return (indices.size() * sizeof(Vertex));
}



void Cubo::initCubeGeometry()
{
    // Front Verticies
    Vertex VERTEX_FTR( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    Vertex VERTEX_FTL( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    Vertex VERTEX_FBL( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    Vertex VERTEX_FBR( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );

    // Back Verticies
    Vertex VERTEX_BTR( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    Vertex VERTEX_BTL( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    Vertex VERTEX_BBL( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    Vertex VERTEX_BBR( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) );
    vertices.push_back(VERTEX_FTR); // 0
    vertices.push_back(VERTEX_FTL); // 1
    vertices.push_back(VERTEX_FBL); // 2
    vertices.push_back(VERTEX_FBR); // 3
    vertices.push_back(VERTEX_BTR); // 4
    vertices.push_back(VERTEX_BTL); // 5
    vertices.push_back(VERTEX_BBL); // 6
    vertices.push_back(VERTEX_BBR); // 7

    // Face 1 (Front
    indices.push_back(0);indices.push_back(1);indices.push_back(2);
    indices.push_back(2);indices.push_back(3);indices.push_back(0);
    // Face 2 (Back)
    indices.push_back(7);indices.push_back(5);indices.push_back(4);
    indices.push_back(5);indices.push_back(7);indices.push_back(6);
    // Face 3 (Top)
    indices.push_back(0);indices.push_back(4);indices.push_back(5);
    indices.push_back(5);indices.push_back(1);indices.push_back(0);
    // Face 4 (Bottom)
    indices.push_back(3);indices.push_back(2);indices.push_back(6);
    indices.push_back(6);indices.push_back(7);indices.push_back(3);
    // Face 5 (Left)
    indices.push_back(2);indices.push_back(1);indices.push_back(5);
    indices.push_back(2);indices.push_back(5);indices.push_back(6);
    // Face 6 (Right)
    indices.push_back(0);indices.push_back(3);indices.push_back(7);
    indices.push_back(7);indices.push_back(4);indices.push_back(0);

    generateGeometry();
}

void Cubo::generateGeometry()
{
    sg_vertexes1 = new Vertex[indices.size()];
    for(int i=0; i < indices.size();i++){
        sg_vertexes1[i] = vertices.at(indices.at(i));

    }
    for(int& i:indices){
        sg_vertexes.push_back(vertices.at(i));
    }
}
