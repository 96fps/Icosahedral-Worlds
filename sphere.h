#ifndef SPHERE_H
#define SPHERE_H



typedef struct materialStruct{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


void display(void);
void materials(materialStruct *materials);
void Triangle(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color);
void superdivIsa(int m);
void superDivTri(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m) ;
void isoTri();
void isoVerts();
void coordinate(void) ;
void lightSrc() ;
void quad(int a, int b, int c , int d);
void colorcube(void);
void swivel2();
void swivel1();
void wobble();
void mykey(unsigned char key, int x, int y) ;
void resize(GLsizei w, GLsizei h);
void init() ;
void config_lights();
void cube();
void sphere();
void ring(double dist,double size);
void mymotion() ;
int main(int argc, char **argv);

#endif