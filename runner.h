#ifndef RUNNER_H
#define RUNNER_H


typedef struct materialStruct{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;
typedef struct lightStruct{
  GLfloat position[4];
  GLfloat diffuse[4];
  GLfloat ambient[4];
  GLfloat specular[4];
} lightStruct;
typedef struct vec4{
  GLfloat value[4];
} vec4;

void figurine(GLfloat theter);
GLfloat absol(GLfloat f);
void head();
void torso();
void arm(int s);
void uparm();
void foarm();
void leg(int s);
void upleg();
void foleg();
void foot();
void line(GLfloat a, GLfloat b);
void line2(GLfloat a, GLfloat b);
void line3(GLfloat a, GLfloat b, GLfloat c);

void display(void);
GLfloat mod(GLfloat v, GLfloat c);
void wobble2();
void materials(materialStruct *materials);
void sphere();

void config_lights();
void lightSrc();
void drawLights();
void swivel1();
void swivel1();
void wobble();
vec4 avg(vec4 a, vec4 b);
vec4 wavg(vec4 a, vec4 b, float na, float nb);

void mykey(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void init();
// void config_lights(GLfloat* lit_pos);
vec4 avg(vec4 a, vec4 b);
vec4 wavg(vec4 a, vec4 b, float na, float nb);
float clamp(float a, float l, float h);
float clampB(float a);
float abso(float a);
void cube();
void grid(int size, vec4 color, vec4 bg, float thickness, float blur);
void grid2(int size, vec4 color, vec4 bg, float thickness, float blur);
void mymotion();
int main(int argc, char **argv);

#endif