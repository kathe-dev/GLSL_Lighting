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

class ClassBridge
{
	AbrirMalla nombreAsignado = AbrirMalla("./mallas/OldBridge.obj");

public:
	ClassBridge();

	void DibujarBridge();
};

