#include <GL/glut.h>
void display()
{
	glBegin(GL_POLYGON);
        glVertex2f((29-100)/100.0,-(65-100)/100.0);
        glVertex2f((40-100)/100.0,-(55-100)/100.0);
        glVertex2f((43-100)/100.0,-(65-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((40-100)/100.0,-(55-100)/100.0);
        glVertex2f((72-100)/100.0,-(58-100)/100.0);
        glVertex2f((50-100)/100.0,-(79-100)/100.0);
    glEnd();


	glutSwapBuffers();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("week02");
	glutDisplayFunc(display);
	glutMainLoop();
}
