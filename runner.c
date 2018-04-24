#include <GL/glut.h>
#include <stdlib.h>


  GLfloat h=1.9;
  GLfloat anim=0.0;
  GLfloat sh=1.6;
  GLfloat sw=0.2;
  GLfloat ual=.5;
  GLfloat fal=.5;
  GLfloat hh=.7;
  GLfloat hw=.2;
  GLfloat ull=.5;
  GLfloat fll=.5;
  GLfloat wid = 0.1;


void figurine(GLfloat theter);
void head();
void torso();
void arm(int s);
void foarm();
void uparm();
GLfloat absol(GLfloat f);
void line(GLfloat a, GLfloat b);
void line2(GLfloat a, GLfloat b);
void line3(GLfloat a, GLfloat b, GLfloat c);

void figurine(GLfloat theter){
  anim=theter*2;
  //body
  glLineWidth(2.0);
  glColor3f(1,1,1);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glPushMatrix();
  glTranslatef(.5,0,.5);

   hh=.9+sin(anim*.324)*.5;
   hh=.9;

  glTranslatef(0,absol(sin(anim))*0.2,0);
  //torso
  head();
  torso();
  arm(0);
  arm(1);

  leg(0);
  leg(1);


  glPopMatrix();
  // glDisable(GL_LIGHTING);
}
GLfloat absol(GLfloat f){
  if (f<0)
    f*=-1;
  return f;
}
void head(){
  glPushMatrix();
  glTranslatef(0,h,0);
  glScalef(0.15,0.2,0.15);
  sphere();
  glPopMatrix();
}
void torso(){
  // glBegin(GL_LINE_LOOP);
  //   glVertex3f(0,hh,0);
  //   glVertex3f(0,sh,sw);
  //   glVertex3f(0,sh,-sw);
  // glEnd();


  glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);
    glVertex3f(0,hh,0);
    glVertex3f(0,sh,sw);
    glVertex3f(0,sh,-sw);
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(.9,0,.3);
    glVertex3f(0,sh,sw);
    glVertex3f(0,hh,0);
    glVertex3f(.1,sh,0);
  glEnd();
  glBegin(GL_POLYGON);
    glNormal3f(.9,0,-.3);
    glVertex3f(.1,sh,0);
    glVertex3f(0,hh,0);
    glVertex3f(0,sh,-sw);
  glEnd();
}
void arm(int s){
  s=(s%2)*2-1;

  glPushMatrix();
  glTranslatef(0,sh,sw*s);
  glRotatef(sin(anim)*35*s,0,0,1);
  uparm();
  glTranslatef(0,-ual,0);
  glRotatef(sin(anim)*55*s+55,0,0,1);
  foarm();
  glPopMatrix();
}
void uparm(){
  line2(0,-ual);
}
void foarm(){
  // glRotatef(180,0,1,0);
  line3(0,-fal, 0.1);
}
void leg(int s){
  s=(s%2)*2-1;

  glPushMatrix();
  glTranslatef(0,hh,hw*s*.5);
  glRotatef(sin(anim)*35*s,0,0,-1);
  upleg();
  glTranslatef(0,-ull,0);
  glRotatef(sin(anim-3.14*.5)*45*s+55,0,0,-1);
  foleg();
  glTranslatef(0,-fll,0);
  glRotatef(-55+sin(anim-3.14*1.5)*35*s,0,0,-1);
  foot();
  glPopMatrix();
}
void upleg(){
  line2(0,-ull);
}
void foleg(){
  line2(0,-fll);
}
void foot(){
  line2(0,-.2);
}
void line(GLfloat a, GLfloat b){
  glBegin(GL_LINES);
    glVertex3f(0,a,0);
    glVertex3f(0,b,0);
  glEnd();
}
void line2(GLfloat a, GLfloat b){
  line3(a, b, wid);
}
void line3(GLfloat a, GLfloat b, GLfloat c){
  glNormal3f(.6,1,.6);
  glBegin(GL_POLYGON);
    glVertex3f(0,a,0);
    glVertex3f(-c,a*.75+b*.25,c*.5);
    glVertex3f(0,b,0);
  glEnd();
  glNormal3f(.6,0,-.6);
  glBegin(GL_POLYGON);
    glVertex3f(-c,a*.75+b*.25,-c*.5);
    glVertex3f(0,a,0);
    glVertex3f(0,b,0);
  glEnd();
  glNormal3f(0,-1,0);
  glBegin(GL_POLYGON);
    glVertex3f(-c,a*.75+b*.25,c*.5);
    glVertex3f(-c,a*.75+b*.25,-c*.5);
    glVertex3f(0,b,0);
  glEnd();
  glNormal3f(0,1,0);
  glBegin(GL_POLYGON);
    glVertex3f(0,a,0);
    glVertex3f(-c,a*.75+b*.25,-c*.5);
    glVertex3f(-c,a*.75+b*.25,c*.5);
  glEnd();
}

static GLfloat theta[] = {15.0, -35.0, 0.0} ;

GLfloat theter = 0.0;
double Rad = 6.28/360;
double pi_value = 3.141592;

GLfloat isovert[12][3] = {0};
int isoTriangle[20][3] = {0};

typedef struct materialStruct{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

materialStruct basicMaterial = {
  { 0, 0, 0, 1}, //ambient
  { 1,.9,.7, 1}, //diffuse
  { 0, 0, 0, 1}, //sepcular
  128.0
};
materialStruct woodMaterial = {
  { 0, 0, 0, 1}, //ambient
  { 1,.5,.2, 1}, //diffuse
  { 0, 0, 0, 1}, //sepcular
  128.0
};
materialStruct steelMaterial = {
  { 0, 0, 0, 1}, //ambient
  { 1, 1, 1, 1}, //diffuse
  {.8,.8,.8, 1}, //sepcular
  64.0
};
materialStruct darksteelMaterial = {
  {.06,.06,.06, 1}, //ambient
  {.6,.6,.6, 1}, //diffuse
  {.8,.8,.8, 1}, //sepcular
  64.0
};
materialStruct glassMaterial = {
  { 0, 0, 0, 1}, //ambient
  {2, 2,2,.5}, //diffuse
  { 1, 1, 1, 1}, //sepcular
  128.0
};
materialStruct wallMaterial = {
  {.1,.1,.1, 1}, //ambient
  { 1, 1, 1, 1}, //diffuse
  { 1, 1, 1, 1}, //sepcular
  128.0
};

typedef struct lightStruct{
  GLfloat position[4];
  GLfloat diffuse[4];
  GLfloat ambient[4];
  GLfloat specular[4];
} lightStruct;
typedef struct vec4{
  GLfloat value[4];
} vec4;
  vec4 bgColor ={{.8,.8,.8,1.0}};
    // vec4 bgColor ={{1.0,1.0,1.0,1.0}};
  vec4 red  ={{1,0,0,1.0}};
  vec4 green={{0,1,0,1.0}};
  vec4 blue ={{0,0,1,1.0}};

  vec4 white ={{1,1,1,1.0}};
  vec4 grey ={{.5,.5,.5,1.0}};
  vec4 black ={{0,0,0,1.0}};
  vec4 transparent ={{0,0,0,0}};

  vec4 cyan    = {{0,1,1,1.0}};
  vec4 magenta = {{1,0,1,1.0}};
  vec4 yellow  = {{1,1,0,1.0}};
  

lightStruct light0 = {
  { 4, 4, 4, 1}, //position
  {.5,.1,.1, 1}, //diffuse
  { 0, 0, 0, 0}, //ambient
  { 1, 1, 1, 1}  //spec
};
lightStruct light1 = {
  {10, 0, 0, 1}, //position
  {.1,.5,.1, 1}, //diffuse
  { 0, 0, 0, 1}, //ambient
  { 0, 0, 0, 1}  //spec
};
lightStruct light2 = {
  { 0,10, 0, 1}, //position
  {.1,.1,.5, 1}, //diffuse
  { 0, 0, 0, 1}, //ambient
  { 0, 0, 0, 1}  //spec
};
lightStruct light3 = {
  { 0, 0,10, 1}, //position
  {.2,.2,.2, 1}, //diffuse
  {.0,.0,.0, 1}, //ambient
  { 0, 0, 0, 1}  //spec
};

void materials(materialStruct *materials);

void swivel1();
void wobble2();

void config_lights();
void lightSrc();
void drawLights();
vec4 avg(vec4 a, vec4 b);
vec4 wavg(vec4 a, vec4 b, float na, float nb);

void init();

void cube();
void grid(int size, vec4 color, vec4 bg, float thickness, float blur);
void grid2(int size, vec4 color, vec4 bg, float thickness, float blur);

GLfloat mod(GLfloat v, GLfloat c);

double sin(double);
double cos(double);

void display(void){
  /* display callback, clear frame buffer and z buffer,
     rotate cube and draw, swap buffers */
  bgColor = wavg(white, cyan,0.05,0.02);
  bgColor = wavg(white, cyan,0.03,0.02);
  // bgColor = green;
  // bgColor = black;
 // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bgColor.value[0],bgColor.value[1],bgColor.value[2],bgColor.value[3]);

  // float n = sin(theter*pi_value*0.1)*.5+.5;
  // n *= 0.25;
  // bgColor = wavg(white, black,n,1.0-n);
  
  glLoadIdentity();

  // config_lights();

  glTranslatef(0,0,theta[2]-5);
  glRotatef(theta[0], 1.0, 0.0, 0.0);
  glRotatef(theta[1], 0.0, 1.0, 0.0);

  glTranslatef(0,-.8,0);
  // wobble2();
  // swivel1();

  vec4 t = wavg(yellow,grey,.3,.5);
  // t = wavg(yellow,grey,.15,.25);
  t = wavg(green,grey,.02,.03);
  // t = wavg(white, black,.02,0);
  // t = grey;
  // t = wavg(white,black,.98,.0);
  // t = red;
  // t = cyan;
  // t = grey;
  // cube();
  glPushMatrix();
  glTranslatef(-mod(theter*pi_value,1.0),0,0);
  GLfloat shift = mod(theter*pi_value,1.0);
  // grid(100, t, bgColor, 3.0, 6.0);
  grid2(40, t, bgColor, 3.0, 8.0);
  t = wavg(yellow,grey,.15,.25);
  vec4 t2 = wavg(yellow,grey,.15,.25);

  glPopMatrix();
  glPushMatrix();
  glTranslatef(-mod(theter*pi_value,4.0),0,0);

  shift = mod(theter*pi_value,4.0)*.25;
  for(int i = -10; i<10; i++){
  GLfloat d = i +shift;
  GLfloat br = 1.0/(d*d+1);
  GLfloat bl = (1-1.0/(d*d+1))*3;
  glPushMatrix();
  glTranslatef(-4*i,0,0);

  if(i<4 && i>-4){
  glPushMatrix();
  glScalef(.1,.1,.1);

    t2 = wavg(yellow,transparent,br*.05,0);
  grid2(19, t2, bgColor, 3.0, 3.0);
  glPopMatrix();
  }

    t2 = wavg(t,transparent,br,0);
  grid2(2, t2, bgColor, 3.0, 3.0+bl);
  
  glPopMatrix();
  }

  glPopMatrix();
  // room();
  figurine(theter*pi_value);
  lightSrc();
  drawLights();

  glFlush();
  glutSwapBuffers();
}GLfloat mod(GLfloat v, GLfloat c){
  if(v>c){
    int s=v/c;
    v-=s*c;
  }
  return v;
}
void wobble2(){
  glRotatef(5*sin(theter *Rad*180),1,0,0);
  glRotatef(5*cos(theter *Rad*180),0,1,0);
  // glRotatef(15*cos(0.5+theter *Rad*180),0,0,1);
}

void materials(materialStruct *materials){
  glMaterialfv(GL_FRONT, GL_DIFFUSE, 
      materials -> diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, 
      materials -> specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, 
      materials -> ambient);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 
      materials -> shininess);
}
void sphere(){
  GLUquadricObj *mysphere;
  mysphere = gluNewQuadric();

  glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricDrawStyle(mysphere, GLU_FILL);
    // glColor3f (r,g,b);
    gluSphere(mysphere,1.0,12,9);
  glPopMatrix();
}
void drawlight(lightStruct light){
   glEnable(GL_BLEND);
   // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(light.diffuse);
    // glRasterPos3fv(light.position);
    // glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    glTranslatef(light.position[0],light.position[1],light.position[2]);
    glScalef(.1,.1,.1);
    // glScalef(.5,.5,.5);
    // glScalef(-1,-1,-1);
    materials(&darksteelMaterial);
     // glMaterialfv(GL_FRONT, GL_DIFFUSE, 
     // light.diffuse);
    vec4 lit= white;
    lit.value[0] = light.diffuse[0];
    lit.value[1] = light.diffuse[1];
    lit.value[2] = light.diffuse[2];
    lit.value[3] = light.diffuse[3];

    vec4 lit2 = wavg(lit, black, 4.0 ,0);

    float amb[4];
    amb[0] = lit2.value[0];
    amb[1] = lit2.value[1];
    amb[2] = lit2.value[2];
    amb[3] = lit2.value[3];
    amb[3] = 0.1;
    // amb[3] = 1.0;

    float diff[4];
    diff[0] = darksteelMaterial.diffuse[0];
    diff[1] = darksteelMaterial.diffuse[1];
    diff[2] = darksteelMaterial.diffuse[2];
    diff[3] = darksteelMaterial.diffuse[3];
    diff[3] = 1.0;

     glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
     sphere();
    
    glPopMatrix();

    glDisable(GL_NORMALIZE);

    // glPointSize(4.0);
    // glBegin(GL_POINTS);
    //  glVertex3fv(light.position);
    // glEnd();
}
void lightSrc() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  config_lights();

  light0.position[0]=0.5+sin(theter*pi_value*.25);
  light0.position[1]=1.75;
  light0.position[2]=cos(theter*pi_value*.25);

  light1.position[0]=-1;
  light1.position[1]=0.8;
  light1.position[2]=2*cos(theter*pi_value);

  light2.position[0]=1.5;
  light2.position[1]=1.4+sin(theter*pi_value*0.5);
  light2.position[2]=1-sin(theter*pi_value*0.5);

  light3.position[0]=0;
  light3.position[1]=3.0;
  light3.position[2]=0;
}
void drawLights(){
  drawlight(light0);
  drawlight(light1);
  drawlight(light2);
  drawlight(light3);
}
void swivel2(){
  // glTranslatef(0,-1.1,-0.0);
  glRotatef(theter*90/3.14/3,1,0,0);
  glRotatef(theter*90/3.14/5,0,1,0);
  glRotatef(theter*90/3.14/7,0,0,1);
}
void swivel1(){
  // glTranslatef(0,-1.1,-0.0);
  glRotatef(-theter*90/10,0,1,0);
  // glRotatef(-theter*90/10,1,0,0);
}
void wobble(){
  glRotatef(15*sin(theter *Rad*180),1,0,0);
  glRotatef(15*cos(theter *Rad*180),0,1,0);
  glRotatef(15*cos(0.5+theter *Rad*180),0,0,1);
}
void mykey(unsigned char key, int x, int y) {

  switch (key) {
  case 'i':
    theta[0] = theta[0] + 1;
    glutPostRedisplay();
    break;
  case 'k':
    theta[0] = theta[0] - 1;
    glutPostRedisplay();
    break;
  case 'j':
    theta[1] = theta[1] + 1;
    glutPostRedisplay();
    break;
  case 'l':
    theta[1] = theta[1] - 1;
    glutPostRedisplay();
    break;
  case 'u':
    theta[2] = theta[2] + 1;
    glutPostRedisplay();
    break;
  case 'o':
    theta[2] = theta[2] - 1;
    glutPostRedisplay();
    break;
  case 'q':
    exit(0);
    break;
  default:
    break;
  } 
} 
void resize(GLsizei w, GLsizei h){

    GLsizei ww,hh;
    init();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // gluOrtho2D(-2000,2000,-2000,2000);

    GLfloat aspect = (GLfloat) w /(GLfloat) h;

    GLfloat fit = 1.5;

    gluPerspective(60,aspect,0.1,5000);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glViewport(0,0,w,h);
}
void init() {

  glEnable(GL_DEPTH_TEST);

  config_lights();
  // isoTri();
  // isoVerts();
}
void config_lights(GLfloat* lit_pos){

  glEnable(GL_LIGHTING);
  // glEnable(GL_NORMALIZE);
  glDisable(GL_NORMALIZE);


  GLfloat light0pos2[] = {0,0,10,0};

  for (int i=0; i<4; i++){
    // light0.position[i]=light0.position[i]-lit_pos[i];
  }

  glEnable(GL_LIGHT0); //light source 0
    glLightfv(GL_LIGHT0, GL_POSITION, light0.position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0.specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0.diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light0.ambient);

  glEnable(GL_LIGHT1); //light source 0
    glLightfv(GL_LIGHT1, GL_POSITION, light1.position);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1.specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1.diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light1.ambient);

  glEnable(GL_LIGHT2); //light source 0
    glLightfv(GL_LIGHT2, GL_POSITION, light2.position);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2.specular);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2.diffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT,  light2.ambient);

  glEnable(GL_LIGHT3); //light source 0
    glLightfv(GL_LIGHT3, GL_POSITION, light3.position);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3.specular);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  light3.diffuse);
    glLightfv(GL_LIGHT3, GL_AMBIENT,  light3.ambient);
}
vec4 avg(vec4 a, vec4 b){
  vec4 temp={{0,0,0,0}};
  temp.value[0] = a.value[0]*.5 + b.value[0]*.5;
  temp.value[1] = a.value[1]*.5 + b.value[1]*.5;
  temp.value[2] = a.value[2]*.5 + b.value[2]*.5;
  temp.value[3] = a.value[3]*.5 + b.value[3]*.5;
  return temp;
}
vec4 wavg(vec4 a, vec4 b, float na, float nb){
  vec4 temp={{0,0,0,0}};
  temp.value[0] = a.value[0]*na + b.value[0]*nb;
  temp.value[1] = a.value[1]*na + b.value[1]*nb;
  temp.value[2] = a.value[2]*na + b.value[2]*nb;
  temp.value[3] = a.value[3]*na + b.value[3]*nb;
  return temp;
}
float clamp(float a, float l, float h){
  if(a < l) a = l;
  if(a > h) a = h;
  return a;
}
float clampB(float a){
  a = clamp(a, 0.0, 1.0);
  return a;
}
float abso(float a){
  if(a < 0) a = -a;
  return a;
}
void cube(){
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  float th2  = 1.5; //line thickness.
  float co = 3.0; //min 1.5, Approx AA at 3.0, max 8.0

  // th2 = 2+2*(sin(theter*pi_value)*.5+.5);
  // co  = 8*(cos(theter*pi_value*.674)*.5+.5);
  // co = clamp(co, 3.0, 8.0);
  
  float frc = 1.0;
  if (th2 <=co){
    frc = th2/co;
    th2 = co;
  }
  float pgr = 0;
  float pgr2 =0;
  int n = 10;
  vec4 in={{.5,.5,.5,1.0}};

  for(int i = th2; i>0; i--)
  {
    pgr = (float)i/th2;
    if (pgr != 1.0)
    {
      glLineWidth(i);

      pgr2= clampB((1.0-pgr)*frc);

      // in=black;
      vec4 tempColor= wavg(in,bgColor,pgr2,1.0-pgr2);
        
      glColor3fv(tempColor.value);
    
      glBegin( GL_LINES);
      for(int q = -n; q<=n; q++){
        glVertex3f( q,0, n);
        glVertex3f( q,0,-n);
        glVertex3f( n,0, q);
        glVertex3f(-n,0, q);
      }
      glEnd();
    }
  }
  // glEnable(GL_LIGHTING);
  // glEnable(GL_DEPTH_TEST);
}
void grid(int size, vec4 color, vec4 bg, float thickness, float blur){
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  float th2  = 1.5; //line thickness.
  float co = 3.0; //min 1.5, Approx AA at 3.0, max 8.0
  th2 = thickness;
  co = blur;
  // th2 = 2+2*(sin(theter*pi_value)*.5+.5);
  // co  = 8*(cos(theter*pi_value*.674)*.5+.5);
  // co = clamp(co, 3.0, 8.0);
  
  float frc = 1.0;
  if (th2 <=co){
    frc = th2/co;
    th2 = co;
  }
  float pgr = 0;
  float pgr2 =0;
  int n = 10;
  n = size;
  // vec4 in={{.5,.5,.5,1.0}};
  // in = color;

  //normie
  // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  // // addition
  // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

  // // Min
  // glBlendEquationSeparate(GL_MIN, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

  // Max
  // glBlendEquationSeparate(GL_MAX, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

  // Multiply
  // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_DST_COLOR, GL_ZERO, GL_ONE, GL_ZERO);
 
  // 0 = D - S*D
  // glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_DST_COLOR, GL_ONE, GL_ONE, GL_ZERO);

  
  for(int i = th2; i>0; i--)
  {
    // i = th2/2;
    pgr = (float)i/th2;
    if (pgr != 1.0)
    {
      glLineWidth(i);

      pgr2= clampB((1.0-pgr)*frc);
      // float pgr3= pgr2/(float)th2;
      // pgr2;
      // vec4 tempColor= wavg(color,bg,pgr2,1.0-pgr2);
      vec4 tempColor= wavg(color,black,pgr2,1.0-pgr2);      
      // tempColor = color;  
      glColor3fv(tempColor.value);
  
      glBegin( GL_LINES);
      for(int q = -n; q<=n; q++){
        glVertex3f( q,0, n);
        glVertex3f( q,0,-n);
        glVertex3f( n,0, q);
        glVertex3f(-n,0, q);
      }
      glEnd();
    }
  }
   glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  // glEnable(GL_LIGHTING);
  // glEnable(GL_DEPTH_TEST);
}
void grid2(int size, vec4 color, vec4 bg, float thickness, float blur){
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
 glEnable(GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  float th2  = 1.5; //line thickness.
  float co = 3.0; //min 1.5, Approx AA at 3.0, max 8.0
  th2 = thickness;
  co = blur;
  // th2 = 2+2*(sin(theter*pi_value)*.5+.5);
  // co  = 8*(cos(theter*pi_value*.674)*.5+.5);
  // co = clamp(co, 3.0, 8.0);
  
  float frc = 1.0;
  if (th2 <=co){
    frc = th2/co;
    th2 = co;
  }
  float pgr = 0;
  float pgr2 =0;
  int n = 10;
  n = size;
  // vec4 in={{.5,.5,.5,1.0}};
  // in = color;

  //normie
  // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  // // addition
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

  // // Min
  // glBlendEquationSeparate(GL_MIN, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

  // Max
  // glBlendEquationSeparate(GL_MAX, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);

  // Multiply
  // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_DST_COLOR, GL_ZERO, GL_ONE, GL_ZERO);
 
  // 0 = D - S*D
  // glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
  // glBlendFuncSeparate(GL_DST_COLOR, GL_ONE, GL_ONE, GL_ZERO);

    for(int i = th2; i>0; i--)
    {
      // i = th2/2;
      pgr = (float)i/th2;
      if (pgr != 1.0)
      {
        glLineWidth(i);

        pgr2= clampB((1.0-pgr)*frc);
        // float pgr3= pgr2/(float)th2;
        // pgr2;
        // vec4 tempColor= wavg(color,bg,pgr2,1.0-pgr2);
        vec4 tempColor= wavg(color,black,pgr2,1.0-pgr2);      
        // tempColor = color;  
        glColor3fv(tempColor.value);
    
        glBegin( GL_LINES);
        for(int q = -n; q<=n; q++){
          glVertex3f( q,0, n);
          glVertex3f( q,0,-n);
          glVertex3f( n,0, q);
          glVertex3f(-n,0, q);
        }
        glEnd();
      }
  }
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  // glEnable(GL_LIGHTING);
  // glEnable(GL_DEPTH_TEST);
}
void mymotion() {
    // usleep(16667);
    theter +=0.01;
    glutPostRedisplay();
}
int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 480);
    glutCreateWindow("Illumination");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutIdleFunc( mymotion );
    glutKeyboardFunc(mykey);

    init();
    glutMainLoop();
}
