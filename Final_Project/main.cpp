#include <stdio.h> ///­nÀÉ®×ªºInput/Output
#include <GL/glut.h>
#include "glm.h"
GLMmodel * head=NULL;
GLMmodel * body=NULL;
GLMmodel * Rshoulder=NULL;
GLMmodel * Rarm=NULL;
int show[4]={1,0,0,0};
float teapotX = 0, teapotY = 0;
FILE * fout = NULL;///step02-1
FILE * fin = NULL;///step02-2
void keyboard(unsigned char key,int x,int y){
    if(key=='0')show[0]=! show[0];
    if(key=='1')show[1]=! show[1];
    if(key=='2')show[2]=! show[2];
    if(key=='3')show[3]=! show[3];
    glutPostRedisplay();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(head==NULL){
        head=glmReadOBJ("model/head.obj");
        body=glmReadOBJ("model/body.obj");
        Rshoulder=glmReadOBJ("model/Rshoulder.obj");
        Rarm=glmReadOBJ("model/Rarm.obj");
    }
        glPushMatrix();
            glTranslatef(teapotX,teapotY,0);
            if(show[0])glmDraw(head,GLM_MATERIAL);
        glPopMatrix();
        if(show[1])glmDraw(body,GLM_MATERIAL);
        if(show[2])glmDraw(Rshoulder,GLM_MATERIAL);
        if(show[3])glmDraw(Rarm,GLM_MATERIAL);
    glPopMatrix();
    glutSwapBuffers();
}
int oldX=0,oldY=0;
void mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN){
        oldX=x;
        oldY=y;
    }
}
void motion(int x,int y){
    teapotX += (x-oldX)/150.0;
    teapotY -= (y-oldY)/150.0;
    oldX=x;
    oldY=y;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week13");

    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); ///step02-2
    glutMouseFunc(mouse); ///step02-1

    glutMainLoop();
}
