# The incredible world of SpongeBobScaredPants

<img src="https://static.wixstatic.com/media/2c841b_c9d3d8541b6a46be86b1fcd3afe3a05f~mv2.png/v1/fill/w_1622,h_886/TP2Logo.png" style="float: right">  
TP2 Computação Gráfica

# Instruções

Para realizar o desenvolvimento do trabalho foram utilizadas as seguintes
bibliotecas: FreeGlut, Glew, SOIL, SDL e SDL-mixer, para garantir o
funcionamento, devemos instalar:

_sudo apt-get update_  
_sudo apt install freeglut3-dev_  
_sudo apt install libglew-dev_  
_sudo apt install libsoil-dev_  
_sudo apt install libsdl1.2-dev_  
_sudo apt install libsdl-image1.2-dev_  
_sudo apt install libsdl-mixer1.2-dev_  
_sudo apt install libsdl-ttf2.0-dev_

ou

sudo apt install freeglut3-dev libglew-dev libsoil-dev libsdl1.2-dev
libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev

para compilar e executar o programa é necessário ir até a pasta makefile, abrir
pelo terminal e executar o comando "make run".

# Comandos

**l** -> ativa/desativa iluminação  
**w/a/s/d** -> movimenta o personagem  
**q/e** -> move o personagem para cima e para baixo respectivamente  
**mouse/setas direcionais** -> movem a camera  
**1/2** -> seleciona o modo de camera terceira e primeira pessoa
respectivamente  
**j** -> ativa/desativa particulas(nao concluido)  
**c** -> muda o chunck(nao concluido)

# Configurar Servidor Local

Para conectar ao servidor local:

1- certifique-se de manter as duas maquinas na mesma rede  
tambem se certifique que o ip informado no codigo do cliente seja o ip (ipV4) da
maquina do servidor na rede  
2- execute no primeiro jogador selecionando a opção **(1)server**  
3- execute no segundo jogador selecionando a opção **(2)cliente**
