#include <stdio.h> ///要檔案的Input/Output
#include <GL/glut.h>
///step03-1
///CodeBlocks的專案設定 Project-Properties裡第二個Build Target
/// Executing working dir 工作執行目錄
///原本是 C:\Users\Administrator\Desktop\freeglut\bin
///改成 . (小數點) 再 File-Save Everything 便能將專案檔設好、存檔。
///之後你的工作執行目錄, 就在你的程式專案的那一目錄裡
///但執行時, 就會少了 freeglut.dll 檔, 你再手動copy到你的專案檔裡。
///  註: 你可以看到 .cbp CodeBlocks Project 專案裡 working_dir 有變動哦
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
    if(state==GLUT_DOWN){ ///如果mouse按下去
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
