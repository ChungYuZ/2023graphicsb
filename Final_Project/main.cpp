#include <stdio.h> ///要檔案的Input/Output
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
        glScalef(0.1,0.1,0.1);
        if(show[0])glmDraw(head,GLM_MATERIAL);
        if(show[1])glmDraw(body,GLM_MATERIAL);
        if(show[2])glmDraw(Rshoulder,GLM_MATERIAL);
        if(show[3])glmDraw(Rarm,GLM_MATERIAL);
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    teapotX = (x-150)/150.0;
    teapotY = (150-y)/150.0;
    if(state==GLUT_DOWN){ ///如果mouse按下去
        if(fout==NULL) fout = fopen("file4.txt", "w");

        fprintf(fout, "%f %f\n", teapotX, teapotY);
    }
    display();
}
//void keyboard(unsigned char key, int x, int y)///step02-2
//{
//    if(fin==NULL){
//       fclose(fout);///step02-2
//        fin = fopen("file4.txt", "r");///step02-2
//    }
//    fscanf(fin, "%f%f", &teapotX, &teapotY);///step02-2
//    display();///step02-2
//}///step02-2
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week13");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); ///step02-2
    glutMouseFunc(mouse); ///step02-1

    glutMainLoop();
}
