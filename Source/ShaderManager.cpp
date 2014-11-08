#include "ShaderManager.h"
#include <fstream>



using namespace std;

ShaderManager* ShaderManager::Instance()
{
	static ShaderManager Instance;
	return &Instance;
}




ShaderManager::ShaderManager(void)
{
}


ShaderManager::~ShaderManager(void)
{
}

void ShaderManager::GenerateShader(char * VS, char * Frag, string name)
{

    map<string, GLuint>::iterator iterator;
	iterator = Programs.find(name);

	if(iterator == Programs.end())
	{
		GLuint glShaderV = glCreateShader(GL_VERTEX_SHADER);
	    GLuint glShaderF = glCreateShader(GL_FRAGMENT_SHADER);

	    const GLchar* vShaderSource = Loadfile(VS);
	    const GLchar* fShaderSource = Loadfile(Frag);

	    glShaderSource(glShaderV, 1, &vShaderSource, NULL);
	    glShaderSource(glShaderF, 1, &fShaderSource, NULL);

	    delete [] vShaderSource;
	    delete [] fShaderSource;

	   glCompileShader(glShaderV);
	   glCompileShader(glShaderF);

	   GLint result;
	   glGetShaderiv( glShaderV, GL_COMPILE_STATUS, &result );
       if( GL_FALSE == result )
       {
          fprintf( stderr, "Vertex shader compilation failed!\n" );
          GLint logLen;
          glGetShaderiv( glShaderV, GL_INFO_LOG_LENGTH, &logLen );
          if( logLen > 0 )
          {
                char * log = (char *)malloc(logLen);
				GLsizei written;
                glGetShaderInfoLog(glShaderV, logLen, &written, log);
                fprintf(stderr, "Shader log:\n%s", log);
                 free(log);
            }
         }

	   glGetShaderiv( glShaderF, GL_COMPILE_STATUS, &result );
       if( GL_FALSE == result )
       {
          fprintf( stderr, "Fragment shader compilation failed!\n" );
          GLint logLen;
          glGetShaderiv( glShaderF, GL_INFO_LOG_LENGTH, &logLen );
          if( logLen > 0 )
          {
                char * log = (char *)malloc(logLen);
				GLsizei written;
                glGetShaderInfoLog(glShaderF, logLen, &written, log);
                fprintf(stderr, "Shader log:\n%s", log);
                 free(log);
            }
         }

	   GLuint glProgram = glCreateProgram();

	   glAttachShader(glProgram, glShaderV);
	   glAttachShader(glProgram, glShaderF);

       glLinkProgram(glProgram);
     
	   Programs.insert(std::pair<string,GLuint>(name,glProgram));
	}

}

GLuint ShaderManager::GetShaderProram(string name)
{
	map<string, GLuint>::iterator iterator;
	iterator = Programs.find(name);

	if(iterator != Programs.end())
	{
		return(iterator->second);
	}
	else
	{
		return(-1);
	}
}

char * ShaderManager::Loadfile(char * path)
{
	char * data;
	int len;
	std::ifstream ifs(path, std::ios::in);
	ifs.seekg(0, std::ios::end);
	len = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	data = new char[len + 1];
	ifs.read(data, len);
	data[len] = 0;

	ifs.close();
	return data;
}