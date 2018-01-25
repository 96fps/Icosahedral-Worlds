 // Simple OpenGL graphics program

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

GLfloat theta = 0.0;

GLfloat isovert[12][3] = {0};
int isoTriangle[20][3] = {0};

GLfloat isoNetvert[22][3] = {0};
int isoNetTriangle[20][3] = {0};

int sec = 0;

double AU = 149.6; // in gigameters (million km)
double timescale = 360/60; // 60sec = one earth year
double Rad = 6.28/360;

double enlargement = 10;
// double enlargement = 5;
double shrinkdist = 1/10;



/*
  Planetary Data:
  =================
  - Diameter (km),
  - dist (Gm),
  - day length (hours),
  - number of moons 
*/
double planets[10][4] = 
  {
    {  4879,    57.9, 4222.6, 0}, //mercury
    { 12104,   108.2,   2802, 0}, //venus
    { 12756,   149.6,   24.0, 1}, //earth
    {  6792,   227.9,   24.7, 2}, //mars
    {   473,  414.01,   9.07, 0}, //ceres
    {142984,   778.6, 4222.6, 4}, //jupiter
    {120536,  1433.5,   2802, 4}, //saturn
    { 51118,  2872.5,   24.0, 3}, //uranus
    { 49528,  4495.1,   24.7, 2}, //neptune
    {1188.3, 5906.38,    123, 1}, //pluto
  };

// planet colors (rgb)
double planetColors[10][3] =
  {
    { .8, .8, .8 }, //mercury
    {  1,  1,  1 }, //venus
    {  0,  1,  0 }, //earth
    {  1,  1,  0 }, //mars
    { .5, .5, .5 }, //ceres
    { .8, .7, .3 }, //jupiter
    { .8, .8, .6 }, //saturn
    { .6, .7,  1 }, //uranus
    {  0,  0,  1 }, //neptune
    {  1, .7, .6 }, //pluto
  };

double sunMass = 332946; //in earth masses
double planetMasses[10]=
{
  0.0553,
  0.815,
  1.0,
  0.107,
  0.00015,
  317.8,
  95.2,
  14.5,
  17.1,
  0.00218,
};

double moonStats[3]= {1737.1, .384399, 29.530589 };
/*===========
  - Radius (km),
  - dist (Gm),
  - synodic period, (in earth days) ~ Month
*/
double monthPyear= 365.25/29.530589;
double MU = .384399;

void display(){

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0,0,0,0);

  glPointSize(4.0);
  glLineWidth(1.5);

  glPushMatrix();
    configcamera();
  glEnable(GL_CULL_FACE);

  // superdivIsa(3);
  // superdivIsaNet(3);
  
  glPushMatrix();
  glScalef(50,50,50);
  cube();
  glPopMatrix();

  glRotatef(90,0,1,0);
  solarSystem();

  glPopMatrix();
  glutSwapBuffers();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void sphere(double col[3]){
  GLUquadricObj *mysphere;
  mysphere = gluNewQuadric();

  double r = col[0];
  double g = col[1];
  double b = col[2];

  glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricDrawStyle(mysphere, GLU_FILL);
    glColor3f (r,g,b);
    gluSphere(mysphere,1.0,15,9);
    gluQuadricDrawStyle(mysphere, GLU_LINE);
    glColor3f (r*0.7,g*0.7,b*0.7);
    gluSphere(mysphere,1.005,15,9);
  glPopMatrix();
}

void planet(int i){

  double radius = planets[i][0]/2;
  double size = radius/10000;

  glPushMatrix();
  glScalef(size,size,size);     
  // scaled so planet radius = 1.0 units
    sphere(planetColors[i]);

    if(i==6){
       ring2(1.9,0.2);
       ring2(2.5,0.3);
    }
  glPopMatrix();
}
void moon(int parent, int index){
  double color[] = {10,10,10};
    sphere(color);
}
void planetarySys(double param[4],int index){
  glPushMatrix();

      double dist = param[1];
      double radius = param[0]/2;
      double size = radius/10000;
      double inAU = dist/AU;
      double year = 1.0/(inAU*inAU); //years per year

     
      // ORBIT PARENT
      glRotatef(theta *timescale* year,0,1,0);

      //make distances smaller
      glScalef(shrinkdist,shrinkdist,shrinkdist);    
      // DRAW PATH
      ring(dist,size);
      
      glPushMatrix();
      glTranslatef(dist,0,0);
      // position RELATIVE TO CENTER OF PLANET

        //make planets bigger
        glScalef(enlargement,enlargement,enlargement);  
        // Draw the planet
        planet(index);

        // MOON-time ==
        // if(index==2){//for earth
        //   moonSys(moonStats[1], moonStats[0], index, 0);
        // }
        // else
        {
          double d1= moonStats[1] * pow(planets[index][0]/planets[2][0],0.7);
          // d1 += planets[index][0]/2.0;
           double r1= moonStats[0] * pow(planets[index][0]/planets[2][0],0.2);
          if(index==3){
            r1/=4;
          }
          for (int i =0; i<param[3]; i++){
            moonSys(d1, r1, index, i);
            d1 *= 1.2;
            r1 *= 0.8;
          }
        }

      glPopMatrix();
    glPopMatrix();
}
void moonSys(double dist, double radius, int parent, int index){
  glPushMatrix();
      // double size = radius/6;
      double size = radius/5000;
      double p_mass = planetMasses[parent];
      double grav_factor = p_mass;
      // double grav_factor = 1;
      double d_inMu = dist/MU;//distances in moon distances
      double month = 1.0/(d_inMu*d_inMu); //months per month

      double distScaled=dist*6;
  

     //make distances smaller
      // double shrintMint=sqrt(shrinkdist);
      // glScalef(shrintMint,shrintMint,shrintMint);    
 
      // ORBIT PARENT
      glRotatef( theta *timescale*monthPyear*month*grav_factor,0,1,0);
      // DRAW PATH
      // ring(distScaled,size);
      
      glPushMatrix();
      glTranslatef(distScaled,0,0);
      // position RELATIVE TO CENTER OF MOON
    
    //make planets bigger
        // glScalef(enlargement,enlargement,enlargement);  
    
        glPushMatrix();
        glScalef(size,size,size);
        // scaled so moon radius = 1.0 units
        moon(parent, index);
        glPopMatrix();
        
      glPopMatrix();
    glPopMatrix();
}
void sun(){
  double color[] = {1.1,.6,.0};
  sphere(color);
}
void ring(double dist,double size){
  GLUquadricObj *ring;
  ring = gluNewQuadric();
  double a = 0.15*size;

  glDisable(GL_CULL_FACE);
  glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricDrawStyle(ring, GLU_FILL);
    glColor3f (.2,.2,.2);
    gluDisk(ring,dist-a,dist+a,32,1);
  glLineWidth(1.0);
    gluQuadricDrawStyle(ring, GLU_LINE);
    // glColor3f (1,0.5,0);
    gluDisk(ring,dist-a,dist+a,32,1);
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}
void ring2(double dist,double size){
  GLUquadricObj *ring;
  ring = gluNewQuadric();
  double a = size;

  glDisable(GL_CULL_FACE);
  glPushMatrix();
    glRotatef(90,1,0,0);
    gluQuadricDrawStyle(ring, GLU_FILL);
    glColor3f(.6, .6, .4 );
    gluDisk(ring,dist-a,dist+a,32,1);
  glLineWidth(1.0);
    // gluQuadricDrawStyle(ring, GLU_LINE);
    // glColor3f(.3, .3, .2 );
    // gluDisk(ring,dist-a,dist+a,32,1);
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}
void solarSystem(){

	
	sun();

	for(int i =0; i<10; i++){
		planetarySys(planets[i], i);
	}
}
void configcamera(){

    // lowOrbit();  

    // glTranslatef(0,0,-3);
    // glTranslatef(0,0,-5);
    // glTranslatef(0,0,-8);
    glTranslatef(0,0,-120);
    // glTranslatef(0,0,-50);

     // glRotatef( 5,1,0,0);
     // glRotatef(5,1,0,0);
     // glRotatef(15,1,0,0);
     glRotatef(20,1,0,0);
     // glRotatef(30,1,0,0);
     // glRotatef(45,1,0,0);

   // wobble();
   swivel1(90/10);

    // swivel2();  


   //   glRotatef(10,1,0,0);
   // swivel1();
}
void wobble(){
  glRotatef(1*sin(theta * Rad * 90/10),1,0,0);
  glRotatef(1*cos(theta * Rad * 90/10),0,1,0);
}
void swivel1(double speed){
     // glRotatef(2,1,0,0);
  glRotatef(theta * 90/10,0,1,0);
}
void lowOrbit(){
  glRotatef(30,1,0,0);
  glRotatef(-60,0,0,1);
  glTranslatef(0,-1.1,-0.0);

  glRotatef(-theta*90/10, 0,1,0);
  glRotatef(-theta*90/10, 1,0,0);
}
void swivel2(){
  glTranslatef(0,-1.1,-0.0);
  glRotatef(-theta*90/10,0,1,0);
  glRotatef(-theta*90/10,1,0,0);
}
void cube(){
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
}
void mymotion() {
    usleep(16667); // 1/60th of a sec
    theta +=0.016667;
    glutPostRedisplay();

    if (theta >=sec){
      sec++;
      // printf("tick sec");
    }

    // enlargement = 1+(sin(theta*Rad*360/10)+1)*10;
    // enlargement = 1+(sin(theta*Rad*360/10)+1)*5 + 5;
    enlargement = 12;

    shrinkdist = 1.0/enlargement;
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
int main(int argc, char** argv){

    glutInit( &argc, argv );
    // glutInitDisplayMode(GLUT_DOUBLE)
    glutInitWindowSize(800,480);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH );
    glutCreateWindow("Solar System (not to scale)");
    glutDisplayFunc( display );
    glutIdleFunc( mymotion );
    glutReshapeFunc( resize );
    glutMainLoop();

    return 0;
}
