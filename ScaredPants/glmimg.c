#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
# ifdef _WIN32
#   include <windows.h>
# endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#include "glm.h"
/*
#define DEBUG
#define GLDEBUG
*/
#include "glmint.h"

#include "SOIL/SOIL.h"


/*
#undef HAVE_LIBJPEG
#undef HAVE_LIBSDL_IMAGE
*/
/* WARNING: GLOBAL VARIABLES */
GLenum _glmTextureTarget = GL_TEXTURE_2D;
static GLint gl_max_texture_size;
static int glm_do_init = 1;
static GLboolean gl_sgis_generate_mipmap = GL_FALSE;

static GLboolean glmIsExtensionSupported(const char *extension)
{

    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    /* Extension names should not have spaces. */
    where = (GLubyte *) strchr(extension, ' ');
    if (where || *extension == '\0')
	return 0;

    extensions = glGetString(GL_EXTENSIONS);
    if (!extensions)
	return GL_FALSE;

    /* It takes a bit of care to be fool-proof about parsing the
       OpenGL extensions string.  Don't be fooled by sub-strings,
       etc. */
    start = extensions;
    for (;;) {
	where = (GLubyte *) strstr((const char *) start, extension);
	if (!where)
	    break;
	terminator = where + strlen(extension);
	if (where == start || *(where - 1) == ' ')
	    if (*terminator == ' ' || *terminator == '\0')
		return GL_TRUE;
	start = terminator;
    }
    return GL_FALSE;
}

static void glmImgInit(void)
{
    glm_do_init = 0;
    _glmTextureTarget = GL_TEXTURE_2D;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &gl_max_texture_size);
    if (gl_max_texture_size <= 0)
        __glmFatalError( "glmImgInit() failed: glGetIntegerv(GL_MAX_TEXTURE_SIZE) returned %d. Maybe the OpenGL context is not initialized?", gl_max_texture_size);
#if GLM_MAX_TEXTURE_SIZE > 0    
#warning GLM_MAX_TEXTURE_SIZE
    if(gl_max_texture_size > GLM_MAX_TEXTURE_SIZE)
        gl_max_texture_size = GLM_MAX_TEXTURE_SIZE;
#endif
    //return;
#if 0				/* rectangle textures */
#ifdef GL_TEXTURE_RECTANGLE_ARB
    if (glmIsExtensionSupported("GL_ARB_texture_rectangle")) {
	DBG_(__glmWarning("glmImgInit(): GL_ARB_texture_rectangle is available"));
	_glmTextureTarget = GL_TEXTURE_RECTANGLE_ARB;
    }
    else
#endif
#ifdef GL_TEXTURE_RECTANGLE_NV
	if (glmIsExtensionSupported("GL_NV_texture_rectangle")) {
	    DBG_(__glmWarning("glmImgInit(): GL_NV_texture_rectangle is available"));
	    _glmTextureTarget = GL_TEXTURE_RECTANGLE_NV;
	}
#endif
#endif				/* rectangle textures */
#ifdef GL_GENERATE_MIPMAP_SGIS
    if (glmIsExtensionSupported("GL_SGIS_generate_mipmap")) {
	DBG_(__glmWarning("glmImgInit(): GL_SGIS_generate_mipmap is available"));
	gl_sgis_generate_mipmap = GL_TRUE;
    }
#endif
    /*_glmTextureTarget = GL_TEXTURE_2D;*/
}

/* glmReadPPM: read a PPM raw (type P6) file.  The PPM file has a header
 * that should look something like:
 *
 *    P6
 *    # comment
 *    width height max_value
 *    rgbrgbrgb...
 *
 * where "P6" is the magic cookie which identifies the file type and
 * should be the only characters on the first line followed by a
 * carriage return.  Any line starting with a # mark will be treated
 * as a comment and discarded.   After the magic cookie, three integer
 * values are expected: width, height of the image and the maximum
 * value for a pixel (max_value must be < 256 for PPM raw files).  The
 * data section consists of width*height rgb triplets (one byte each)
 * in binary format (i.e., such as that written with fwrite() or
 * equivalent).
 *
 * The rgb data is returned as an array of unsigned chars (packed
 * rgb).  The malloc()'d memory should be free()'d by the caller.  If
 * an error occurs, an error message is sent to stderr and NULL is
 * returned.
 *
 * filename   - name of the .ppm file.
 * width      - will contain the width of the image on return.
 * height     - will contain the height of the image on return.
 *
 */
static GLubyte* 
glmReadPPM(const char* filename, GLboolean alpha, int* width, int* height, int *type)
{
    FILE* fp;
    int i, w, h, d;
    unsigned char* image;
    char head[70];          /* max line <= 70 in PPM (per spec). */
    
    fp = fopen(filename, "rb");
    if (!fp) {
        perror(filename);
        return NULL;
    }
    
    /* grab first two chars of the file and make sure that it has the
       correct magic cookie for a raw PPM file. */
    fgets(head, 70, fp);
    if (strncmp(head, "P6", 2)) {
	DBG_(__glmWarning("glmReadPPM() failed: %s: Not a raw PPM file", filename));
	fclose(fp);
        return NULL;
    }
    
    /* grab the three elements in the header (width, height, maxval). */
    i = 0;
    while(i < 3) {
        fgets(head, 70, fp);
        if (head[0] == '#')     /* skip comments. */
            continue;
        if (i == 0)
            i += sscanf(head, "%d %d %d", &w, &h, &d);
        else if (i == 1)
            i += sscanf(head, "%d %d", &h, &d);
        else if (i == 2)
            i += sscanf(head, "%d", &d);
    }
    
    /* grab all the image data in one fell swoop. */
    image = (unsigned char*)malloc(sizeof(unsigned char)*w*h*3);
    fread(image, sizeof(unsigned char), w*h*3, fp);
    fclose(fp);
    
    *type = GL_RGB;
    *width = w;
    *height = h;
    return image;
}




/* don't try alpha=GL_FALSE: gluScaleImage implementations seem to be buggy */
GLuint
glmLoadTexture(const char *filename, GLboolean alpha, GLboolean repeat, GLboolean filtering, GLboolean mipmaps, GLfloat *texcoordwidth, GLfloat *texcoordheight) {
    GLuint id;
    
    printf("3D->%s\n", filename);
    
    
    id = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
            );
    

    if (id == 0) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }
    
    if (_glmTextureTarget == GL_TEXTURE_2D) {
	*texcoordwidth = 1.;		//Posicao da textura entre 0..1;
	*texcoordheight = 1.;
    }
    
    return id;
}


