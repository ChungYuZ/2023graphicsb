#include <GL/glut.h>
void display()
{
	glBegin(GL_POLYGON);
        glVertex2f((48-100)/100.0,-(80-100)/100.0);
        glVertex2f((62-100)/100.0,-(74-100)/100.0);
        glVertex2f((68-100)/100.0,-(89-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((62-100)/100.0,-(74-100)/100.0);
        glVertex2f((74-100)/100.0,-(101-100)/100.0);
        glVertex2f((89-100)/100.0,-(84-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((74-100)/100.0,-(101-100)/100.0);
        glVertex2f((114-100)/100.0,-(55-100)/100.0);
        glVertex2f((114-100)/100.0,-(103-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((74-100)/100.0,-(101-100)/100.0);
        glVertex2f((114-100)/100.0,-(103-100)/100.0);
        glVertex2f((95-100)/100.0,-(127-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((114-100)/100.0,-(55-100)/100.0);
        glVertex2f((114-100)/100.0,-(103-100)/100.0);
        glVertex2f((155-100)/100.0,-(55-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((94-100)/100.0,-(44-100)/100.0);
        glVertex2f((94-100)/100.0,-(79-100)/100.0);
        glVertex2f((110-100)/100.0,-(63-100)/100.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f((105-100)/100.0,-(74-100)/100.0);
        glVertex2f((95-100)/100.0,-(127-100)/100.0);
        glVertex2f((95-100)/100.0,-(135-100)/100.0);
        glVertex2f((123-100)/100.0,-(135-100)/100.0);
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
