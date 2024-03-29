//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================


//PROYECTO DE COMPUTACON GRAFICA
//REALIZADO POR:
//JUAN JOSE BETANCOURT
//CAMILA PALADINES
//KATHERINE RAMIREZ

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "AbrirMalla.h"
#include "ClassSugarcane.h"
#include "ClassBridge.h"
#include "ClassChair.h"
#include "ClassTree.h"
#include "ClassTable.h"
#include "ClassFloor.h"
#include "ClassLeaf.h"
#include "FreeImage.h"  //Para textura

//-----------------------------------------------------------------------------

#define NUM_ARBOLES  10

class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;
    cwc::glShader* shader;
    cwc::glShader* shaderTextura;  //Para textura
    GLuint ProgramObject;
    clock_t time0, time1;
    float timer010;  // timer counting 0->1->0
    bool bUp;        // flag if counting up or down.
    ClassSugarcane* miCane;
    ClassBridge* miBridge;  //Objeto con textura
    ClassChair* miChair;
    ClassTree* miTree;
    ClassTable* miTable;
    ClassFloor* miFloor;
    ClassLeaf* miLeaf;
    GLuint texid; //id de la textura
    GLfloat movimientoY;
    GLfloat movimientoX;
    GLfloat movimientoZ;
    bool Yup, Ydown;
    bool Xup, Xdown;
    bool Zup, Zdown;


public:
    myWindow() {}

    void controlMovimiento() {
        if (Yup)
        {
            if (movimientoY + 0.05 >= -4.0) {
                movimientoY = movimientoY + 0.05;
            }
        }
        if (Ydown) {
            if (movimientoY - 0.05 >= -4.0) {
                movimientoY = movimientoY - 0.05;
            }
        }
        if (Xup) {
            movimientoX = movimientoX + 0.05;
        }
        if (Xdown) {
            movimientoX = movimientoX - 0.05;
        }

        if (Zup) {
            movimientoZ = movimientoZ + 0.05;
        }
        if (Zdown) {
            movimientoZ = movimientoZ - 0.05;
        }
    }

    void initialize_textures(void)
    {
        int w, h;
        GLubyte* data = 0;
        //data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
        //std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

        //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./Mallas/texPuente.jpg", 0),
            "./Mallas/texPuente.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }



    virtual void OnRender(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //timer010 = 0.09; //for screenshot!
        glPushMatrix();

        //control TX locales
        glPushMatrix();
        if (shader) shader->begin();

        //posiciona y dibuja la ca�a de azucar
        glPushMatrix();
        glTranslatef(0.5f, 1.4f, -4.0f);
        glScalef(1.5f, 1.5f, 1.5f);
        miCane->DibujarSugarCane();
        glPopMatrix();


        //posiciona y dibuja la silla
        glPushMatrix();
        glTranslatef(-3.0f, 0.91f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        miChair->DibujarChair();
        glPopMatrix();
        
        //posiciona y dibuja el arbol
        glPushMatrix();
        glTranslatef(-4.5f, 3.0f, 0.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        miTree->DibujarTree();
        glPopMatrix();

        //posiciona y dibuja la hoja
        glPushMatrix();
        controlMovimiento();
        glTranslatef(movimientoX, movimientoY, movimientoZ);
        glTranslatef(-4.6f, 4.0f, 0.0f);
        glScalef(0.2f, 0.2f, 0.2f);
        miLeaf->DibujarLeaf();
        glPopMatrix();
        
        //posiciona y dibuja la mesa
        glPushMatrix();
        glTranslatef(-2.0f, 0.3f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        miTable->DibujarTable();
        glPopMatrix();

        //posiciona y dibuja el piso
        glPushMatrix();
        miFloor->DibujarFloor(0.0, 0.0, 0.0);
        glPopMatrix();

        if (shader) shader->end();

        /*** Para Textura: llamado al shader para objetos texturizados***/
        if (shaderTextura) shaderTextura->begin();

            //posiciona y dibuja el puente
            glPushMatrix();
            glTranslatef(0.0f, 0.7f, 4.0f);
            glScalef(3.0f, 3.0f, 3.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            
            glBindTexture(GL_TEXTURE_2D, texid);
            miBridge->DibujarBridge();
            glPopMatrix();
      //glutSolidTeapot(1.0);
      if (shaderTextura) shaderTextura->end();

        glPopMatrix();

        glutSwapBuffers();
        glPopMatrix();

        UpdateTimer();

        Repaint();
    }

    virtual void OnIdle() {}

    // When OnInit is called, a render context (in this case GLUT-Window) 
    // is already available!

    virtual void OnInit()
    {
        movimientoY = 0.0f;
        movimientoX = 0.0f;
        movimientoZ = 0.0f;
        Yup = false;
        Ydown = false;
        Xup = false;
        Xdown = false;
        Zdown = false;
        Zup = false;

        miCane = new ClassSugarcane();
        miBridge = new ClassBridge();
        miChair = new ClassChair();
        miTree = new ClassTree();
        miTable = new ClassTable();
        miFloor = new ClassFloor();
        miLeaf = new ClassLeaf();

        glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
        if (shader == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader->GetProgramObject();
        }

        //Para Textura: abre los shaders para texturas
        shaderTextura = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt");
        if (shaderTextura == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shaderTextura->GetProgramObject();
        }
        time0 = clock();
        timer010 = 0.0f;
        bUp = true;

        initialize_textures();
        DemoLight();

    }

    virtual void OnResize(int w, int h)
    {
        if (h == 0) h = 1;
        float ratio = 1.0f * (float)w / (float)h;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, w, h);

        gluPerspective(45, ratio, 1, 500);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(10.0f, 10.0f, 10.0f,
            0.0, 0.0, 0.0,
            0.0f, 1.0f, 0.0f);
    }
    virtual void OnClose(void) {}
    virtual void OnMouseDown(int button, int x, int y) {}
    virtual void OnMouseUp(int button, int x, int y) {}
    virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) {}

    virtual void OnKeyDown(int nKey, char cAscii)
    {
        if (cAscii == 27) // 0x1b = ESC
        {
            this->Close(); // Close Window!
        }
        switch (cAscii)
        {
        case 'w':
            Yup = true;
            break;
        case 's':
            Ydown = true;
            break;
        case 'a':
            Xdown = true;
            break;
        case 'd':
            Xup = true;
            break;
        case 'x':
            Zup = true;
            break;
        case 'y':
            Zdown = true;
        }
        

    };

    virtual void OnKeyUp(int nKey, char cAscii)
    {
        if (cAscii == 'l')      // s: Shader
            shader->enable();
        else if (cAscii == 'f') // f: Fixed Function
            shader->disable();

        switch (cAscii)
        {
        case 'w':
            Yup = false;
            break;
        case 's':
            Ydown = false;
            break;
        case 'a':
            Xdown = false;
            break;
        case 'd':
            Xup = false;
            break;
        case 'x':
            Zup = false;
            break;
        case 'y':
            Zdown = false;
        }
    }

    void UpdateTimer()
    {
        time1 = clock();
        float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
        delta = delta / 4;
        if (delta > 0.00005f)
        {
            time0 = clock();
            if (bUp)
            {
                timer010 += delta;
                if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
            }
            else
            {
                timer010 -= delta;
                if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
            }
        }
    }

    void DemoLight(void)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        // Light model parameters:
        // -------------------------------------------

        GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

        // -------------------------------------------
        // Spotlight Attenuation

        GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
        GLint spot_exponent = 30;
        GLint spot_cutoff = 180;

        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
        glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
        glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

        GLfloat Kc = 1.0;
        GLfloat Kl = 0.0;
        GLfloat Kq = 0.0;

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


        // ------------------------------------------- 
        // Lighting parameters:

        GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
        GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
        GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
        GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

        // -------------------------------------------
        // Material parameters:

        GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
        GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
        GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
        GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
        GLfloat material_Se = 20.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
    }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
    virtual void OnInit() { std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
    myApplication* pApp = new myApplication;
    myWindow* myWin = new myWindow();

    pApp->run();
    delete pApp;
    return 0;
}

//-----------------------------------------------------------------------------

