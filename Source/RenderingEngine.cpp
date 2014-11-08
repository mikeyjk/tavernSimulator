#include "RenderingEngine.h"



RenderingEngine* RenderingEngine::Instance()
{
	static RenderingEngine Instance;
	return &Instance;
}

RenderingEngine::RenderingEngine(void)
{
}


RenderingEngine::~RenderingEngine(void)
{
}

Camera * RenderingEngine::GetCamera()
{
	return ((OpenGL *)Handle)->GetCamera();
}


void RenderingEngine::CreateRenderAPI(string name)
{
	Handle = APIFactory.CreateRender(name);
}


I_Graphic * RenderingEngine::GetRenderHandle()
{
	return Handle;
}


void RenderingEngine::AddRefToBuffer(int Id, I_DrawableObject * Ref)
{
	((OpenGL *)Handle)->AddRefToBuffer(Id, Ref);
}


void RenderingEngine::EraseRefFromBuffer(unsigned int Id)
{
	((OpenGL *)Handle)->EraseRefFromBuffer(Id);
}

void RenderingEngine::RenderOverlay(float start_x, float start_y,float w, float h,string name)
{
	((OpenGL *)Handle)->RenderOverlay(start_x, start_y, w, h, name);
}

void RenderingEngine::DrawModel(string ModelName, string TextureName, float transparency, Vec3 transition, Vec3 rotation)
{
	((OpenGL *)Handle)->DrawModel(ModelName, TextureName,transparency, transition, rotation);
}

void RenderingEngine::DrawModel(string ModelName, string TextureName, float transparency, Vec3 transition, Vec3 rotation, Vec3 scale)
{
	((OpenGL *)Handle)->DrawModel(ModelName, TextureName,transparency, transition, rotation, scale);
}