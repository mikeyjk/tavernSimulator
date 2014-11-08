#include "Geometry.h"
#include "OpenGL.h"
#include "RenderingEngine.h"
#include "World.h"
#include <iostream>
//#include "boost\

Geometry::Geometry(RenderingEngine  * Ref, Vec3 pos, float rotX, float rotY, string model, string texture, bool bound, float transparency, std::vector<Affordance> affordances,float weight)
	:GameObject(Ref, pos, rotX, rotY, model, texture, bound, trans,weight)
{
	type = gameObjectType::geometry;

	setAffordances(affordances);
	//Add affordances here...
}

void Geometry::Destory(void)
{
	((OpenGL *)RederingHandle->GetRenderHandle())->EraseRefFromBuffer(m_objectID);
}

void Geometry::Draw()
{
	
	if(isBounding)
	{
		GLfloat mat[16];
		Bounding->body->getGLTransform(mat);
		m_position.X = Bounding->body->getPosition().x;
		m_position.Y = Bounding->body->getPosition().y;
		m_position.Z = Bounding->body->getPosition().z;
		glPushMatrix();
		glMultMatrixf(mat);
		RederingHandle->DrawModel(model, texture, trans, Vec3(0,0,0), Vec3(0,0,0), Vec3(1, 1, 1));
		glPopMatrix();
	}
	else
	{
		RederingHandle->DrawModel(model, texture, trans, m_position, m_rotation, Vec3(1, 1, 1));
	}
}

void Geometry::Update(double deltaTime)
{
	//std::cout << position.getX() << ", " << position.getY() << ", " << position.getZ() << std::endl;
}

void Geometry::SetBufferRef()
{
	((OpenGL *)RederingHandle->GetRenderHandle())->AddRefToBuffer(m_objectID, this);
}