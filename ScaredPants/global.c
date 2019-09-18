#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "global.h"

enum tela tela = JOGO;

float xMouse = 250; //?
float yMouse = 250;
float larguraJanela = 1280; //resolução inicial
float alturaJanela = 720;

float buffer[5]={0};
float enviar[5]={0};
int j = 0;

GLfloat lPos[4]={0.00, 0.00, 0.00, 1.00 };
GLfloat lKa[4]={0.00, 0.5, 0.00, 1.00};
GLfloat lKd[4]={0.5, 0.5, 0.5, 1.00};
GLfloat lKs[4]={1.00, 1.00, 1.00, 1.00};
GLfloat mKd[4]={0,0,0,1};
GLfloat mKs[4]={0,0,0,1};
GLfloat mKe[4]={0,0,0,1};

GLfloat lKa1[4]={1.0, 1.0, 1.0, 1.00};       //cor ambiente (basta mudar as 3 para escolher a cor da luz)
GLfloat lKd1[4]={1.0, 1.0, 1.0, 1.00};       //cor difusa
GLfloat lKs1[4]={1.00, 1.00, 1.00, 1.00};    //cor especular

GLfloat lPos1[4]={7.00, -31.2, -45.9, 1.00 };
GLfloat lPos2[4]={7.00, -31.2, -70.7, 1.00 };
GLfloat lPos3[4]={7.00, -31.2, -96.6, 1.00 };
GLfloat lPos4[4]={-16.7, -31.2, -16.8, 1.00 };
GLfloat lPos5[4]={-133.3, -31.2, 37.2, 1.00 };

float matAmbAndDif[4] = {1.0, 1.0, 1.0, 1.0};    //vetor cor ambiente e difusa: branca
float matShine[] = {5};                       // expoente especular (shininess)
int light = 0;
double rotate =0;

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
int sock = 0;
struct sockaddr_in serv_addr;
int choose=0;



int modoCAM=1;


int telaInstrucoes = 0;

void HitBox(int x, int y, int altura, int largura){
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);  glVertex3f(-largura+x, y, 0);
        glTexCoord2f(1, 0);  glVertex3f(largura+x, y, 0);
        glTexCoord2f(1, 1);  glVertex3f(largura+x, altura+y, 0);
        glTexCoord2f(0, 1);  glVertex3f(-largura+x, altura+y, 0);
    glEnd();
}

void HitBoxParticula(double x, double y, double z, double altura, double largura){
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);  glVertex3f(-largura+x, y, z);
        glTexCoord2f(1, 0);  glVertex3f(largura+x, y, z);
        glTexCoord2f(1, 1);  glVertex3f(largura+x, altura+y, z);
        glTexCoord2f(0, 1);  glVertex3f(-largura+x, altura+y, z);
    glEnd();
}



void escreveTexto(void * font, char *s, float x, float y, float z) {
    int j;
    glRasterPos3f(x, y, z);

    for (j = 0; j < strlen(s); j++) {
        glutBitmapCharacter(font, s[j]);
    }
}
