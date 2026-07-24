#ifndef PLANETS_H
#define PLANETS_H


//usleep
void usleep(int miliseconds);

void display();
void sphere(double col[3]);
void planet(int i);
void moon(int parent, int index);
void planetarySys(double param[4],int index);
void moonSys(double dist, double radius, int parent, int index);
void sun();
void ring(double dist,double size);
void ring2(double dist,double size);
void solarSystem();
void configcamera();
void wobble();
void swivel1(double speed);
void lowOrbit();
void swivel2();
void cube();
void mymotion() ;
void resize(GLsizei w, GLsizei h);
int main(int argc, char** argv);

#endif