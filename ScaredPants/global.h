#ifndef GLOBAL_H
#define GLOBAL_H

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

enum tela{MENU, JOGO} tela;

struct coordenadas {
    double x, y, z, altura, largura;
};

struct coordenadas p;   //mouse
struct coordenadas iniciar;
struct coordenadas instrucoes;
struct coordenadas sair;
struct coordenadas voltar;

struct coordenadas foco;
struct coordenadas camera;
struct coordenadas up;

int j; //ativa e desativa particula

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt;
int addrlen;
int sock;
struct sockaddr_in serv_addr;
int choose;

int modoCAM;

char texto[40];

double phi;
double teta;
double rotate;

float buffer[5];
float enviar[5];

GLfloat lPos[4];
GLfloat lKa[4];
GLfloat lKd[4];
GLfloat lKs[4];
GLfloat mKd[4];
GLfloat mKs[4];
GLfloat mKe[4];

GLfloat lPos1[4];
GLfloat lPos2[4];
GLfloat lPos3[4];
GLfloat lPos4[4];
GLfloat lPos5[4];

GLfloat lKa1[4];
GLfloat lKd1[4];
GLfloat lKs1[4];

int city;

void escreveTexto(void * font, char *s, float x, float y, float z); //(fonte da glut, string, x, y, z)
void HitBox(int x, int y, int altura, int largura);
void HitBoxParticula(double x, double y, double z, double altura, double largura);

float matAmbAndDif[4];    //vetor cor ambiente e difusa: branca
float matShine[1];                       // expoente especular (shininess)
int light;

float xMouse, yMouse;
float larguraJanela, alturaJanela;

int telaInstrucoes;
int telaLoad;

GLuint menu_Fundo;
GLuint menu_Iniciar;
GLuint menu_Instrucoes;
GLuint menu_Sair;
GLuint menu_Voltar;
GLuint menu_telaInstrucoes;
GLuint jogo_Load;
GLuint particula;

#endif
