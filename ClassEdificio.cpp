#include "ClassEdificio.h"

ClassEdificio::ClassEdificio()
{}

void ClassEdificio::DibujarEdificio(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(-15, 1, 1, 0);

	//trapiche
	glPushMatrix();
		glTranslatef(0.0f, -0.3f, 0.0f);
		//glRotatef(-15, 0, 1, 0);
		glScalef(0.8f, 0.4f, 1.2f);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -0.3f, -1.2f);
		//glRotatef(-15, 0, 1, 0);
		glScalef(0.3f, 0.8f, 1.2f);
		glutSolidCube(1.0);
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0.0f, -0.3f, 0.0f);
	//glRotatef(-15, 0, 1, 0);
	//glScalef(0.8f, 0.4f, 1.2f);
	//glutSolidCube(1.0);
	//glPopMatrix();


	glPopMatrix();
}