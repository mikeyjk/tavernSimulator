#include "RederingFactory.h"


RederingFactory::RederingFactory(void)
{
}


RederingFactory::~RederingFactory(void)
{
}

I_Graphic * RederingFactory::CreateRender(string name)
{
	assert( (name == "OpenGL") || (name == "DirectX") || "RederingFactory::CreateRender");


	if(name == "OpenGL")
	{
		return new OpenGL();
	}
	else if(name == "DirectX")
	{
		return new DirectX();
	}
	else
	{
		throw std::exception("Unsupported Graphics Interface!");
	}
}
