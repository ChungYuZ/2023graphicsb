#include <stdio.h>
#include <GL/glut.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "glm.h"
GLMmodel * model=NULL;
GLMmodel * head;
GLMmodel * body=NULL;
GLMmodel * arm1=NULL, * arm2=NULL;
GLMmodel * hand1=NULL, * hand2=NULL;
GLMmodel * bot=NULL;
GLMmodel * leg1=NULL, * leg2=NULL;
GLMmodel * knee1=NULL, * knee2=NULL;
GLMmodel * foot1=NULL, * foot2=NULL;
float angle=0;
int oldX, oldY;
float dx=0, dy=0, dz=0;
int mode=0;///0:select, 1:translate, 2:rotate
float angleX[10], angleY[10], angleZ[10];
float posX[10], posY[10];
int nowID=0;
int show[10]={0,1,1,1,1,1,1,1,1,1};
void resize(int width, int height);
void timer(int t);
void display();
int myTexture(char *filename);
void loadGundamAll();
void showAxis();
void display()
{
    glClearColor(0.5,0.5,0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(0, -1, 0);
        showAxis();
        glTranslatef(dx,dy,dz);

        //glRotatef(angle, 0,1,0);
        if(show[0]==1) glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);

        if(show[2]==1) glmDraw(body, GLM_SMOOTH | GLM_TEXTURE);
        glPushMatrix();
            glTranslatef(0.00, +1.69, 0.00);
            glRotatef(angleZ[1], 0,0,1);
            glRotatef(angleX[1], 0,1,0);
            glRotatef(angleY[1], 1,0,0);
            glTranslatef(0.00, -1.69, 0.00);
            if(show[1]==1) glmDraw(head, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
        glPushMatrix();///left arm and hand
            glTranslatef(-0.31, +1.60, 0.00);
            glRotatef(angleX[3], 0,0,1);
            glRotatef(angleY[3], 0,1,0);
            glTranslatef(0.31, -1.60, 0.00);
            if(show[3]==1) glmDraw(arm1, GLM_SMOOTH | GLM_TEXTURE);

            glTranslatef(-0.34, +1.39, 0.00);
            glRotatef(-angleX[5], 1,0,0);
            glRotatef(angleY[5], 0,1,0);
            glTranslatef(0.34, -1.39, 0.00);
            if(show[5]==1) glmDraw(hand1, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
        glPushMatrix();///right arm and hand
            glTranslatef(+0.31, +1.60, 0.00);
            glRotatef(angleX[4], 0,0,1);
            glRotatef(angleY[4], 0,1,0);
            glTranslatef(-0.31, -1.60, 0.00);
            if(show[4]==1) glmDraw(arm2, GLM_SMOOTH | GLM_TEXTURE);

            glTranslatef(+0.34, +1.39, 0.00);
            glRotatef(-angleX[6], 1,0,0);
            glRotatef(angleY[6], 0,1,0);
            glTranslatef(-0.34, -1.39, 0.00);
            if(show[6]==1) glmDraw(hand2, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
        if(show[7]==1) glmDraw(bot, GLM_SMOOTH | GLM_TEXTURE);
        if(show[8]==1) glmDraw(leg1, GLM_SMOOTH | GLM_TEXTURE);
        if(show[9]==1) glmDraw(leg2, GLM_SMOOTH | GLM_TEXTURE);
        glmDraw(knee1, GLM_SMOOTH | GLM_TEXTURE);
        glmDraw(knee2, GLM_SMOOTH | GLM_TEXTURE);
        glmDraw(foot1, GLM_SMOOTH | GLM_TEXTURE);
        glmDraw(foot2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glutSwapBuffers();
}

void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ar, 0.001, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(0,0,2, 0,0,0, 0,1,0);
}
void timer(int t)
{
    glutTimerFunc(30, timer, t+1);
    angle++;
    glutPostRedisplay();
}
char strMode[3][20]={"select","translate","Rotate"};
void keyboard(unsigned char key, int x, int y)
{
    int now;
    if(isdigit(key)) nowID=key-'0';
    if(mode==0 && isdigit(key)) show[nowID]=!show[nowID];
    if(key=='q' || key=='Q') mode=0;///select
    if(key=='w' || key=='W') mode=1;///translate
    if(key=='e' || key=='E') mode=2;///rotate
    if(key=='a' || key=='A'){///reset
        angleX[nowID]=0; angleY[nowID]=0;
    }
    if(mode==0){
        for(int i=0;i<10;i++){
            printf("[%d]:%d ", i,show[i]);
        }
        printf("\n");
    }
    printf("Mode: %s, nowID:%d\n", strMode[mode], nowID);
}
void mouse(int button, int state, int x, int y)
{
    oldX=x; oldY=y;
}
void motion(int x, int y)
{
    if(mode==1){///translate
        posX[nowID]+=(x-oldX)/300.0;
        posY[nowID]-=(y-oldY)/300.0;
        printf("glTranslatef(%.2f, %.2f, %.2f);\n", posX[nowID], posY[nowID], 0);
    }else if(mode==2){
        angleX[nowID]+= x-oldX;
        angleY[nowID]+= y-oldY;
        printf("angleX:%.0f, angleY:%.0f\n", angleX[nowID], angleY[nowID]);
    }
    oldX=x; oldY=y;
    glutPostRedisplay();
}
void showAxis()
{
    glutSolidSphere(0.1, 10,10);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex3f(0,0,0); glVertex3f( 0.5, 0,0);
        glVertex3f(0,0,0); glVertex3f(-0.5, 0,0);
        glVertex3f(0,0,0); glVertex3f(0, 0.5, 0);
        glVertex3f(0,0,0); glVertex3f(0,-0.5, 0);
        glVertex3f(0,0,0); glVertex3f(0,0, 0.5);
        glVertex3f(0,0,0); glVertex3f(0,0,-0.5);
    glEnd();
    glColor3f(1,1,1);
}
int myTexture(char *filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void loadGundamAll()
{
    float dimensions[3];
    if(model==NULL){
        model = glmReadOBJ("Gundam.obj");
        head = glmReadOBJ("head.obj");
        body = glmReadOBJ("body.obj");
        arm1 = glmReadOBJ("arm1.obj");
        arm2 = glmReadOBJ("arm2.obj");
        hand1 = glmReadOBJ("hand1.obj");
        hand2 = glmReadOBJ("hand2.obj");
        bot = glmReadOBJ("bot.obj");
        leg1 = glmReadOBJ("leg1.obj");
        leg2 = glmReadOBJ("leg2.obj");
        knee1 = glmReadOBJ("knee1.obj");
        knee2 = glmReadOBJ("knee2.obj");
        foot1 = glmReadOBJ("foot1.obj");
        foot2 = glmReadOBJ("foot2.obj");
        glmDimensions(model, dimensions);
        glmScale(model, 2.0/dimensions[1]);
        glmScale(head, 2.0/dimensions[1]);
        glmScale(body, 2.0/dimensions[1]);
        glmScale(arm1, 2.0/dimensions[1]);
        glmScale(arm2, 2.0/dimensions[1]);
        glmScale(hand1, 2.0/dimensions[1]);
        glmScale(hand2, 2.0/dimensions[1]);
        glmScale(bot, 2.0/dimensions[1]);
        glmScale(leg1, 2.0/dimensions[1]);
        glmScale(leg2, 2.0/dimensions[1]);
        glmScale(knee1, 2.0/dimensions[1]);
        glmScale(knee2, 2.0/dimensions[1]);
        glmScale(foot1, 2.0/dimensions[1]);
        glmScale(foot2, 2.0/dimensions[1]);
    }
    myTexture("Diffuse.jpg");
}
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    //glutInitWindowSize(400,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    loadGundamAll();
    glutMainLoop();

    return EXIT_SUCCESS;
}
