// Simple OpenGL graphics program

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

GLfloat theta = 0.0;

GLfloat isovert[12][3] = {0};
int isoTriangle[20][3] = {0};
// int isoTriangle[20][3] = 
//   { {2,1,0}, {3,2,0}, {4,3,0}, {5,4,0}, {1,5,0},
//     {5,1,8}, {9,8,1}, {1,2,9}, {10,9,2}, {0,0,0},
//     {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
//     {6,7,11}, {7,8,11}, {8,9,11}, {9,10,11}, {10,6,11},
//    };

void display(){

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);

    glPointSize(4.0);
    glLineWidth(1.5);

    glPushMatrix();
    // glTranslatef(0,-1.05,-0.3);
    glTranslatef(0,0,-3);

    //6-DOF orbit
      glRotatef(15,1,0,0);
      glRotatef(theta*360/3.14/3,1,0,0);
      glRotatef(theta*360/3.14/5,0,1,0);
      glRotatef(theta*360/3.14/7,0,0,1);
    

    // //Wobble
    //   glRotatef(sin(theta*360/3.14/60)*5,1,0,0);
    //   glRotatef(cos(theta*360/3.14/60)*5,0,1,0);

    //   glRotatef(45,1,0,0);
      // glRotatef(0,0,1,0);
    
    // Orbit equator
      // glRotatef(30,1,0,0);
      // glRotatef(90,1,0,0);
      // glRotatef(-theta*360/3.14/3,0,1,0);
      // glRotatef(-theta*360/3.14/3,1,0,0);
    

    glEnable(GL_CULL_FACE);

    // isa();
    // solidIsa2();
    // subdivIsa(0);
    superdivIsa(3);
    // supersubdivIsa((int)(theta*5) % 5);
    // supersubdivIsa(3);
    // superdivIsa((int)(theta*10) % 4);
  // isahedron();

  cube();

    glPopMatrix();
    glutSwapBuffers();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Triangle(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color)
{
   glBegin(GL_POLYGON);
    {
        glColor3f (color[0], color[1], color[2]);
        // glColor3f (1,0,0);
        glVertex3fv(a);
        // glColor3f (0,1,0);
        glVertex3fv(b);
        // glColor3f (0,0,1);
        glVertex3fv(c);
    }
    glEnd();

    // glBegin(GL_POLYGON);
    // {
    //     // glColor3f (color[0], color[1], color[2]);
    //     glColor3f (1,0,0);
    //     glVertex3fv(a);
    //     glColor3f (0,1,0);
    //     glVertex3fv(b);
    //     glColor3f (0,0,1);
    //     glVertex3fv(c);
    // }
    // glEnd();

    // glBegin(GL_LINE_LOOP);
    // {
    //     glColor3f (color[0]*0.5, color[1]*0.5, color[2]*0.5);
    //     // glColor3f (1,0,0);
    //     glVertex3fv(a);
    //     // glColor3f (0,1,0);
    //     glVertex3fv(b);
    //     // glColor3f (0,0,1);
    //     glVertex3fv(c);
    // }
    // glEnd();
}

void subDivTri(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m) 
{
  GLfloat v[3][3];
  int j;
  int i;
  // if (m>1)
  if (m>0)
  {
    for(j=0;j<3;j++){
      v[0][j]=(a[j]+b[j])/2;
      v[1][j]=(a[j]+c[j])/2;
      v[2][j]=(b[j]+c[j])/2;
    }
    for(j=0;j<3;j++){
    
    GLfloat magnitude = 
      sqrt(v[j][0]*v[j][0]
          +v[j][1]*v[j][1]
          +v[j][2]*v[j][2]);
      for(i=0;i<3;i++){
        v[j][i]/=magnitude;
      }
    }
    subDivTri(a,v[0],v[1],color,m-1);
    subDivTri(v[0],b,v[2],color,m-1);
    subDivTri(v[1],v[2],c,color,m-1);
    subDivTri(v[2],v[1],v[0],color,m-1);
  }
  // if (m==1){
  //   superDivTri(a,b,c,color,m-1);
  // }
  else Triangle(a,b,c,color);
}
void supersubDivTri(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m) 
{
  GLfloat v[3][3];
  int j;
  int i;
  // if (m>1)
  if (m>1)
  {
    for(j=0;j<3;j++){
      v[0][j]=(a[j]+b[j])/2;
      v[1][j]=(a[j]+c[j])/2;
      v[2][j]=(b[j]+c[j])/2;
    }
    for(j=0;j<3;j++){
    
    GLfloat magnitude = 
      sqrt(v[j][0]*v[j][0]
          +v[j][1]*v[j][1]
          +v[j][2]*v[j][2]);
      for(i=0;i<3;i++){
        v[j][i]/=magnitude;
      }
    }
    supersubDivTri(a,v[0],v[1],color,m-1);
    supersubDivTri(v[0],b,v[2],color,m-1);
    supersubDivTri(v[1],v[2],c,color,m-1);
    supersubDivTri(v[2],v[1],v[0],color,m-1);
  }
  else if (m==1){
    superDivTri(a,b,c,color,m);
  }
  else Triangle(a,b,c,color);
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
 
    // glBegin(GL_POINTS);
    // {
    //     glColor3f(1,0,0);
    //     glVertex3fv(a);
    //     glColor3f(0,1,0);
    //     glVertex3fv(b);
    //     glColor3f(0,0,1);
    //     glVertex3fv(c);
    //   for(j=0;j<7;j++){
    //     glColor3f(j/8.0,j/8.0,j/8.0);
    //     glVertex3fv(v[j]);
    //   }
    // }
    // glEnd();
    // glBegin(GL_LINE_STRIP);
    // {
    //   for(j=0;j<7;j++){
    //     glColor3f(j/8.0,j/8.0,j/8.0);
    //     glVertex3fv(v[j]);
    //   }
    // }
    // glEnd();

    GLfloat color2[3]={0};
    color2[0]=color[0]*0.9;
    color2[1]=color[1]*0.9;
    color2[2]=color[2]*0.9;

    if(m%2==1){
      color2[0]=color[0]*.8;
      color2[1]=color[1]*.8;
      color2[2]=color[2]*.8+0.2;
    }
    else{
      color2[0]=color[0]*.7;
      color2[1]=color[1]*.7;
      color2[2]=color[2]*.7+0.3;
    }
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

void supersubdivIsa(int m){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};
    // color[0]=(i/4)*.2;
    // color[1]= 1-(i/4)*.2;
    // color[2]=  0;
    

    color[0]=(i/2)*.1;
    color[1]= 1-(i/2)*.1;
    color[2]=  0;
    

    supersubDivTri(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color, m);
   
  }

}void superdivIsa(int m){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};
    // color[0]=(i/4)*.2;
    // color[1]= 1-(i/4)*.2;
    // color[2]=  0;
    

    color[0]=(i/2)*.1;
    color[1]= 1-(i/2)*.1;
    color[2]=  0;
    

    superDivTri(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color, m);
   
  }
}

void subdivIsa(int m){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};
    // color[0]=(i/4)*.2;
    // color[1]= 1-(i/4)*.2;
    // color[2]=  0;
    

    color[0]=(i/2)*.1;
    color[1]= 1-(i/2)*.1;
    color[2]=  0;
    
    subDivTri(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color, m);

   
  }
}
void solidIsa2(){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};
    color[0]=(i/4)*.2;
    color[1]= 1-(i/4)*.2;
    color[2]=  0;

    // color[0]=(i/2)*.1;
    // color[1]= 1-(i/2)*.1;
    // color[2]=  0;
    
    Triangle(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color);
   
  }
}

void solidIsa(){

  for(int i = 0; i<20; i ++)
  {
    //isoTriangle[i]
    glBegin(GL_POLYGON);
    {
        glColor3f ((i/4)*.2,1-(i/4)*.2,0);
        // glColor3f (1,0,0);
        glVertex3fv(isovert[isoTriangle[i][0]]);
        // glColor3f (0,1,0);
        glVertex3fv(isovert[isoTriangle[i][1]]);
        // glColor3f (0,0,1);
        glVertex3fv(isovert[isoTriangle[i][2]]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    {
        glColor3f ((i/4)*.1,0.5-(i/4)*.1,0);
        // glColor3f (1,0,0);
        glVertex3fv(isovert[isoTriangle[i][0]]);
        // glColor3f (0,1,0);
        glVertex3fv(isovert[isoTriangle[i][1]]);
        // glColor3f (0,0,1);
        glVertex3fv(isovert[isoTriangle[i][2]]);
    }
    glEnd();
  }
}
void isa(){
    glBegin(GL_POINTS);
    {
        glColor3f (1,1,1);
        for(int i=0; i<12; i++){


          glColor3f (i/12.0,0,1-i/12.0);

          glVertex3f(isovert[i][0],isovert[i][1],isovert[i][2]);
        }
    }
    glEnd();

      glLineWidth(4.0);
     glBegin(GL_LINE_STRIP);
    {
        glColor3f (1,1,1);
        for(int i=0; i<12; i++){


          glColor3f (i/12.0,0,1-i/12.0);

          glVertex3f(isovert[i][0],isovert[i][1],isovert[i][2]);
        }
    }
    glEnd();
}

void isahedron(){

  double lat=atan(0.5)*180.0/3.1415;
  // double lat=90;


  glPointSize(4.0);
  glBegin(GL_POINTS);
  {
      glColor3f (1,1,1);
      glVertex3f( 0,1,0);
      glVertex3f( 0,-1,0);
  }
  glEnd();


  for(int i = 0; i<5; i++){
    glPushMatrix();

    glRotatef(72*i,0,1,0);
    glRotatef(lat,0,0,1);
   
    glBegin(GL_POINTS);
    {
        glColor3f (1,1,1);
        glVertex3f( 1,0,0);
        glVertex3f( -1,0,0);
    }
    glEnd();

    glPopMatrix();
  }

}
void isoTri(){
//   {2,1,0}, {3,2,0}, {4,3,0}, {5,4,0}, {1,5,0},
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
void isoVerts()
{
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
void cube(){

    glLineWidth(1.1);
    glBegin( GL_LINES);  
    {

        for(int q = -10; q<=10; q++){
          glColor3f ( .4,.2,.2);
            glVertex3f( 10,  q, 10);
            glVertex3f( 10,  q,-10);
            glVertex3f( 10, 10,  q);
            glVertex3f( 10,-10,  q);

            glVertex3f(-10,  q, 10);
            glVertex3f(-10,  q,-10);
            glVertex3f(-10, 10,  q);
            glVertex3f(-10,-10,  q);

          glColor3f ( .2,.4,.2);
            glVertex3f(  q, 10, 10);
            glVertex3f(  q, 10,-10);
            glVertex3f( 10, 10,  q);
            glVertex3f(-10, 10,  q);

            glVertex3f(  q,-10, 10);
            glVertex3f(  q,-10,-10);
            glVertex3f( 10,-10,  q);
            glVertex3f(-10,-10,  q);

          glColor3f ( .2,.2,.4);
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

}

void mymotion() {
    // usleep(16667);
    theta +=0.005;
    glutPostRedisplay();
}

void resize(GLsizei w, GLsizei h){

    GLsizei ww,hh;
    glClearColor(.6,.7,.8,0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // gluOrtho2D(-2000,2000,-2000,2000);


    GLfloat aspect = (GLfloat) w /(GLfloat) h;

    GLfloat fit = 1.5;

    gluPerspective(60,aspect,0.1,50);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glViewport(0,0,w,h);
}

int main(int argc, char** argv){


    isoVerts();
    isoTri();

    glutInit( &argc, argv );
    // glutInitDisplayMode(GLUT_DOUBLE)
    glutInitWindowSize(512,512);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH );
    glutCreateWindow("Hello graphics!");
    glutDisplayFunc( display );
    glutIdleFunc( mymotion );
    glutReshapeFunc( resize );
    glutMainLoop();

    return 0;
}
