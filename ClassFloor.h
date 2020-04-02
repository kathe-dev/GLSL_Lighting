#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>

class ClassFloor
{
public:
	ClassFloor();

	void DibujarFloor(GLfloat x, GLfloat y, GLfloat z);
};

