#pragma once
#include "GameObject.h"
#include "RenderingEngine.h"
#include "Vec3.h"
#include "IdGenerator.h"
#include "ResourceManager.h"



class SkyBox : public GameObject
{
public:
	SkyBox(RenderingEngine  * Ref, Vec3 pos, string _texture);
	~SkyBox(void);

	void Draw();
	void SetBufferRef();
	void Destory();
	void Update(double deltaTime);

	void SetAttributes(float width);



private:

	float m_width;
	float m_height;
	


	GLuint elementbuffer;
	GLuint vetexbuffer;
	GLuint TextureCoorbuffer;

private:

	void GenerateBuffer();
	void UpdateSkyBoxPos();
};

