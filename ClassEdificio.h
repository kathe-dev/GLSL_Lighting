#pragma once


#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "ClassArbol.h"


class ClassEdificio
{
public:

	ClassEdificio();

	void DibujarEdificio(GLfloat x, GLfloat y, GLfloat z);
};

