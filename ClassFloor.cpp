#include "ClassFloor.h"


ClassFloor::ClassFloor()
{}

void ClassFloor::DibujarFloor(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);

	//dibujar el cubo
	glPushMatrix();
	glScalef(14.0f, 0.2f, 14.0f);
	glutSolidCube(1);
	glPopMatrix();


	glPopMatrix();


}