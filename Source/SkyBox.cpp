#include "SkyBox.h"
#include "GL\freeglut.h"
#include "GL\glext.h"
#include "ResourceManager.h"

SkyBox::SkyBox(RenderingEngine  * Ref, Vec3 pos, string _texture): GameObject(Ref,pos,0,0,"","", true, 1,10)
{
	texture = _texture;
}

SkyBox::~SkyBox(void)
{
}

void SkyBox::UpdateSkyBoxPos()
{
	Vec3 newpos = ((OpenGL*)RederingHandle->GetRenderHandle())->GetCamera()->GetPosition();
	this->m_position = newpos;
}

void SkyBox::SetAttributes(float width)
{
	m_width = width/2;
	GenerateBuffer();
}

void SkyBox::GenerateBuffer()
{
	ResourceManager::Instance()->GenerateShader("Shaders/Skyvertex.sh", "Shaders/Skyfragment.sh", "SkyBox");

	GLfloat Cube_vertices[] =
	{
		-m_width,   m_width,  m_width,
		-m_width,  -m_width,  m_width,
		 m_width,  -m_width,  m_width,
		 m_width,   m_width,  m_width,
		-m_width,   m_width, -m_width,
		-m_width,  -m_width, -m_width,
		 m_width,  -m_width, -m_width,
		 m_width,   m_width, -m_width
	};

	GLfloat Cube_Coordinate[] = 
	{
		0.0, -1.0,
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0
	};


	GLushort Cube_indices[] = {
	  0, 1, 2, 3,
	  3, 2, 6, 7,
	  7, 6, 5, 4,
	  4, 5, 1, 0,
	  0, 3, 7, 4,
	  1, 2, 6, 5,
	};
   
   //glGenBuffersARB(1, &TextureCoorbuffer);
   //glBindBufferARB(GL_ARRAY_BUFFER,TextureCoorbuffer);
   //glBufferDataARB(GL_ARRAY_BUFFER, sizeof(Cube_Coordinate), Cube_Coordinate, GL_STATIC_DRAW);

   glGenBuffersARB(1, &vetexbuffer);
   glBindBufferARB(GL_ARRAY_BUFFER, vetexbuffer);
   glBufferDataARB(GL_ARRAY_BUFFER,sizeof(Cube_vertices), Cube_vertices, GL_STATIC_DRAW);


   glGenBuffersARB(1, &elementbuffer);
   glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
   glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cube_indices),  Cube_indices, GL_STATIC_DRAW);


   GLuint vertex = glGetAttribLocation(ResourceManager::Instance()->GetShaderProram("SkyBox"), "vertex");
   //glEnableVertexAttribArray(vertex);
   //glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void SkyBox::Draw()
{
	UpdateSkyBoxPos();
	((OpenGL *)RederingHandle->GetRenderHandle())->DrawSkyBox(m_position, vetexbuffer, elementbuffer, TextureCoorbuffer, texture);
}

void SkyBox::SetBufferRef()
{
	((OpenGL *)RederingHandle->GetRenderHandle())->AddRefToBuffer(m_objectID, this);
}

void SkyBox::Destory()
{
	((OpenGL *)RederingHandle->GetRenderHandle())->EraseRefFromBuffer(m_objectID);
}

void SkyBox::Update(double deltaTime)
{
}