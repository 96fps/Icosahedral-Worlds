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
double offset = 0;
double speed = 4.0;

//global primitives
  GLfloat isovert[12][3] = {0};
  int isoTriangle[20][3] = {0};

  GLfloat isoNetVert[22][3] = {0};
  int isoNetTriangle[20][3] = {0};

  GLfloat isoTubeVert[22][3] = {0};
  int isoTubeTriangle[20][3] = {0};

GLfloat xrot(GLfloat x, GLfloat y, GLfloat theta);
GLfloat yrot(GLfloat x, GLfloat y, GLfloat theta);

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

 	// glPushMatrix();
 //  	glScalef(.075,.075,.075);
 //     glRotatef(theta*180/3.14*speed,-1,0,0);
 //    cube();
	// glPopMatrix();
    cube2();

  //Main attraction:
    grid(10,10,10);
    // grid(10,15,7,4.0);
    // squishy();
	car();
	sun();
	gnd();
    // rollingsphere(3);
    // static_contact(1);
    // std_globe();
    // tube();
    // superdivIsaNet_ext(detail,0.0);

  //cleanup
    glPopMatrix();
    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void configcamera(){

    // glTranslatef(0,0,-3);
    // glTranslatef(0,0,-5);
    // glTranslatef(0,0,-8);
    glTranslatef(0,0.5,-10);
     // glRotatef(20,1,0,0);
     // glRotatef(10,1,0,0);
     glRotatef(1,1,0,0);
     // glRotatef(cos(theta)*180/PI,1,0,0);
     // glRotatef(45,1,0,0);

   wobble();
   // swivel1();
   // swivel3();
   // swivel4();
    // lowOrbit();  


   //   glRotatef(10,1,0,0);
   // swivel1();
}
void wobble(){
  // glRotatef(sin(theta*360/3.14/32)*1,1,0,0);
  glRotatef(cos(theta*360/3.14/47)*5,0,1,0);
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
  glTranslatef(0.5,-1,7+sin(theta));
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
void swivel4(){
     // glRotatef(15,1,0,0);
      glRotatef(-cos(theta-0.1)*35+35+10,1,0,0);
      glRotatef(theta*360/3.14/5,0,1,0);
      // glRotatef(cos(theta*3.14)*45,0,0,1);
}
void swivel3(){
     glRotatef(15,1,0,0);
      glRotatef(theta*360/3.14/3,1,0,0);
      glRotatef(theta*360/3.14/5,0,1,0);
      glRotatef(theta*360/3.14/7,0,0,1);
}
void swivel1(){
     glRotatef(2,1,0,0);
      glRotatef(theta*360/3.14/5,0,1,0);
}
void surfaceslide(){
  glRotatef(30,1,0,0);
  glTranslatef(0,-1.01,-0.0);
  glRotatef(-theta*360/3.14/3,0,1,0);
  glRotatef(-theta*360/3.14/3,1,0,0);
}
void lowOrbit(){
  glRotatef(30,1,0,0);
  glRotatef(-60,0,0,1);
  glTranslatef(0,-1.1,-0.0);
  glRotatef(-theta*360/3.14/3,0,1,0);
  glRotatef(-theta*360/3.14/3,1,0,0);
}
void squishy(){
  glPushMatrix();
    glEnable(GL_CULL_FACE);
    superdivIsa_ext(2,1*sin(theta*20)+0.5);
    // superdivIsa_ext(2,1.0);
  glPopMatrix();
}
void template2(){
  glPushMatrix();
    glRotatef(45,1,0,0);
      glRotatef(theta*50*3.0 ,1,0,0);
      glRotatef(theta*50*5.0 ,0,1,0);
      glRotatef(theta*50*7.0 ,0,0,1);
      glRotatef(theta*360/3.0 ,1,0,0);
      glRotatef(theta*360/5.0 ,0,1,0);
      glRotatef(theta*360/7.0 ,0,0,1);
    glEnable(GL_CULL_FACE);
    superdivIsa_ext(detail,1.0);
  glPopMatrix();
}
void rollingball(double radius){
  glPushMatrix();
    // glTranslatef(0,sin(theta*5)*.4-0.35,0);
    // glTranslatef(0,sin(theta*6)*2-0.35+1,0);
    glTranslatef(0,-1+radius,0);
  	glRotatef(theta*180*speed/radius,1,0,0);

    glScalef(radius,radius,radius);
    template();
    // template2();
  glPopMatrix();
}
void template(){
  glPushMatrix();
    glEnable(GL_CULL_FACE);
    superdivIsa_ext(detail,1.0);
  glPopMatrix();
}
void std_globe(){
  glPushMatrix();
    glEnable(GL_CULL_FACE);
    glRotatef(-90,0,1,0);
    glRotatef(rot*360,0,1,0);
    superdivIsa_ext(detail,1.0);
  glPopMatrix();
}
void tube(){
  glPushMatrix();
    glDisable(GL_CULL_FACE);
    glTranslatef(0,sqrt(3)*.25,0);
    // glRotatef(-90,0,1,0);
    glRotatef(rot*360,0,1,0);
    superdivIsaTube(detail,1.0);
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}
void grid(int width, int depth, int front){

    int xwidth = width;
    int far = depth;
    int near = front;

  double offset=-theta*3.1415*speed+(int)(gridOffset);

  glPushMatrix();

     glRotatef(180,0,1,0);
  glTranslatef(0,0,offset);
  // glScalef(scale,scale,scale);
  
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
  if(-offset>1.0){
	  gridOffset++;
  }
  glPopMatrix();
}
void rollingsphere(int copies){
  glPushMatrix();
    glRotatef(90,1,0,0);
    glPushMatrix();
      glEnable(GL_CULL_FACE);
      glRotatef(-90,0,1,0);
      glRotatef(rot*360,0,1,0);
      superdivIsa_ext(detail,1.0);
    glPopMatrix();
    glPushMatrix();
      glDisable(GL_CULL_FACE);
      glTranslatef(0,0,1);
      glScalef(scalefactor*.2,scalefactor*.2,scalefactor*.2);
      glTranslatef(rot*5-2.5,sqrt(3)*.25,0);
      glTranslatef(-2.5*copies,0,0);
      for(int i=0; i<copies; i++){
        superdivIsaNet_ext(detail,0.0);
        glTranslatef(5,0,0);
      }
    glPopMatrix();
  glPopMatrix();
  glEnable(GL_CULL_FACE);
  glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex3f( 10.1, 10, 10);
    glVertex3f( 10.1, 10,-10);
    glVertex3f( 10.1,-10,-10);
    glVertex3f( 10.1,-10, 10);
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex3f(-10.1, 10,-10);
    glVertex3f(-10.1, 10, 10);
    glVertex3f(-10.1,-10, 10);
    glVertex3f(-10.1,-10,-10);
  glEnd();
}
void static_contact(int copies){
  glPushMatrix();
    glPushMatrix();
      glDisable(GL_CULL_FACE);
      glTranslatef(0,0,1);
      // glTranslatef(0,0,-.1);
      glScalef(scalefactor*.2,scalefactor*.2,scalefactor*.2);
      glTranslatef(rot*5-2.5,sqrt(3)*.25,0);
      glTranslatef(-2.5*copies,0,0);
      for(int i=0; i<copies; i++){
        superdivIsaNet_ext(detail,0.0);
        glTranslatef(5,0,0);
      }
    glPopMatrix();
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}
void Triangle(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color){
  glBegin(GL_POLYGON);
    glColor3f (color[0], color[1], color[2]);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
  glEnd();
}
void TriangleTricolor(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* colorset){
  glBegin(GL_POLYGON);
    glColor3f (colorset[0], colorset[1], colorset[2]);
    glVertex3fv(a);
    glColor3f (colorset[3], colorset[4], colorset[5]);
    glVertex3fv(b);
    glColor3f (colorset[6], colorset[7], colorset[8]);
    glVertex3fv(c);
  glEnd();
}
void subDivTri2(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m, double inflate) {
  GLfloat v[3][3];
  int j;
  int i;

  if (m>0)
  {
    for(j=0;j<3;j++){
      v[0][j]=(a[j]+b[j])/2;
      v[1][j]=(a[j]+c[j])/2;
      v[2][j]=(b[j]+c[j])/2;
    }
    for(j=0;j<3;j++)
    {
      GLfloat magnitude = 
      sqrt(v[j][0]*v[j][0]
          +v[j][1]*v[j][1]
          +v[j][2]*v[j][2]);

      if(inflate!=0.0){
        double vcopy;
        for(i=0;i<3;i++){
          vcopy = v[j][i];
          v[j][i] = vcopy/magnitude;
          v[j][i] *= inflate;
          v[j][i] += (1-inflate)*vcopy;
        }
      }
    }

    GLfloat color1[3]={0};
      
      color1[0]=color[0]*.9+0.1;
      color1[1]=color[1]*.9;
      color1[2]=color[2]*.9;
    
    GLfloat color2[3]={0};
      
      color2[0]=color[0]*.9;
      color2[1]=color[1]*.9;
      color2[2]=color[2]*.9+0.1;
  
    GLfloat color3[3]={0};
      
      color3[0]=color[0]*.9+0.1;
      color3[1]=color[1]*.9;
      color3[2]=color[2]*.9;

    subDivTri2(a,v[0],v[1],color1,m-1,inflate);
    subDivTri2(v[0],b,v[2],color2,m-1,inflate);
    subDivTri2(v[1],v[2],c,color3,m-1,inflate);
    subDivTri2(v[2],v[1],v[0],color,m-1,inflate);
  }
  else Triangle(a,b,c,color);
}
void superDivTri2(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m, double inflate) {
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

    for(j=0;j<7;j++)
    {
      GLfloat magnitude = 
      sqrt(v[j][0]*v[j][0]
          +v[j][1]*v[j][1]
          +v[j][2]*v[j][2]);
      if(inflate!=0.0){
        double vcopy;
        for(i=0;i<3;i++){
          vcopy = v[j][i];
          v[j][i] = vcopy/magnitude;
          v[j][i] *= inflate;
          v[j][i] += (1-inflate)*vcopy;
        }
      }
    }

    GLfloat color0[3]={0};
      
      color0[0]=1-color[1]*0.5-color[2]*0.5;
      color0[1]=1-color[0]*0.5-color[2]*0.5;
      color0[2]=1-color[0]*0.5-color[1]*0.5;
    
    GLfloat color1[3]={0};
      
      color1[0]=color[0]*.9+0.1;
      color1[1]=color[1]*.9;
      color1[2]=color[2]*.9;
    
    GLfloat color2[3]={0};
      
      color2[0]=color[0]*.9;
      color2[1]=color[1]*.9;
      color2[2]=color[2]*.9+0.1;
  
    GLfloat color3[3]={0};
      
      color3[0]=color[0]*.9+0.1;
      color3[1]=color[1]*.9;
      color3[2]=color[2]*.9;
  
    superDivTri2(a,v[1],v[2],color0,m-1,inflate);
    superDivTri2(v[3],b,v[4],color0,m-1,inflate);
    superDivTri2(v[5],v[6],c,color0,m-1,inflate);

    superDivTri2(v[0],v[2],v[1],color1,m-1,inflate);
    superDivTri2(v[4],v[0],v[3],color2,m-1,inflate);
    superDivTri2(v[6],v[5],v[0],color3,m-1,inflate);

    superDivTri2(v[0],v[4],v[6],color1,m-1,inflate);
    superDivTri2(v[2],v[0],v[5],color2,m-1,inflate);
    superDivTri2(v[1],v[3],v[0],color3,m-1,inflate);
  }
  else {
    // GLfloat colorset[9]={0};

    // double amt=0.1;
      
    //   colorset[0]=color[0]*(1-amt)+amt;
    //   colorset[1]=color[1]*(1-amt);
    //   colorset[2]=color[2]*(1-amt);

    //   colorset[3]=color[0]*(1-amt);
    //   colorset[4]=color[1]*(1-amt)+amt;
    //   colorset[5]=color[2]*(1-amt);

    //   colorset[6]=color[0]*(1-amt);
    //   colorset[7]=color[1]*(1-amt);
    //   colorset[8]=color[2]*(1-amt)+amt;
    // TriangleTricolor(a,b,c,colorset);
    Triangle(a,b,c,color);
  }
}
void superDivTri3(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* color, int m, double inflate) {
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
          +v[j][2]*v[j][2]);
      if(inflate!=0.0){
        double vcopy;
        for(i=0;i<3;i++){
          vcopy = v[j][i];
          v[j][i] = vcopy/magnitude;
          v[j][i] *= inflate;
          v[j][i] += (1-inflate)*vcopy;
          if(i==1) v[j][i]=vcopy;
        }
      }
    }

    GLfloat color0[3]={0};
      
      color0[0]=1-color[1]*0.5-color[2]*0.5;
      color0[1]=1-color[0]*0.5-color[2]*0.5;
      color0[2]=1-color[0]*0.5-color[1]*0.5;
    
    GLfloat color1[3]={0};
      
      color1[0]=color[0]*.9+0.1;
      color1[1]=color[1]*.9;
      color1[2]=color[2]*.9;
    
    GLfloat color2[3]={0};
      
      color2[0]=color[0]*.9;
      color2[1]=color[1]*.9;
      color2[2]=color[2]*.9+0.1;
  
    GLfloat color3[3]={0};
      
      color3[0]=color[0]*.9+0.1;
      color3[1]=color[1]*.9;
      color3[2]=color[2]*.9;
  
    superDivTri3(a,v[1],v[2],color0,m-1,inflate);
    superDivTri3(v[3],b,v[4],color0,m-1,inflate);
    superDivTri3(v[5],v[6],c,color0,m-1,inflate);

    superDivTri3(v[0],v[2],v[1],color1,m-1,inflate);
    superDivTri3(v[4],v[0],v[3],color2,m-1,inflate);
    superDivTri3(v[6],v[5],v[0],color3,m-1,inflate);

    superDivTri3(v[0],v[4],v[6],color1,m-1,inflate);
    superDivTri3(v[2],v[0],v[5],color2,m-1,inflate);
    superDivTri3(v[1],v[3],v[0],color3,m-1,inflate);
  }
  else {
    // GLfloat colorset[9]={0};

    // double amt=0.1;
      
    //   colorset[0]=color[0]*(1-amt)+amt;
    //   colorset[1]=color[1]*(1-amt);
    //   colorset[2]=color[2]*(1-amt);

    //   colorset[3]=color[0]*(1-amt);
    //   colorset[4]=color[1]*(1-amt)+amt;
    //   colorset[5]=color[2]*(1-amt);

    //   colorset[6]=color[0]*(1-amt);
    //   colorset[7]=color[1]*(1-amt);
    //   colorset[8]=color[2]*(1-amt)+amt;
    // TriangleTricolor(a,b,c,colorset);
    Triangle(a,b,c,color);
  }
}
void superdivIsa_ext(int m, double inflate){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};

    color[0]= 1-(i/2)*.1;
    color[1]=(i/2)*.1;
    color[2]=  0;

    superDivTri2(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color, m, inflate);
  }
}
void subdivIsa_ext(int m, double inflate){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};

    color[0]= 1-(i/2)*.1;
    color[1]=(i/2)*.1;
    color[2]=  0;

    subDivTri2(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color, m, inflate);
  }
}
void superdivIsaNet_ext(int m, double inflate){

  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};

    color[0]= 1-(i/2)*.1;
    color[1]=(i/2)*.1;
    color[2]=  0;
    
    superDivTri2(isoNetVert[isoNetTriangle[i][0]],
             isoNetVert[isoNetTriangle[i][1]],
             isoNetVert[isoNetTriangle[i][2]],
             color, m,inflate);
   
  }
}
void superdivIsaTube(int m, double inflate){
  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};

    color[0]= 1-(i/2)*.1;
    color[1]=(i/2)*.1;
    color[2]=  0;
    
    superDivTri3(isoTubeVert[isoTubeTriangle[i][0]],
             isoTubeVert[isoTubeTriangle[i][1]],
             isoTubeVert[isoTubeTriangle[i][2]],
             color, m,inflate);
  }
}
void solidIsa2(){
  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};
    color[0]=(i/4)*.2;
    color[1]= 1-(i/4)*.2;
    color[2]=  0;
    
    Triangle(isovert[isoTriangle[i][0]],
             isovert[isoTriangle[i][1]],
             isovert[isoTriangle[i][2]],
             color);
  }
}
void solidIsaNet2(){
  for(int i = 0; i<20; i ++)
  {
    GLfloat color[3]={0};
    color[0]=(i/4)*.2;
    color[1]= 1-(i/4)*.2;
    color[2]=  0;

    Triangle(isoNetVert[isoNetTriangle[i][0]],
             isoNetVert[isoNetTriangle[i][1]],
             isoNetVert[isoNetTriangle[i][2]],
             color);
  }
}
void generatePrimitives(){
  genIcosahedron();
  genIcosahedronNet();
  genIcosahedronTube();
}
void genIcosahedron(){
    isoVerts();
    isoTri();
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
void isoTri(){
  int i; //strip of triangles
  int j; //row of the triangle
  int k;
  for(i = 0; i<5; i++){     
    j=0;
    k=4-i;

    isoTriangle[i*4+j][0]=(k+1)%5+1;
    isoTriangle[i*4+j][1]=k%5+1;
    isoTriangle[i*4+j][2]=0;
    
    j++;
    isoTriangle[i*4+j][1]=(k+1)%5+1;
    isoTriangle[i*4+j][0]=k%5+1;
    isoTriangle[i*4+j][2]=(k+3)%5+6;
   
    j++;
    isoTriangle[i*4+j][1]=(k+2)%5+6;
    isoTriangle[i*4+j][0]=(k+3)%5+6;
    isoTriangle[i*4+j][2]=k%5+1;
   
    j++;
    isoTriangle[i*4+j][0]=(k+2)%5+6;
    isoTriangle[i*4+j][1]=(k+3)%5+6;
    isoTriangle[i*4+j][2]=11;
  }
}
void genIcosahedronNet(){
    isoNetVerts();
    isoNetTri();
}
void isoNetVerts(){
  int i;
  double h = sqrt(3)*0.5;

  for(i=0; i<5; i++){
    isoNetVert[i][0]=i+0.5;
    isoNetVert[i][1]=h;
  }
  for(i=5; i<11; i++){
    isoNetVert[i][0]=(i-5);
  }
  for(i=11; i<17; i++){
    isoNetVert[i][0]=(i-11)+0.5;
    isoNetVert[i][1]=-h;
  }
  for(i=17; i<22; i++){
    isoNetVert[i][0]=(i-17)+1;
    isoNetVert[i][1]=-2*h;
  }
}
void isoNetTri(){
  int j;
  for(int i = 0; i<5; i++){
    j = i*4;
    isoNetTriangle[j][0]=5+i;
    isoNetTriangle[j][1]=6+i;
    isoNetTriangle[j][2]=0+i;

    j++;
    isoNetTriangle[j][0]=6+i;
    isoNetTriangle[j][1]=5+i;
    isoNetTriangle[j][2]=11+i;
    
    j++;
    isoNetTriangle[j][0]=11+i;
    isoNetTriangle[j][1]=12+i;
    isoNetTriangle[j][2]=6+i;

    j++;
    isoNetTriangle[j][0]=12+i;
    isoNetTriangle[j][1]=11+i;
    isoNetTriangle[j][2]=17+i;
  }
}
void genIcosahedronTube(){
    isoTubeVerts();
    isoTubeTri();
}
void isoTubeVerts(){
  int i;
  double h = sqrt(3)*0.5;
  double angle=0;

  for(i=0; i<22; i++){
    angle=(isoNetVert[i][0]*.2)*scalefactor;
    
    isoTubeVert[i][0]=yrot(1.0, 0, angle);
    isoTubeVert[i][1]=isoNetVert[i][1]*.2*scalefactor;
    isoTubeVert[i][2]=xrot(1.0, 0, angle);
  }
}
void isoTubeTri(){
  int j;
  for(int i = 0; i<5; i++){
    j = i*4;
    isoTubeTriangle[j][0]=5+i;
    isoTubeTriangle[j][1]=6+i;
    isoTubeTriangle[j][2]=0+i;

    j++;
    isoTubeTriangle[j][0]=6+i;
    isoTubeTriangle[j][1]=5+i;
    isoTubeTriangle[j][2]=11+i;
    
    j++;
    isoTubeTriangle[j][0]=11+i;
    isoTubeTriangle[j][1]=12+i;
    isoTubeTriangle[j][2]=6+i;

    j++;
    isoTubeTriangle[j][0]=12+i;
    isoTubeTriangle[j][1]=11+i;
    isoTubeTriangle[j][2]=17+i;    
  }
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
    theta +=0.005;
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
    generatePrimitives();
    glutMainLoop();
    return 0;
}
GLfloat xrot(GLfloat x, GLfloat y, GLfloat theta){
    GLfloat xnew = cos(theta)*x - sin(theta)*y;
    return xnew;
}
GLfloat yrot(GLfloat x, GLfloat y, GLfloat theta){
    GLfloat ynew = sin(theta)*x + cos(theta)*y;
    return ynew;
}
