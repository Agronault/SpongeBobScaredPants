#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "teclado.h"
#include "global.h"


void teclado(unsigned char key, int x, int y) {

    //printf("%c em %i %i", key, x, y);
    switch (key) {
        case 27:
            //system("clear");
            if(tela==JOGO){
              tela=MENU;
              glutSetCursor(GLUT_CURSOR_INHERIT);
              glColor3f(1,0,0);
            glutReshapeWindow(larguraJanela, alturaJanela);

          }
            else{
              if(tela==MENU){
              exit(0);
              }
          }

            break;
        case ' ':
            break;
        case 'W':
        case 'w':
            if(foco.z<101.2)
            foco.z = foco.z + 0.2;
            rotate=0;
            break;
        case 'S':
        case 's':
            if(foco.z>-101.2)
            foco.z = foco.z - 0.2;
            rotate= 180;
            break;
        case 'A':
        case 'a':
            if(foco.x<149.6)
            foco.x = foco.x + 0.2;
            rotate= 90;
            break;
        case 'D':
        case 'd':
            if(foco.x>-149.4)
            foco.x = foco.x - 0.2;
            rotate= -90;
            break;
        case 'Q':
        case 'q':
            if(foco.y<39.0) foco.y = foco.y + 0.2;
            break;
        case 'E':
        case 'e':
            if(foco.y> -35.4) foco.y = foco.y - 0.2;
            break;
        case 'L':
        case 'l':
            if(light==0){
                light=1;
            } else{
                light=0;
            }
            break;
        case 'J':
        case 'j':
            if(j==0){
                j=1;
            }else{
                j=0;
            }
            break;
        case 'C':
        case 'c':
            foco.x=0; foco.y=0; foco.z=0;
            city++;
            if(city>2){city=1;}
            break;

//modos da câmera
        case '1':
          modoCAM=1;
          break;
        case '2':
          modoCAM=2;
          break;
        case '3':
          modoCAM=3;
        case '4':
          modoCAM=4;

        default:
            break;
        }
}

void specialInput(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP:
            phi= phi + 0.01;
            break;
        case GLUT_KEY_DOWN:
            phi= phi - 0.01;
            break;
        case GLUT_KEY_LEFT:
            teta= teta + 0.01;
            break;
        case GLUT_KEY_RIGHT:
            teta= teta - 0.01;
            break;
        default:
            break;
    }

if(phi==0) phi= 0.01;

}


void keyUp(unsigned char key, int x, int y) {
    switch (key) {
        case ' ':
            break;
    }
}
