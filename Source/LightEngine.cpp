#include "LightEngine.h"
#include <ostream>

LightEngine::LightEngine()
{
	lightCount = 0;
}

LightEngine * LightEngine::Instance()
{
	static LightEngine Instance;
	return &Instance;
}

void LightEngine::Initialise()
{
	glEnable(GL_LIGHTING);
	GLfloat global_ambient[] = {0.3f, 0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glShadeModel(GL_SMOOTH);

	for(int i=0;i<sizeof(lightArray);i++)
	{
		lightArray[i].clear = true;
	}


	//Setting up these lights is temp in here... would be usually done through scripting
	Vec3 spec(0.66f, 0.33f, 0.0f);
	Vec3 dir(0.0f, -1.0f, 0.0f);
	Vec3 pos(-135.0, 70.0f, 0.0f);
	createLight(spec, spec, spec, pos, dir, 60.0f);

	spec.setX(0.33f);
	spec.setY(0.66f);
	spec.setZ(0.0f);
	pos.setX(175);
	createLight(spec, spec, spec, pos, dir, 60.0f);

	pos.setZ(-175);
	createLight(spec, spec, spec, pos, dir, 60.0f);

	spec.setX(0.33f);
	spec.setY(0.0f);
	spec.setZ(0.66f);
	pos.setX(420);
	createLight(spec, spec, spec, pos, dir, 60.0f);

	pos.setZ(0);
	createLight(spec, spec, spec, pos, dir, 60.0f);
	

}

int LightEngine::createLight(Vec3 ambient, Vec3 specular, Vec3 Diffuse, Vec3 position, Vec3 Direction, GLfloat cutoff)
{
	int firstFreeLight = -1;
	for(int i=0;i<sizeof(lightArray);i++)
	{
		if(lightArray[i].clear == true)
		{
			firstFreeLight = i;
			break;
		}
	}

	GLenum lightNumber = getLightGlenum(firstFreeLight);

	if(lightNumber != -1 && firstFreeLight < 8)
	{
		lightArray[firstFreeLight].specular[0] = specular.getX();
		lightArray[firstFreeLight].specular[1] = specular.getY();
		lightArray[firstFreeLight].specular[2] = specular.getZ();
		lightArray[firstFreeLight].specular[3] = 1.0f;


		lightArray[firstFreeLight].ambient[0] = ambient.getX();
		lightArray[firstFreeLight].ambient[1] = ambient.getY();
		lightArray[firstFreeLight].ambient[2] = ambient.getZ();
		lightArray[firstFreeLight].ambient[3] = 1.0f;

		lightArray[firstFreeLight].diffuse[0] = Diffuse.getX();
		lightArray[firstFreeLight].diffuse[1] = Diffuse.getY();
		lightArray[firstFreeLight].diffuse[2] = Diffuse.getZ();
		lightArray[firstFreeLight].diffuse[3] = 1.0f;

		lightArray[firstFreeLight].position[0] = position.getX();
		lightArray[firstFreeLight].position[1] = position.getY();
		lightArray[firstFreeLight].position[2] = position.getZ();
		lightArray[firstFreeLight].position[3] = 1.0f;

		lightArray[firstFreeLight].direction[0] = Direction.getX();
		lightArray[firstFreeLight].direction[1] = Direction.getY();
		lightArray[firstFreeLight].direction[2] = Direction.getZ();

		lightArray[firstFreeLight].cutoff = cutoff;

		lightArray[firstFreeLight].active = true;
		lightArray[firstFreeLight].clear = false;
		lightArray[firstFreeLight].lightNumber = lightNumber;

		//lightCount ++;
		return firstFreeLight;
	}
	return -1;
}

GLenum LightEngine::getLightGlenum(int number)
{
	switch(number)
		{
		case 0:
			return GL_LIGHT0;
			break;
		case 1:
			return GL_LIGHT1;
			break;
		case 2:
			return GL_LIGHT2;
			break;
		case 3:
			return GL_LIGHT3;
			break;
		case 4:
			return GL_LIGHT4;
			break;
		case 5:
			return GL_LIGHT5;
			break;
		case 6:
			return GL_LIGHT6;
			break;
		case 7:
			return GL_LIGHT7;
			break;
		default:
			return -1;
			break;
		}
}

void LightEngine::drawLights()
{
	//test light source
	int count = 0;
	for each(lightParams light in lightArray)
	{
		if(light.clear == false && light.active == true)
		{
			//lighting effects? .. test
			lightArray[count].specular[0] += 0.005;
			if(lightArray[count].specular[0] > 1)
				lightArray[count].specular[0] = 0;

			lightArray[count].specular[1] += 0.005;
			if(lightArray[count].specular[1] > 1)
				lightArray[count].specular[1] = 0;

			lightArray[count].specular[2] += 0.005;
			if(lightArray[count].specular[2] > 1)
				lightArray[count].specular[2] = 0;
			//end lighting effects

			glLightfv(light.lightNumber, GL_SPECULAR, light.specular);
			glLightfv(light.lightNumber, GL_AMBIENT, light.specular);
			glLightfv(light.lightNumber, GL_DIFFUSE, light.specular);
			glLightfv(light.lightNumber, GL_POSITION, light.position);
			glLightf(light.lightNumber, GL_SPOT_CUTOFF, light.cutoff);
			glLightfv(light.lightNumber, GL_SPOT_DIRECTION, light.direction);

			glEnable(light.lightNumber);

			//For testing purposes.
			glPushMatrix();
			glTranslatef(light.position[0], light.position[1], light.position[2]);
			glutSolidSphere(1, 10, 10);
			glPopMatrix();
		}
		count++;
	}
}




