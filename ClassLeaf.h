#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include <string>
#include "AbrirMalla.h"
using namespace std;

class ClassLeaf
{
	AbrirMalla nombreAsignado = AbrirMalla("./mallas/leaf.obj");

public:
	ClassLeaf();

	void DibujarLeaf();
};
