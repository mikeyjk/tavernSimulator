#pragma once

//#include "GL\glew.h"
#include "GL\freeglut.h"
#include "GL\glext.h"
#include <string>
#include <map>
using std::string;
using std::map;

class ShaderManager
{
public:

	static ShaderManager* Instance();
	void GenerateShader(char * VS, char * PS, string name);
	GLuint GetShaderProram(string name);


private:


	char * Loadfile(char * path);
	map<string, GLuint> Programs;
	ShaderManager(void);
	~ShaderManager(void);
};

