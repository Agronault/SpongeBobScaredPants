#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "glm.h"
#include "glmint.h"
#include "load.h"
#include "global.h"

GLMmodel *cityModel = NULL;
GLMmodel *city2Model = NULL;
GLMmodel *zepModel = NULL;
GLMmodel *skyModel = NULL;

void desenha_load(){

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, jogo_Load);
    HitBox( larguraJanela/2, 0, alturaJanela, larguraJanela/2);
    glDisable(GL_TEXTURE_2D);

    glColor3f(0, 0, 0);
    sprintf(texto, "LOADING...");
    escreveTexto(GLUT_BITMAP_HELVETICA_18, texto, 1000, 20, 0);

    glutSwapBuffers();
}

void MENU_load(){

    menu_Fundo = SOIL_load_OGL_texture(
        "../source/misc/menu.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

    menu_Iniciar = SOIL_load_OGL_texture(
        "../source/misc/jogar.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );

    menu_Instrucoes = SOIL_load_OGL_texture(
        "../source/misc/inst.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );

    menu_Sair = SOIL_load_OGL_texture(
        "../source/misc/sair.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );

    menu_Voltar = SOIL_load_OGL_texture(
        "../source/misc/a.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );

    menu_telaInstrucoes = SOIL_load_OGL_texture(
        "../source/misc/instrucoes.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );

    jogo_Load = SOIL_load_OGL_texture(
        "../source/misc/jogo_Load.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );

    particula = SOIL_load_OGL_texture(
        "../source/misc/particula2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

}

void GAME_load(){




}

void drawmodelCity(){

    if(!cityModel){
        cityModel = glmReadOBJ("../source/obj/lastBikini/bikinitp2.obj");
        glmScale(cityModel, 200.0);
        if(!cityModel)
            exit(0);
        glmUnitize(cityModel);
        glmFacetNormals(cityModel);
        glmVertexNormals(cityModel, 90.0, 1);   //(model, angle, bool keep_existing)
    }

    glmDraw(cityModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

void drawmodelSky(){

    if(!skyModel){
        skyModel = glmReadOBJ("../source/obj/TP2SkySphere/TP2Sphere.obj");
        glmScale(skyModel, 200.0);
        if(!skyModel)
            exit(0);
        glmUnitize(skyModel);
        glmFacetNormals(skyModel);
        glmVertexNormals(skyModel, 90.0, 1);   //(model, angle, bool keep_existing)
    }

    glmDraw(skyModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}


void drawmodelCity2(){

    if(!city2Model){
        city2Model = glmReadOBJ("../source/obj/newBikini/bikinitp2.obj");
        glmScale(city2Model, 200.0);
        if(!city2Model)
            exit(0);
        glmUnitize(city2Model);
        glmFacetNormals(city2Model);
        glmVertexNormals(city2Model, 90.0, 1);   //(model, angle, bool keep_existing)
    }

    glmDraw(city2Model, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

void drawmodelZep(){

    if(!zepModel){
        zepModel = glmReadOBJ("../source/obj/SpongeBob (Skeleton)/sbskeleton.obj");
        if(!zepModel)
            exit(0);
        glmUnitize(zepModel);
        glmFacetNormals(zepModel);
        glmVertexNormals(zepModel, 90.0, 1);    //(model, angle, bool keep_existing)
    }

    glmDraw(zepModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);

}

void drawmodelZep2(){

    if(!zepModel){
        zepModel = glmReadOBJ("../source/obj/SpongeBob (Skeleton)/sbskeleton.obj");
        if(!zepModel)
            exit(0);
        glmUnitize(zepModel);
        glmFacetNormals(zepModel);
        glmVertexNormals(zepModel, 90.0, 1);    //(model, angle, bool keep_existing)
    }

    glmDraw(zepModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);

}




void drawEstrelas(int quantidade){
   int i;

  for(i=0; i<quantidade; i++){
    glColor4f(0,0,0,1);

    glBindTexture(GL_TEXTURE_2D, particula);
    HitBoxParticula(rand()%20-10, rand()%20-10, rand()%20-10, 1, 2/2);

  }



}
