#include <GL/glut.h>
#include "glm.h"
GLMmodel*pmodel=NULL;
void display()
{
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    if(pmodel==NULL){
        pmodel=glmReadOBJ("Gundam.obj");
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel,90);
    }
    glmDraw(pmodel,GLM_SMOOTH | GLM_MATERIAL);
    glutSwapBuffers();
}
int main(int argc, char* argv[] )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week08");
    glutDisplayFunc(display);
    glutMainLoop();
}
