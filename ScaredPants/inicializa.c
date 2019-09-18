#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "inicializa.h"
#include "load.h"
#include "global.h"
#include "desenhaCena.h"
#include "musica.h"

void define(){
  phi=0;
  teta=0;

  city=1;

  p.x = 0;
  p.y = 0;
  p.altura = 10;
  p.largura = 10;

  iniciar.x = 650;
  iniciar.y = 320;
  iniciar.altura = 100;
  iniciar.largura = 150;

  instrucoes.x = 650;
  instrucoes.y = 200;
  instrucoes.altura = 100;
  instrucoes.largura = 150;

  sair.x = 650;
  sair.y = 80;
  sair.altura = 100;
  sair.largura = 150;

  voltar.x = 70;
  voltar.y = 600;
  voltar.altura = 100;
  voltar.largura = 50;

  foco.x= 0;
  foco.y= 0;
  foco.z= 0;

  camera.x=0;
  camera.y=0;
  camera.z=0;

  up.x=0;
  up.y=1;
  up.z=0;

}

void inicializa(){

    //glutFullScreen();

    tocar_musica("./../source/musica/menu.ogg", -1);


    glClearColor( 1, 1, 1, 1);

    define();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tela = MENU;
    MENU_load();



    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    //glLightfv(GL_LIGHT0, GL_POSITION, lPos);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, lKa);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, lKd);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, lKs);

 //    glutSetCursor(GLUT_CURSOR_NONE);    //esconde o ponteiro do mouse dentro da janela
 //    glutSetCursor(GLUT_CURSOR_INHERIT); //utiliza o cursor pai (volta o cursor ao normal)
}

void inicializa3d(){

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mKd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mKs);
    glMaterialfv(GL_FRONT, GL_EMISSION, mKe);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //?, algo referente a iluminacao
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //em textura



}


void redimensiona(int w, int h){
    larguraJanela = w;
    alturaJanela = h;

    switch(tela){
        case MENU:
            parar_musica();
            glDisable(GL_DEPTH_TEST);
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, w, 0, h, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            tocar_musica("./../source/musica/menu.ogg", -1);
            break;
        case JOGO:
            parar_musica();
            glEnable(GL_DEPTH_TEST);                // Ativa o Z buffer
            glViewport (0, 0, w, h);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, (float)w/(float)h, 0.2, 350.0);     //colocar fovy entre 45.0 e 60.0

            glMatrixMode(GL_MODELVIEW);     //muda para matriz de modelo e visão
            inicializa3d();
            tocar_musica("./../source/musica/game.ogg", -1);
            break;
        default:
            break;
    }

}
