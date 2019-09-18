#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>

#include "desenhaCena.h"
#include "load.h"
#include "global.h"

void frame(int time){

    glutPostRedisplay();

    glutTimerFunc(time, frame, 10);
}

void desenhaCena(){

  enviar[0]= foco.x;
  enviar[1]= foco.y;
  enviar[2]= foco.z;
  

  switch(choose){
    case(1):
        valread = read( new_socket , buffer, 5*sizeof(float));
        printf("%f\n",buffer[2] );
        send(new_socket , enviar , 5*sizeof(float) , 0 );
        printf("float enviado\n");
        break;
    case(2):
        send(sock , enviar , 5*sizeof(float) , 0 );
        printf("float enviado\n");
        valread = read( sock , buffer, 5*sizeof(float));
        printf("%f\n",buffer[2] );
        break;
    default:
    break;
  }




    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

    switch(tela){
        case(MENU):
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT_MODEL_AMBIENT);
            if(telaInstrucoes==0){
                desenhaMenu();
            }else{
                desenhaInstrucoes();
            }
            break;
        case(JOGO):
            desenhaGame();
            break;
        default:
           break;
    }

    printf("alvo.z: %f\nalvo.x: %f\nalvo.y: %f\n\n", foco.z, foco.x, foco.y);
    glutSwapBuffers();  //glFlush com buffers
}

void desenhaGame(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float m = 0.2;  //intensidade da luz global
    float globAmb[] = { m, m, m, 1.0 };
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    float colorFog[4] = {0.41, 0.89, 0.96, 1};  //azul agua skysphere
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP2);    //GL_EXP, GL_EXP2 e GL_LINEAR
    //glFogf(GL_FOG_START, 100);    //onde começa e termina o fog para GL_LINEAR(-3.00 ate 3.00)
    //glFogf(GL_FOG_END, 110);
    glFogf(GL_FOG_DENSITY, 0.011);   //densidade do fog, 0.00 á 3.00
    glFogfv(GL_FOG_COLOR, colorFog);


    camera.x = 10*sin(phi)*cos(teta);
    camera.z = 10*sin(phi)*sin(teta);
    camera.y = 10*cos(phi);

//    gluLookAt(camera.x, camera.y, camera.z, foco.x, foco.y, foco.z, up.x, up.y, up.z);



    if (light==1) {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
        glEnable(GL_LIGHT5);
        glEnable(GL_LIGHT6);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT_MODEL_AMBIENT);


        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
        glLightfv(GL_LIGHT0, GL_POSITION, lPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lKa);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lKd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lKs);

        glPushMatrix();
        glTranslatef(-foco.x, -foco.y, -foco.z);

        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
        glLightfv(GL_LIGHT1, GL_POSITION, lPos1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, lKa1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lKd1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lKs1);

        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);
        glLightfv(GL_LIGHT2, GL_POSITION, lPos2);
        glLightfv(GL_LIGHT2, GL_AMBIENT, lKa1);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, lKd1);
        glLightfv(GL_LIGHT2, GL_SPECULAR, lKs1);

        glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.5);
        glLightfv(GL_LIGHT3, GL_POSITION, lPos3);
        glLightfv(GL_LIGHT3, GL_AMBIENT, lKa1);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, lKd1);
        glLightfv(GL_LIGHT3, GL_SPECULAR, lKs1);

        glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.5);
        glLightfv(GL_LIGHT4, GL_POSITION, lPos4);
        glLightfv(GL_LIGHT4, GL_AMBIENT, lKa1);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, lKd1);
        glLightfv(GL_LIGHT4, GL_SPECULAR, lKs1);

        glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.5);
        glLightfv(GL_LIGHT5, GL_POSITION, lPos5);
        glLightfv(GL_LIGHT5, GL_AMBIENT, lKa1);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, lKd1);
        glLightfv(GL_LIGHT5, GL_SPECULAR, lKs1);

        glPopMatrix();

    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
        glDisable(GL_LIGHT6);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT_MODEL_AMBIENT);
    }

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

//   gluLookAt(camera.x+ foco.x, camera.y+ foco.y, camera.z+ foco.z, 0, 0, 0, up.x, up.y, up.z);

glLoadIdentity();

    switch(modoCAM){
        case 1:
            gluLookAt( camera.x, camera.y, camera.z, 0, 0, 0, up.x, up.y, up.z);
            break;
        case 2:
            gluLookAt( 0, 0, 0, camera.x, camera.y, camera.z, up.x, up.y, up.z);
            break;
        case 3:
            gluLookAt( camera.x, camera.y, camera.z, 0, 0, 0, up.x, up.y, up.z);
            break;
        default:
            gluLookAt( camera.x, camera.y, camera.z, 0, 0, 0, up.x, up.y, up.z);
            break;
    }
  glPushMatrix();
    
    if(j==1){
        drawEstrelas(10);
    }

   glRotatef(rotate, 0, 1, 0);


    if(modoCAM!=2){
        drawmodelZep();
    }



   glRotatef(-rotate, 0, 1, 0);

    glTranslatef(-foco.x, -foco.y, -foco.z);

    glPushMatrix();

      glTranslatef(buffer[0], buffer[1], buffer[2]);
      drawmodelZep2();
    glPopMatrix();


    glScalef(150, 150, 150);

    switch(city){
    case 1:
        drawmodelCity();

        break;
    case 2:
        drawmodelCity2();

        break;
    default:
        drawmodelCity();

        break;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -foco.y-25, 0);
    glScalef(100, 100, 100);
    drawmodelSky();

    glPopMatrix();
}

void desenhaMenu(){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu_Fundo);
    HitBox( larguraJanela/2, 0, alturaJanela, larguraJanela/2);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu_Iniciar);
    HitBox(iniciar.x, iniciar.y, iniciar.altura, iniciar.largura);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu_Instrucoes);
    HitBox(instrucoes.x, instrucoes.y, instrucoes.altura, instrucoes.largura);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu_Sair);
    HitBox(sair.x, sair.y, sair.altura, sair.largura);
    glDisable(GL_TEXTURE_2D);


    //so pra escrever os botoes, pode excluir depois dos sprites
    glColor3f(1, 0, 0);
    sprintf(texto, "Iniciar");
    escreveTexto(GLUT_BITMAP_HELVETICA_18, texto, iniciar.x, iniciar.y+(iniciar.altura/2), 0);

    sprintf(texto, "Instrucoes");
    escreveTexto(GLUT_BITMAP_HELVETICA_18, texto, instrucoes.x, instrucoes.y+(instrucoes.altura/2), 0);

    sprintf(texto, "Sair");
    escreveTexto(GLUT_BITMAP_HELVETICA_18, texto, sair.x, sair.y+(sair.altura/2), 0);

}

void desenhaInstrucoes(){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu_telaInstrucoes);
    HitBox( larguraJanela/2, 0, alturaJanela, larguraJanela/2);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu_Voltar);
    HitBox(voltar.x, voltar.y, voltar.altura, voltar.largura);
    glDisable(GL_TEXTURE_2D);


    //so pra escrever os botoes, pode excluir depois dos sprites
    glColor3f(1, 0, 0);
    sprintf(texto, "Voltar");
    escreveTexto(GLUT_BITMAP_HELVETICA_18, texto, voltar.x, voltar.y+(voltar.altura/2), 0);

}
