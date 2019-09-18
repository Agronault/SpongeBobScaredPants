#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#include "global.h"
#include "load.h"

void colisaoMouse(struct coordenadas alvo);

void testeColisao() {

  colisaoMouse(iniciar);
  colisaoMouse(instrucoes);
  colisaoMouse(sair);
  colisaoMouse(voltar);

}

void colisao(struct coordenadas alvo) {

  if (((alvo.y + alvo.altura) > (p.y) && (alvo.y + alvo.altura) < (p.y + p.altura) &&
      (alvo.x - alvo.largura) < (p.x + p.largura) && (alvo.x - alvo.largura) > (p.x - p.largura)) ||
    ((alvo.y + alvo.altura) > (p.y + p.altura) && (alvo.y) < (p.y + p.altura) &&
      (alvo.x - alvo.largura) < (p.x + p.largura) && (alvo.x - alvo.largura) > (p.x - p.largura)) ||
    ((alvo.y + alvo.altura) > (p.y) && (alvo.y + alvo.altura) < (p.y + p.altura) &&
      (alvo.x + alvo.largura) < (p.x + p.largura) && (alvo.x + alvo.largura) > (p.x - p.largura)) ||
    ((alvo.y + alvo.altura) > (p.y + p.altura) && (alvo.y) < (p.y + p.altura) &&
      (alvo.x + alvo.largura) < (p.x + p.largura) && (alvo.x + alvo.largura) > (p.x - p.largura)
    )) {

    if (alvo.x == iniciar.x && alvo.y == iniciar.y) {
      //exit(0);
      printf("___________________________________\n");

    }

  }

}



void colisaoMouse(struct coordenadas alvo) {

  if (p.x > (alvo.x - alvo.largura) &&
    p.x < (alvo.x + alvo.largura) &&
    p.y > (alvo.y) &&
    p.y < (alvo.y + alvo.altura)
  ) {

    if(tela == MENU){
      if(alvo.x == instrucoes.x && alvo.y == instrucoes.y){
        telaInstrucoes = 1;
      }else if(alvo.x == voltar.x && alvo.y == voltar.y){
        telaInstrucoes = 0;
      } else if(alvo.x == sair.x && alvo.y == sair.y && telaInstrucoes==0){
        exit(0);
      }else if(alvo.x == iniciar.x && alvo.y == iniciar.y && telaInstrucoes==0){
        glutSetCursor(GLUT_CURSOR_NONE);
        desenha_load();
        tela = JOGO;
        glutReshapeWindow(larguraJanela,alturaJanela);
      }
    }

  }

}
