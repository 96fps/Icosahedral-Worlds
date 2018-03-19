#include <GL/glut.h>
#include <stdlib.h>

static GLfloat theta[] = {0.0, 0.0, 0.0} ;

GLfloat theter = 0.0;
double Rad = 6.28/360;

GLfloat isovert[12][3] = {0};
int isoTriangle[20][3] = {0};

typedef struct materialStruct{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

materialStruct brassMaterial = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

materialStruct blackPlasticMaterial = {
  {    0,    0,    0, 1.0},
  { 0.01, 0.01, 0.01, 1.0},
  { 0.50, 0.50, 0.50, 1.0},
  32.0
};

materialStruct basicMaterial = {
  { 0, 0, 0, 1}, //ambient
  { 1, 1, 1, 1}, //diffuse
  { 0, 0, 0, 1}, //sepcular
  128.0
};

//cube
GLfloat vertices[8][3] = 
  { {-1,-1,-1},{ 1,-1,-1},
    { 1, 1,-1},{-1, 1,-1}, 
    {-1,-1, 1},{ 1,-1, 1}, 
    { 1, 1, 1},{-1, 1, 1}};
//   back:  3, 2,
//          0, 1,
//
//   front: 7, 6,
//          4, 5,

// specify light properties below


 GLfloat light0_pos[]  = {-.9, -.9, -.9, 1};
 // GLfloat light0_diff[] = {1000,1000,1000, 1};
 GLfloat light0_diff[] = {.7,.7,.7, 1};
 GLfloat light0_amb[]  = { 0, 0, 0, 0};
 GLfloat light0_spec[] = { 1, 1, 1, 1};

 GLfloat light1_pos[]  = {10, 0, 0, 0};
 GLfloat light1_diff[] = {.1, 0, 0, 1};
 GLfloat light1_amb[]  = { 0, 0, 0, 1};
 GLfloat light1_spec[] = { 0, 0, 0, 1};

 GLfloat light2_pos[]  = { 0,10, 0, 0};
 GLfloat light2_diff[] = { 0,.1, 0, 1};
 GLfloat light2_amb[]  = { 0, 0, 0, 1};
 GLfloat light2_spec[] = { 0, 0, 0, 1};

 GLfloat light3_pos[]  = { 0, 0,10, 0};
 GLfloat light3_diff[] = { 0, 0,.1, 1};
 GLfloat light3_amb[]  = { 0, 0, 0, 1};
 GLfloat light3_spec[] = { 0, 0, 0, 1};

 GLfloat light4_pos[]  = {-1, 0, 0, 0};
 GLfloat light4_diff[] = { 0,.1,.1, 1};
 GLfloat light4_amb[]  = { 0, 0, 0, 1};
 GLfloat light4_spec[] = { 0, 0, 0, 1};

 GLfloat light5_pos[]  = { 0,-1, 0, 0};
 GLfloat light5_diff[] = {.1, 0,.1, 1};
 GLfloat light5_amb[]  = { 0, 0, 0, 1};
 GLfloat light5_spec[] = { 0, 0, 0, 1};

 GLfloat light6_pos[]  = { 0, 0,-1, 0};
 GLfloat light6_diff[] = {.1,.1, 0, 1};
 GLfloat light6_amb[]  = { 0, 0, 0, 1};
 GLfloat light6_spec[] = { 0, 0, 0, 1};


void display(void)
{
  /* display callback, clear frame buffer and z buffer,
     rotate cube and draw, swap buffers */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  // config_lights();
  glTranslatef(0,0,-4);

  glRotatef(theta[0], 1.0, 0.0, 0.0);
  glRotatef(theta[1], 0.0, 1.0, 0.0);
  glRotatef(theta[2], 0.0, 0.0, 1.0);
  // swivel1();

  glDisable(GL_LIGHTING);
  glLineWidth(2.0);
  coordinate();
  cube();
  glEnable(GL_LIGHTING);

  config_lights();
  lightSrc();

  wobble();
  superdivIsa(3);

  glFlush();
  glutSwapBuffers();
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
void Triangle(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color){
  glEnable(GL_LIGHTING);

  GLfloat colour[4]={0};

  for(int i = 0; i<3; i ++)
    colour[i]=color[i];

  colour[4]=0.5;

   glBegin(GL_POLYGON);
    {
        glColor3f (color[0], color[1], color[2]);

      materials(&basicMaterial);
      // materials(&blackPlasticMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);

        // glColor3f (1,0,0);
  		glNormal3fv(a);
      // config_lights(a);
        glVertex3fv(a);
        // glColor3f (0,1,0);
  		glNormal3fv(b);
      // config_lights(b);
        glVertex3fv(b);
        // glColor3f (0,0,1);
  		glNormal3fv(c);
      // config_lights(c);
        glVertex3fv(c);
    }
    glEnd();
}
void superdivIsa(int m){
  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};

    color[0]=((i/2)*.1  )*0.8 +0.2;
    color[1]=(1-(i/2)*.1)*0.8 +0.2;
    color[2]=  0              +0.2;
    
    superDivTri(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color, m);
  }
}
void superDivTri(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m) {
  GLfloat v[7][3];
  int j;
  int i;
  if (m>0){
    for(j=0;j<3;j++){

      v[0][j]=(a[j]+b[j]+c[j])/3;

      v[1][j]=(2*a[j]+b[j])/3;   
      v[2][j]=(2*a[j]+c[j])/3;

      v[3][j]=(a[j]+2*b[j])/3;
      v[4][j]=(2*b[j]+c[j])/3;

      v[5][j]=(a[j]+2*c[j])/3;
      v[6][j]=(b[j]+2*c[j])/3;
    }

    //normalize
    for(j=0;j<7;j++){
    GLfloat magnitude = 
      sqrt(v[j][0]*v[j][0]
          +v[j][1]*v[j][1]
          +v[j][2]*v[j][2]);
      for(i=0;i<3;i++){
        v[j][i]/=magnitude;
      }
    }

    GLfloat color2[3]={0};
    color2[0]=color[0]*0.5+0.5;
    color2[1]=color[1]*0.5+0.5;
    color2[2]=color[2]*0.5+0.5;

    superDivTri(a,v[1],v[2],color2,m-1);
    superDivTri(v[3],b,v[4],color2,m-1);
    superDivTri(v[5],v[6],c,color2,m-1);

    superDivTri(v[0],v[2],v[1],color,m-1);
    superDivTri(v[4],v[0],v[3],color,m-1);
    superDivTri(v[6],v[5],v[0],color,m-1);

    superDivTri(v[0],v[4],v[6],color,m-1);
    superDivTri(v[2],v[0],v[5],color,m-1);
    superDivTri(v[1],v[3],v[0],color,m-1);
  }
  else Triangle(a,b,c,color);
}
void isoTri(){
  for(int i = 0; i<5; i++){
    for(int j = 0; j<4; j++){
     
      if (j==0){
        isoTriangle[i*4+j][0]=(i+1)%5+1;
        isoTriangle[i*4+j][1]=i%5+1;
        isoTriangle[i*4+j][2]=0;
      }
      if (j==1){
        isoTriangle[i*4+j][1]=(i+1)%5+1;
        isoTriangle[i*4+j][0]=i%5+1;
        isoTriangle[i*4+j][2]=(i+3)%5+6;
      }
      if (j==2){
        isoTriangle[i*4+j][1]=(i+2)%5+6;
        isoTriangle[i*4+j][0]=(i+3)%5+6;
        isoTriangle[i*4+j][2]=i%5+1;
      }
      if (j==3){
        isoTriangle[i*4+j][0]=(i+2)%5+6;
        isoTriangle[i*4+j][1]=(i+3)%5+6;
        isoTriangle[i*4+j][2]=11;
      }
    }
  }
}
void isoVerts(){
  isovert[0][1]=1.0;
  isovert[11][1]=-1.0;

  double lat=atan(0.5);

  double lon=72.0/180.0*3.141592;

  GLfloat rote[3] = {0,0,0};
  GLfloat rot2[3] = {0,0,0};

  rote[0]=cos(lat);
  rote[1]=sin(lat);

  for(int i=0; i<5; i++){

    rot2[0]=cos(lon*i)*rote[0] - sin(lon*i)*rote[2];
    rot2[1]=rote[1];
    rot2[2]=sin(lon*i)*rote[0] + cos(lon*i)*rote[2];

    isovert[i+1][0]=rot2[0];
    isovert[i+1][1]=rot2[1];
    isovert[i+1][2]=rot2[2];
    isovert[i+6][0]=-rot2[0];
    isovert[i+6][1]=-rot2[1];
    isovert[i+6][2]=-rot2[2];

  }
}
void coordinate(void) {
  // x coordinate
  glColor3f(0,1,1);
  glRasterPos3f(2,0,0);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'X');
  glColor3f(1,0,0);
  glBegin(GL_LINES);
   glVertex3f(0, 0, 0);
   glVertex3f(2, 0, 0);
  glEnd();

  // y
  glColor3f(1,0,1);
  glRasterPos3f(0,2,0);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');
  glColor3f(0,1,0);
  glBegin(GL_LINES);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 2, 0);
  glEnd();

  //z
  glColor3f(1,1,0);
  glRasterPos3f(0,0,2);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Z');
  glColor3f(0,0,1);
  glBegin(GL_LINES);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 0, 2);
  glEnd();
}
void lightSrc() {
  glDisable(GL_LIGHTING);
  // This function draws x, y, z coordinates

  light0_pos[0]=2*sin(theter)+1.5;
  light0_pos[1]=0;
  light0_pos[2]=2*cos(theter);

  // x coordinate
  glColor3f(1,1,1);
  glRasterPos3fv(light0_pos);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
  glBegin(GL_LINES);
   glVertex3f(0, 0, 0);
   glVertex3fv(light0_pos);
  glEnd();

  glEnable(GL_LIGHTING);
}
void quad(int a, int b, int c , int d){
  glBegin(GL_POLYGON);
   // glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    // glLightfv(GL_LIGHT0, GL_POSITION, light0_pos2[0]);
    glVertex3fv(vertices[a]);
    // glLightfv(GL_LIGHT0, GL_POSITION, light0_pos2[1]);
    glVertex3fv(vertices[b]);
    // glLightfv(GL_LIGHT0, GL_POSITION, light0_pos2[2]);
    glVertex3fv(vertices[c]);
    // glLightfv(GL_LIGHT0, GL_POSITION, light0_pos2[3]);
    glVertex3fv(vertices[d]);
  glEnd();
}
void colorcube(void){
  glPushMatrix();
  glScalef(.8,.8,.8);
    glNormal3f(0,0,1);
  	quad(4, 5, 6, 7); //front side
    glNormal3f(1,0,0);
  	quad(1, 2, 6, 5); //right side
    glNormal3f(0,1,0);
  	quad(2, 3, 7, 6); //top side
    glNormal3f(-1,0,0);
  	quad(3, 0, 4, 7); //left side
    glNormal3f(0,0,-1);
  	quad(0, 3, 2, 1); //rear side
    glNormal3f(0,-1,0);
  	quad(0, 1, 5, 4); //bottom side
  glPopMatrix();
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
    glClearColor(0,0,0,0);

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

  glClearColor(0,0,0,0);

  glEnable(GL_DEPTH_TEST);

  // specify light properties below

  config_lights();
  isoTri();
  isoVerts();
}
void config_lights(GLfloat* lit_pos){

  glEnable(GL_LIGHTING);
  // glEnable(GL_NORMALIZE);
  glDisable(GL_NORMALIZE);


  GLfloat light0_pos2[] = {0,0,0,0};
  GLfloat light1_pos2[] = {0,0,0,0};
  GLfloat light2_pos2[] = {0,0,0,0};
  GLfloat light3_pos2[] = {0,0,0,0};

  for (int i=0; i<4; i++){
    light0_pos2[i]=light0_pos[i]-lit_pos[i];
    light1_pos2[i]=light1_pos[i]-lit_pos[i];
    light2_pos2[i]=light2_pos[i]-lit_pos[i];
    light3_pos2[i]=light3_pos[i]-lit_pos[i];
  }
  glEnable(GL_LIGHT0); //light source 0
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos2);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diff);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_amb);

  glEnable(GL_LIGHT1); //light source 1
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diff);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_amb);

  glEnable(GL_LIGHT2); //light source 2
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_spec);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2_diff);
    glLightfv(GL_LIGHT2, GL_AMBIENT,  light2_amb);

  glEnable(GL_LIGHT3); //light source 3
    glLightfv(GL_LIGHT3, GL_POSITION, light3_pos2);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3_spec);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  light3_diff);
    glLightfv(GL_LIGHT3, GL_AMBIENT,  light3_amb);

  glEnable(GL_LIGHT4); //light source 1
    glLightfv(GL_LIGHT4, GL_POSITION, light4_pos);
    glLightfv(GL_LIGHT4, GL_SPECULAR, light4_spec);
    glLightfv(GL_LIGHT4, GL_DIFFUSE,  light4_diff);
    glLightfv(GL_LIGHT4, GL_AMBIENT,  light4_amb);

  glEnable(GL_LIGHT5); //light source 2
    glLightfv(GL_LIGHT5, GL_POSITION, light5_pos);
    glLightfv(GL_LIGHT5, GL_SPECULAR, light5_spec);
    glLightfv(GL_LIGHT5, GL_DIFFUSE,  light5_diff);
    glLightfv(GL_LIGHT5, GL_AMBIENT,  light5_amb);

  glEnable(GL_LIGHT6); //light source 3
    glLightfv(GL_LIGHT6, GL_POSITION, light6_pos);
    glLightfv(GL_LIGHT6, GL_SPECULAR, light6_spec);
    glLightfv(GL_LIGHT6, GL_DIFFUSE,  light6_diff);
    glLightfv(GL_LIGHT6, GL_AMBIENT,  light6_amb);
}
void cube(){
  glDisable(GL_LIGHTING);
  glLineWidth(1.1);
  glBegin( GL_LINES);  
    {

        for(int q = -10; q<=10; q++){
          glColor3f ( .2,.1,.1);
            glVertex3f( 10,  q, 10);
            glVertex3f( 10,  q,-10);
            glVertex3f( 10, 10,  q);
            glVertex3f( 10,-10,  q);

            glVertex3f(-10,  q, 10);
            glVertex3f(-10,  q,-10);
            glVertex3f(-10, 10,  q);
            glVertex3f(-10,-10,  q);

          glColor3f ( .1,.2,.1);
            glVertex3f(  q, 10, 10);
            glVertex3f(  q, 10,-10);
            glVertex3f( 10, 10,  q);
            glVertex3f(-10, 10,  q);

            glVertex3f(  q,-10, 10);
            glVertex3f(  q,-10,-10);
            glVertex3f( 10,-10,  q);
            glVertex3f(-10,-10,  q);

          glColor3f ( .1,.1,.2);
            glVertex3f(  q, 10, 10);
            glVertex3f(  q,-10, 10);
            glVertex3f( 10,  q, 10);
            glVertex3f(-10,  q, 10);

            glVertex3f(  q, 10,-10);
            glVertex3f(  q,-10,-10);
            glVertex3f( 10,  q,-10);
            glVertex3f(-10,  q,-10);
        }
  }
  glEnd();
  

      glLineWidth(2.0);

 glBegin( GL_LINES);  
    {
      glColor3f ( .5,.5,.5);


        for(int q = -10; q<=10; q++){
          glColor3f ( .1,.05,.05);
            glVertex3f( 10,  q, 10);
            glVertex3f( 10,  q,-10);
            glVertex3f( 10, 10,  q);
            glVertex3f( 10,-10,  q);

            glVertex3f(-10,  q, 10);
            glVertex3f(-10,  q,-10);
            glVertex3f(-10, 10,  q);
            glVertex3f(-10,-10,  q);

          glColor3f ( .05,.1,.05);
            glVertex3f(  q, 10, 10);
            glVertex3f(  q, 10,-10);
            glVertex3f( 10, 10,  q);
            glVertex3f(-10, 10,  q);

            glVertex3f(  q,-10, 10);
            glVertex3f(  q,-10,-10);
            glVertex3f( 10,-10,  q);
            glVertex3f(-10,-10,  q);

          glColor3f ( .05,.05,.1);
            glVertex3f(  q, 10, 10);
            glVertex3f(  q,-10, 10);
            glVertex3f( 10,  q, 10);
            glVertex3f(-10,  q, 10);

            glVertex3f(  q, 10,-10);
            glVertex3f(  q,-10,-10);
            glVertex3f( 10,  q,-10);
            glVertex3f(-10,  q,-10);
        }

  }
  glEnd();

  glEnable(GL_LIGHTING);
}
void sphere(){

  GLUquadricObj *mysphere;
  mysphere = gluNewQuadric();

  glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricDrawStyle(mysphere, GLU_FILL);
    gluSphere(mysphere,1,15,9);
  glPopMatrix();
}

void ring(double dist,double size){
  GLUquadricObj *ring;
  ring = gluNewQuadric();

  glDisable(GL_CULL_FACE);
  glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricDrawStyle(ring, GLU_FILL);
    glColor3f (.2,.2,.2);
    gluDisk(ring,dist-size,dist+size,64,4);
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}

void mymotion() {
    // usleep(16667);
    theter +=0.01;
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

/* need both double buffering and z buffer */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Illumination");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutIdleFunc( mymotion );
    glutKeyboardFunc(mykey);

    init();
    glutMainLoop();
}
