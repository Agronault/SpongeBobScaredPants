#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>

#include "detectaMouse.h"
#include "global.h"
#include "colisao.h"


void mouse(int botao, int estado, int x, int y){
  p.x=x;
  p.y=(alturaJanela)-y;

  printf("y : %i \n", y);
  printf("x: %f\n", p.x);
  printf("py: %f \n \n", p.y );

  if(botao==0){
    testeColisao();
  }

}

void posicionaCamera(int x, int y){
  double xChange; double yChange;

  xChange= x- xMouse;
  yChange= y- yMouse;

teta= (teta+ xChange/150);


phi= (phi- yChange/150);

  xMouse = x;
  yMouse = y;


  glutPostRedisplay();
}
