#include "OpenGL.h"
#include "World.h"
#include "RenderingEngine.h"
//#include "Singleton.h"
#include <iostream>
#include "GL\glext.h"
#include "InputEngine.h"
#include "ResourceManager.h"
#include "TextureManager.h"
#include "Physic\PhysicEngine.h"


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
//#include "glWindowPos.h"

#include "LightEngine.h"

OpenGL::OpenGL(void)
{
	WindowsWidth = 0;
	WindowsHeight = 0;
    CurrentInstance = this;
	myCamera = Camera::Instance();
	//fixedMouse = true;
}

OpenGL::~OpenGL(void)
{
}

void OpenGL::Init(int & argc, char ** argv, int Windowswidth, int WindowsHeight, char * name)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Windowswidth, WindowsHeight);
	glutCreateWindow(name);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	this->WindowsWidth = Windowswidth;
	this->WindowsHeight = WindowsHeight;
	LastX = glutGet(GLUT_WINDOW_WIDTH)/2;
	LastY = glutGet(GLUT_WINDOW_HEIGHT)/2;
	glutReshapeFunc(Resize);
	glutDisplayFunc(Draw);
	glutTimerFunc(20,Update, 0);
	fogEnbled = false;
}

void OpenGL::DrawModel(string ModelName, string TextureName, float transparency, Vec3 transition, Vec3 rotation)
{
	ResourceManager::Instance()->drawModel(ModelName, TextureName, transparency, transition, rotation);
}

void OpenGL::DrawModel(string ModelName,string TextureName,  float transparency , Vec3 transition, Vec3 rotation, Vec3 scale)
{
	ResourceManager::Instance()->drawModel(ModelName, TextureName, transparency, transition, rotation, scale);
}

void OpenGL::Draw()
{
	glClearColor(0.55f, 0.7f, 0.95f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!ControlSystem::Instance()->hud.getSplash())
	{
		LightEngine::Instance()->drawLights();
	
		map<int,I_DrawableObject*>::iterator it;
		for(it = CurrentInstance->RenderBuff.begin(); it != CurrentInstance->RenderBuff.end(); it++)
		{
			it->second->Draw();
		}
	
		PhysicEngine::Instance()->Draw();
	}
	else
	{
		ControlSystem::Instance()->hud.DrawSplash();
	}

	CurrentInstance->DrawGrid(gridSize);

	glutSwapBuffers();
}


void OpenGL::Resize(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w/(float)h, 1.0, 2100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void OpenGL::Update(int value)
{
	InputEngine* input;
	input = InputEngine::Instance();

	//update function for all of the game engine systems
	//gameEngine->update(); change to
	CurrentInstance->Process(0);

	//Update Camera LookAT function
	CurrentInstance->CreateLookat();

	glutPostRedisplay();
	glutTimerFunc(20, CurrentInstance->Update, 0);

}

void OpenGL::AddRefToBuffer(int Id, I_DrawableObject * Ref)
{	
	RenderBuff.insert(std::pair<int, I_DrawableObject *>(Id, Ref));
}

void OpenGL::EraseRefFromBuffer(unsigned int ID)
{
	RenderBuff.erase(ID);
}

void OpenGL::SetCallBackProcess(void (*Callback)(double))
{
	this->Process = Callback;
}

void OpenGL::setFog(GLfloat start, GLfloat end)
{

	GLfloat fogColor[4] = {0.5, 0.5, 0.6, 1.0}; //set the forcolor to grey
	GLfloat density = 0.000005; //set the density to 0.3 which isacctually quite thick

	glEnable (GL_DEPTH_TEST); //enable the depth testing
	glEnable (GL_FOG); //enable the fog
	glFogi (GL_FOG_MODE, GL_LINEAR); //set the fog mode to GL_EXP2
	glFogf (GL_FOG_START, start);
	glFogf (GL_FOG_END, end);
	glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
	glFogf (GL_FOG_DENSITY, density); //set the density to the value above
	glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
}




void OpenGL::CreateLookat()
{
	glLoadIdentity();
	gluLookAt(myCamera->GetPosition().getX(),  myCamera->GetPosition().getY(), myCamera->GetPosition().getZ(),
		      myCamera->GetPosition().getX() + myCamera->GetDirection().getX(), myCamera->GetPosition().getY() + myCamera->GetDirection().getY() , 
			  myCamera->GetPosition().getZ() + myCamera->GetDirection().getZ(),
			  myCamera->GetUp().getX() ,  myCamera->GetUp().getY(), myCamera->GetUp().getZ());

}

void OpenGL::RenderOverlay(float start_x, float start_y, float w, float h, string name)
{
	int window_W = glutGet(GLUT_WINDOW_WIDTH);
	int window_H = glutGet(GLUT_WINDOW_HEIGHT);

	int fixed_W = 1200, fixed_H = 800;
	
	float stx =  (start_x / fixed_W) * window_W;
	float endx = ((start_x + w) / fixed_W) * window_W;
	float sty = (start_y / fixed_H) * window_H;
	float endy =  ((start_y + h)/fixed_H) * window_H;

	glDisable(GL_LIGHTING);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (GLint)TextureManager::Instance()->getTexture(name));

	glPushMatrix(); // store previous context on stack

	glMatrixMode(GL_PROJECTION); // swap to projection
		glPushMatrix(); // preserve previous projection

		// define 2D projection
		glLoadIdentity(); // clear copy of previous projection
		glOrtho(0, window_W, 0, window_H, 0 ,1); // define 2D size
		
	glMatrixMode(GL_MODELVIEW); // swap to model
		glLoadIdentity(); // clear

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.9);
		glColor3f(1.0, 1.0, 1.0); // reset color, this is needed it seems
	
		glBegin(GL_QUADS); // define overlay region and how the tex maps
			glTexCoord2f(0,0);
			glVertex2f(stx, sty);
			glTexCoord2f(0,1);
			glVertex2f(stx, endy);
			glTexCoord2f(1,1);
			glVertex2f(endx , endy);
			glTexCoord2f(1,0);
			glVertex2f(endx , sty);
		glEnd();
		glDisable(GL_ALPHA_TEST);

	glMatrixMode(GL_PROJECTION); // back to projection
		glPopMatrix(); // restore 3D projection matrix
	
	glMatrixMode(GL_MODELVIEW); // back to model (?) required
	glEnable(GL_LIGHTING);
	glPopMatrix(); // return to original context prior to this function
}

void OpenGL::renderString(float start_x, float start_y, std::string text, int TextSize)
{
	int window_W = glutGet(GLUT_WINDOW_WIDTH);
	int window_H = glutGet(GLUT_WINDOW_HEIGHT);

	int fixed_W = 1200;
	int fixed_H = 800;

	 float stx =  (start_x / fixed_W) * window_W;
	 float sty = (start_y / fixed_H) * window_H;

	glColor3f(1.0, 1.0, 1.0);
	glWindowPos2f(stx, sty);
	for(int i = 0; i < text.size(); i++)
	{
		switch(TextSize)
		{
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,text[i]);
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,text[i]);
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,text[i]);
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,text[i]);
			break;
		default:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,text[i]);
			break;
		}
	}
}

void OpenGL::loop()
{
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();
}

void OpenGL::DrawSkyBox(Vec3 Center, GLuint vetexbuffer, GLuint elementbuffer, GLuint TextureCoorbuffer, string TextureName)
{
	glUseProgram(ResourceManager::Instance()->GetShaderProram("SkyBox"));
	GLuint PVM = glGetUniformLocation(ResourceManager::Instance()->GetShaderProram("SkyBox"), "PVM");
	glm::mat4 Project =   glm::perspective(60.0f, (float)WindowsWidth/(float)WindowsHeight, 1.0f, 4000.0f);
	glm::mat4 view    =   glm::mat4(1.0f);
	glm::mat4 RotateY =   glm::rotate(glm::mat4(1.0f),   myCamera->GetRotateY() , glm::vec3(-1.0f ,0.0f, 0.0f));
	glm::mat4 RotateX =   glm::rotate(RotateY ,          myCamera->GetRotateX() , glm::vec3( 0.0f, 1.0f, 0.0f));
	glm::mat4 M = Project * view * RotateX;
	glUniformMatrix4fv(PVM, 1, GL_FALSE, glm::value_ptr(M));
	glPushMatrix();
	//glDepthMask (GL_FALSE);
	glTranslatef(Center.getX(), Center.getY(), Center.getZ());
	//glClientActiveTexture(GL_TEXTURE1);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glBindBufferARB(GL_ARRAY_BUFFER, TextureCoorbuffer);
	//glTexCoordPointer(2,GL_FLOAT, 0, nullptr);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ResourceManager::Instance()->getTexture(TextureName));

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vetexbuffer);
	glVertexPointer(3, GL_FLOAT,0, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_QUADS,  24 , GL_UNSIGNED_SHORT , nullptr);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_CUBE_MAP);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDepthMask (GL_TRUE);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPopMatrix();

	glUseProgram(0);
}

void OpenGL::DrawGrid(int gridSize)
{
	/**
	glBegin(GL_LINES);
    glColor3f(0.75f, 0.75f, 0.75f);
    for(int i=-gridSize;i<=gridSize;i++)
    {
        glVertex3f((float)i,-45,(float)-gridSize);
        glVertex3f((float)i,-45,(float)gridSize);
 
        glVertex3f((float)-gridSize,-45,(float)i);
        glVertex3f((float)gridSize,-45,(float)i);
    }
    glEnd();*/
}