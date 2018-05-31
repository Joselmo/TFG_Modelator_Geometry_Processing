#include "sphere.h"

Sphere::Sphere(){

    PLYReader pread;
    Malla malla1;
    pread.readPLY(malla1,"esfera.ply");
    //figura3d.setMesh(malla1);
    //figura3d.setColorAll(1,0.0,0.0);
}

void Sphere::setPosition(GLfloat _x, GLfloat _y, GLfloat _z){
    x=_x;
    y=_y;
    z=_z;
}

void Sphere::setColor(GLfloat r, GLfloat g, GLfloat b){
    //figura3d.setColorAll(r,g,b);
}

void Sphere::draw(GLenum face, int mode_view, GLfloat n){
    glPushMatrix();
         glTranslatef(x,y,z);
         //figura3d.draw(face,mode_view,n);
    glPopMatrix();
}
