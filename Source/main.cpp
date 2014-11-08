#include "GameEngine.h"

#define OPENGL
#ifdef OPENGL
#endif

#ifdef DX
#endif // DX

static const int windowWidth = 800;
static const int windowHeight = 600;
static char* windowTitle = "ICT312";

static GameEngine * engine = GameEngine::instance();

int main(int argc, char** argv)
{
	#ifdef OPENGL
		engine->start("OpenGL", argc, argv, windowWidth, windowHeight, windowTitle);
	#endif // OPENGL

	#ifdef DX
		// Direct X Logic
	#endif // DX
	return(EXIT_SUCCESS);
}