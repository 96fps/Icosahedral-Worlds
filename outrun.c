// OpenGL graphics program exploring geometry 

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define PI 3.141592
GLfloat theta = 0.0;
double rot = 0;

double scalefactor = (2.0*PI); //const
int detail=1;
int gridOffset=0;
double distance = 0;
double offset = 0;
double speed = 1.0;

void display(){
  //Setup
  glClearColor(0,0,0,0);
  glPointSize(4.0);
  glLineWidth(1.5);
  glEnable(GL_CULL_FACE);
  glPushMatrix();

  //camera stuff
  configcamera();

  // Background:
  cube2();

  //scene:
  grid(10,10,10);
	car();
	sun();
	gnd();

  //cleanup
  glPopMatrix();
  glutSwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void configcamera(){

  glTranslatef(0,0.5,-10);
  glRotatef(1,1,0,0);

  wobble();
}
void wobble(){
  // glRotatef(sin(theta*360/3.14/32)*1,1,0,0);
  glRotatef(cos(theta*90/3.14/47)*5,0,1,0);
}
void sun(){
  glPushMatrix();
  glTranslatef(0,0,-150);
  glScalef(.5,.5,.5);

  glBegin(GL_POLYGON);
  glColor3f(1,0,0);
  glVertex3f( 0, 30,0);
  glColor3f(1,0.3,0);
  glVertex3f(-21, 21,0);
  glColor3f(1,1,0);
  glVertex3f(-30, 0,0);
  glVertex3f( 30, 0,0);
  glColor3f(1,0.3,0);
  glVertex3f( 21, 21,0);

  glEnd();

  glPopMatrix();
}
void gnd(){
  glPushMatrix();
  glTranslatef(0,-2,0);
  glScalef(1000,1000,1000);

  glBegin(GL_POLYGON);
  glColor3f(.1,0,.1);
  glVertex3f(-1,0, 1);
  glVertex3f( 1,0, 1);
  glVertex3f( 1,0,-1);
  glVertex3f(-1,0,-1);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,-1.0,0);
  glTranslatef(0,0,-10);
  glScalef(1,1000,1000);
  glTranslatef(0,0,-1);

  glBegin(GL_POLYGON);
  glColor3f(.3,0,.3);
  glVertex3f(-1,0, 1);
  glVertex3f( 1,0, 1);
  glVertex3f( 1,0,-1);
  glVertex3f(-1,0,-1);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,-1.001,0);
  glTranslatef(0,0,10);
  glScalef(1,1000,1000);
  glTranslatef(0,0,1);

  glBegin(GL_POLYGON);
  glColor3f(.3,0,.3);
  glVertex3f(-1,0, 1);
  glVertex3f( 1,0, 1);
  glVertex3f( 1,0,-1);
  glVertex3f(-1,0,-1);
  glEnd();

  glPopMatrix();
}
void car(){
  glPushMatrix();
  glTranslatef(0.5,-1,7+sin(theta/4.0));
  glScalef(0.01,0.01,0.01);

  glBegin(GL_POLYGON);
  // glColor3f(.5,.5,.5);
  glColor3f(1,1,1);
  glVertex3f(-28, 15, 45);
  glVertex3f( 28, 15, 45);
  glVertex3f( 28, 15,-45);
  glVertex3f(-28, 15,-45);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(.25,.25,.25);
  // glColor3f(1,1,1);
  glVertex3f(-28,15,-45);
  glVertex3f( 28,15,-45);
  glVertex3f( 28, 5,-45);
  glVertex3f(-28, 5,-45);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(.25,.25,.25);
  // glColor3f(1,1,1);
  glVertex3f( 28,15, 45);
  glVertex3f(-28,15, 45);
  glVertex3f(-28, 5, 45);
  glVertex3f( 28, 5, 45);
  glEnd();

    glBegin(GL_POLYGON);
  glColor3f(.6,.6,.6);
  // glColor3f(1,1,1);
  glVertex3f(-28,15, 45);
  glVertex3f(-28,15,-45);
  glVertex3f(-28, 5,-45);
  glVertex3f(-28, 5, 45);
  glEnd();

    glBegin(GL_POLYGON);
  glColor3f(.6,.6,.6);
  // glColor3f(1,1,1);
  glVertex3f( 28,15,-45);
  glVertex3f( 28,15, 45);
  glVertex3f( 28, 5, 45);
  glVertex3f( 28, 5,-45);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(.2,.2,.2);
  // glColor3f(1,1,1);
  glVertex3f( 28, 5, 45);
  glVertex3f(-28, 5, 45);
  glVertex3f(-28, 5,-45);
  glVertex3f( 28, 5,-45);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0,0,0);
  // glColor3f(1,1,1);
  glVertex3f(-28, .01, 45);
  glVertex3f( 28, .01, 45);
  glVertex3f( 28, .01,-45);
  glVertex3f(-28, .01,-45);
  glEnd();

  glPopMatrix();
}
void grid(int width, int depth, int front){
  int xwidth = width;
  int far    = depth;
  int near   = front;

  distance   = theta*3.1415*speed;
  gridOffset = (int)distance;
  offset     = (int)(gridOffset)-distance;
  glPushMatrix();

  glRotatef(180,0,1,0);
  glTranslatef(0,0,offset);
  
  GLfloat source[3][3]=
    {{.6,.1,.6},
     {.1,.0,.1},
     {.2,.2,.4}};

  GLfloat terrain[3][3]=
    {{.5,.6,.7},
     {.6,.7,.8},
     {.7,.8,.9}};
  GLfloat tile[4]={0};

  GLfloat colors[3][3]={0};

  for(int c = 0; c<3; c++){
    colors[c][0]=source[c][0]*10;
    colors[c][1]=source[c][1]*10;
    colors[c][2]=source[c][2]*10;
  }
   
  for(int i = 0; i< 2; i++){
    if(i==1){
      for(int c = 0; c<3; c++){
        colors[c][0]*=0.5;
        colors[c][1]*=0.5; 
        colors[c][2]*=0.5; 
      } 
      glLineWidth(2.0);
    }
    else glLineWidth(1.1);

    for(int q = -xwidth-1; q<=xwidth; q++)
	    for(int r = -near-1; r<=far; r++){
	    	tile[0]=terrain[(q+30)%3][(r+30+gridOffset)%3];
	    	tile[1]=terrain[(q+30)%3][(r+31+gridOffset)%3];
	    	tile[2]=terrain[(q+31)%3][(r+31+gridOffset)%3];
	    	tile[3]=terrain[(q+31)%3][(r+30+gridOffset)%3];

	    	if (q<2 && q>-2){
	    		tile[0]=.5;
	    		tile[1]=.5;
	    	}
	    	else if (q<3 && q>-3){
	    		tile[0]*=.5+0.25;
	    		tile[1]*=.5+0.25;
	    	}
	    	if (q<1 && q>-3){
	    		tile[2]=.5;
	    		tile[3]=.5;
	    	}
	    	else if (q<2 && q>-4){
	    		tile[2]*=.5+0.25;
	    		tile[3]*=.5+0.25;
	    	}
	     if(i==0){
   		 glBegin( GL_POLYGON);
	      glColor3f(colors[1][0]*tile[0]*0.25,
	      			colors[1][1]*tile[0]*0.25,
	      			colors[1][2]*tile[0]*0.25);
			 if (q<1 && q>-2)      
 				 glColor3f(.2,0,.2);
	        glVertex3f(q  ,2.0*tile[0]-2.02, r  );
	        glVertex3f(q  ,2.0*tile[1]-2.02, r+1);
	        glVertex3f(q+1,2.0*tile[2]-2.02, r+1);
	        glVertex3f(q+1,2.0*tile[3]-2.02, r  );
   		   glEnd();
   		 }
     	 glBegin( GL_LINES);
     	  glColor3f(colors[1][0]*tile[0],
	      			colors[1][1]*tile[0],
	      			colors[1][2]*tile[0]);
	        glVertex3f(q  ,2.0*tile[0]-2.0, r  );
	        glVertex3f(q  ,2.0*tile[1]-2.0, r+1);
	        glVertex3f(q  ,2.0*tile[0]-2.0, r  );
	        glVertex3f(q+1,2.0*tile[3]-2.0, r  );
     	 glEnd();
     	 
    }
  }
  // if(offset<-1.0){
	 //  gridOffset++;
  // }
  // gridOffset=-(int)offset;

  glPopMatrix();
}
void cube(){
  GLfloat source[3][3]=
    {{.4,.2,.2},
     {.2,.4,.2},
     {.2,.2,.4}};

  GLfloat colors[3][3]={0};

  for(int c = 0; c<3; c++){
    colors[c][0]=source[c][0];
    colors[c][1]=source[c][1];
    colors[c][2]=source[c][2];
  }
  for(int i = 0; i< 2; i++){
    if(i==1){
      for(int c = 0; c<3; c++){
        colors[c][0]*=0.5;
        colors[c][1]*=0.5; 
        colors[c][2]*=0.5; 
      } 
      glLineWidth(2.0);
    }
    else glLineWidth(1.1);

    glBegin( GL_LINES);
    for(int q = -10; q<=10; q++){
      glColor3fv ( colors[0]);
        glVertex3f( 10,  q, 10);
        glVertex3f( 10,  q,-10);
        glVertex3f( 10, 10,  q);
        glVertex3f( 10,-10,  q);

        glVertex3f(-10,  q, 10);
        glVertex3f(-10,  q,-10);
        glVertex3f(-10, 10,  q);
        glVertex3f(-10,-10,  q);

      glColor3fv ( colors[1]);
        glVertex3f(  q, 10, 10);
        glVertex3f(  q, 10,-10);
        glVertex3f( 10, 10,  q);
        glVertex3f(-10, 10,  q);

        glVertex3f(  q,-10, 10);
        glVertex3f(  q,-10,-10);
        glVertex3f( 10,-10,  q);
        glVertex3f(-10,-10,  q);

      glColor3fv ( colors[2]);
        glVertex3f(  q, 10, 10);
        glVertex3f(  q,-10, 10);
        glVertex3f( 10,  q, 10);
        glVertex3f(-10,  q, 10);

        glVertex3f(  q, 10,-10);
        glVertex3f(  q,-10,-10);
        glVertex3f( 10,  q,-10);
        glVertex3f(-10,  q,-10);
    }
    glEnd();
  }
}
void cube2(){
  glPushMatrix();
  glScalef(100,100,100);
  glColor3f(0,0,0.1);
  glBegin(GL_POLYGON);
    glVertex3f( 10, 10, 10);
    glVertex3f( 10, 10,-10);
    glVertex3f( 10,-10,-10);
    glVertex3f( 10,-10, 10);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex3f(-10, 10,-10);
    glVertex3f(-10, 10, 10);
    glVertex3f(-10,-10, 10);
    glVertex3f(-10,-10,-10);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex3f( 10, 10,-10);
    glVertex3f( 10, 10, 10);
    glVertex3f(-10, 10, 10);
    glVertex3f(-10, 10,-10);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex3f( 10,-10, 10);
    glVertex3f( 10,-10,-10);
    glVertex3f(-10,-10,-10);
    glVertex3f(-10,-10, 10);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex3f( 10,-10, 10);
    glVertex3f(-10,-10, 10);
    glVertex3f(-10, 10, 10);
    glVertex3f( 10, 10, 10);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex3f( 10,-10,-10);
    glVertex3f( 10, 10,-10);
    glVertex3f(-10, 10,-10);
    glVertex3f(-10,-10,-10);
  glEnd();
  glPopMatrix();
}
void mymotion() {
    // usleep(16667);
    theta +=1.0/60;
    // rot =sin(theta/PI*4)*0.5+0.5;
    rot = theta;
    if(rot>1){
      rot -= (int)rot;
    }

    glutPostRedisplay();
}
void resize(GLsizei w, GLsizei h){
    GLsizei ww,hh;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   
    GLfloat aspect = (GLfloat) w /(GLfloat) h;
    GLfloat fit = 1.5;

    if(w > h)
    {
        gluPerspective(60,aspect,0.01,2000);
    }
    else
    {
        gluPerspective(60/aspect,aspect,0.01,2000);
    }

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,w,h);
}
int main(int argc, char** argv){
    glutInit( &argc, argv );
    glutInitWindowSize(512,512);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH );
    glutCreateWindow("icosahedral worlds");
    glutDisplayFunc( display );
    glutIdleFunc( mymotion );
    glutReshapeFunc( resize );
    glutMainLoop();
    return 0;
}