#include <stdio.h> ///�n�ɮת�Input/Output
#include <GL/glut.h>
///step03-1
///CodeBlocks���M�׳]�w Project-Properties�̲ĤG��Build Target
/// Executing working dir �u�@����ؿ�
///�쥻�O C:\Users\Administrator\Desktop\freeglut\bin
///�令 . (�p���I) �A File-Save Everything �K��N�M���ɳ]�n�B�s�ɡC
///����A���u�@����ؿ�, �N�b�A���{���M�ת����@�ؿ���
///�������, �N�|�֤F freeglut.dll ��, �A�A���copy��A���M���ɸ̡C
///  ��: �A�i�H�ݨ� .cbp CodeBlocks Project �M�׸� working_dir ���ܰʮ@
float teapotX = 0, teapotY = 0;
FILE * fout = NULL;///step02-1
FILE * fin = NULL;///step02-2
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(teapotX, teapotY, 0);
        glutSolidTeapot( 0.3 );
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    teapotX = (x-150)/150.0;
    teapotY = (150-y)/150.0;
    if(state==GLUT_DOWN){ ///�p�Gmouse���U�h
        if(fout==NULL) fout = fopen("file4.txt", "w");

        fprintf(fout, "%f %f\n", teapotX, teapotY);
    }
    display();
}
void keyboard(unsigned char key, int x, int y)///step02-2
{
    if(fin==NULL){
        fclose(fout);///step02-2
        fin = fopen("file4.txt", "r");///step02-2
    }
    fscanf(fin, "%f%f", &teapotX, &teapotY);///step02-2
    display();///step02-2
}///step02-2
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week12");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); ///step02-2
    glutMouseFunc(mouse); ///step02-1

    glutMainLoop();
}