#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

#include "teclado.h"
#include "desenhaCena.h"
#include "inicializa.h"
#include "detectaMouse.h"
#include "global.h"

int main(int argc, char *argv[])
{

  printf("como você gostaria de se conectar ao servidor de SpongeBob ScarePants?\n(1)-abrir servidor\n(2)-conectar como cliente\n(0)-jogar offline\n");
  scanf("%i", &choose );


if(choose==1){

  printf("estabelecendo servidor, aguardando usuários...\n\n");
	// criar descrição do socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("conexão falhou :(");
		exit(EXIT_FAILURE);
	}

	// colocando socket na porta 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// conectando socket à porta 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind falhou :(");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

  printf("conexão estabelecida!");

}
if(choose==2){



	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Servidor não encontrado \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// conversão de IP
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nAcesso inválido ou negado \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConexão falhou :( \n entre em contato com seu servidor local\n\n");
		return -1;
	}




}




  //servidor
  //------------------------------------------------------------------------
  //openGL

    srand(time(0));


    glutInit(&argc, argv);

    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(larguraJanela, alturaJanela);
    glutInitWindowPosition (0, 0);

    glutCreateWindow("SpongeBlock");

    glutEnterGameMode();

    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutTimerFunc(10, frame, 10);                 //1000/16 = 62.5 fps


    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);                      //capturar cliques do mouse
    glutPassiveMotionFunc(posicionaCamera);     //capturar posicionamento do mouse
    glutSpecialFunc(specialInput);              //utilizar caracteres especiais do teclado
    glutKeyboardUpFunc(keyUp);



    inicializa();

    glutMainLoop();
}
