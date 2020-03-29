#include "ClassArbol.h"

ClassArbol::ClassArbol()
{}

void ClassArbol::DibujarArbol( GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
		glTranslatef(x, y, z);

		//dibujar el tallo
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glutSolidCylinder(0.2f, 0.8f, 20, 20);
		glPopMatrix();

		//traslada el follaje y lo dibuja
		glPushMatrix();
			glTranslatef(0.0f, 0.4f, 0.0f);
			glutSolidSphere(0.5f, 20, 20);

		glPopMatrix();


	glPopMatrix();


}