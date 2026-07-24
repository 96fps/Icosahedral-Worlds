#ifndef MAIN_H
#define MAIN_H
#define PI 3.141592

void display();
void configcamera();
void wobble();
void swivel3();
void swivel1();
void surfaceslide();
void lowOrbit();
void squishy();
void template();
void std_globe();
void tube();
void rollingsphere(int copies);
void static_contact(int copies);
void Triangle(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color);
void TriangleTricolor(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* colorset);
void subDivTri2(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m, double inflate);
void superDivTri2(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m, double inflate);
void superDivTri3(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m, double inflate);
void superdivIsa_ext(int m, double inflate);
void subdivIsa_ext(int m, double inflate);
void superdivIsaNet_ext(int m, double inflate);
void superdivIsaTube(int m, double inflate);
void solidIsa2();
void solidIsaNet2();
void generatePrimitives();
void genIcosahedron();
void isoVerts();
void isoTri();
void genIcosahedronNet();
void isoNetVerts();
void isoNetTri();
void genIcosahedronTube();
void isoTubeVerts();
void isoTubeTri();
void cube();
void mymotion();
void resize(GLsizei w, GLsizei h);
int main(int argc, char** argv);
GLfloat xrot(GLfloat x, GLfloat y, GLfloat theta);
GLfloat yrot(GLfloat x, GLfloat y, GLfloat theta);

#endif