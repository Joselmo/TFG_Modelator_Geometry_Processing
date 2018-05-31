#ifndef SPHERE_H
#define SPHERE_H

#include <GL/gl.h>
class Sphere
{
public:
    Sphere();

    void setPosition(GLfloat _x, GLfloat _y, GLfloat _z);
    void setColor(GLfloat r,GLfloat g, GLfloat b);
    void draw(GLenum face,int mode_view,GLfloat n);

private:
   // Figura3D figura3d;
    GLfloat x,y,z;
};

#endif // SPHERE_H
