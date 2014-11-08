#include "Bbox.h"
#include "GL\freeglut.h"

Bbox::Bbox(float half_x, float half_y, float half_z, glm::vec3 position, float mass, cyclone::collisionType type,double x, double y, double z)
{
	this->width  = half_x;
	this->height = half_y;
	this->Depth  = half_z;

	for(int i = 0; i < 8; i++)
	{
		points.push_back(glm::vec3(0,0,0));
	}

	this->type = type;
	//this->body->type = type;
	this->halfSize = cyclone::Vector3(half_x,half_y,half_z);
	this->body = new cyclone::RigidBody(); //Create RegidBody;
	this->body->setPosition(position.x, position.y,position.z);

	double c1 = cos(x/2);
    double s1 = sin(x/2);
    double c2 = cos(y/2);
    double s2 = sin(y/2);
    double c3 = cos(z/2);
    double s3 = sin(z/2);
	float w = sqrt(1.0 + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3)/2.0;
	double w4 = (4.0 * w);
	x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
    y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
    z = (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;


	this->body->setOrientation(1,x,y,z);
	this->body->setVelocity(0,0,0);
	this->body->setRotation(0,0,0);
	this->body->setMass(mass);
	this->body->setDamping(0.9f,0.9f);

	cyclone::Matrix3 it;
	it.setBlockInertiaTensor(halfSize, mass);
	//Set inversed InertialTensor
	this->body->setInertiaTensor(it);
	//Set Transform Matrix by quaternion
	//Rotate intertial tersor
	this->body->calculateDerivedData();
	//times offset
	this->calculateInternals();
	
	if(type == cyclone::collisionType::STATIC)
	this->body->setAcceleration(cyclone::Vector3::NONE);
	else
	this->body->setAcceleration(cyclone::Vector3::GRAVITY);


	this->body->setAwake(true);
	this->body->setCanSleep(true);

	glm::vec3 temp = glm::vec3(0,0,0);

	Update(temp);
}

void Bbox::Update(glm::vec3 pos)
{
	 
	 LTB = glm::vec3(pos.x - width, pos.y + height, pos.z - Depth);
	 points[0] = LTB;

	 LTF = glm::vec3(pos.x - width, pos.y + height, pos.z + Depth);
	 points[1] = LTF;
	 
	 LDB = glm::vec3(pos.x - width, pos.y - height, pos.z - Depth);
	 points[2] = LDB;

	 LDF = glm::vec3(pos.x - width, pos.y - height, pos.z + Depth);
	 points[3] = LDF;

	 RTB = glm::vec3(pos.x + width, pos.y + height, pos.z - Depth);
	 points[4] = RTB;

	 RTF = glm::vec3(pos.x + width, pos.y + height, pos.z + Depth);
	 points[5] = RTF;
	 
	 RDB = glm::vec3(pos.x + width, pos.y - height, pos.z - Depth);
	 points[6] = RDB;

	 RDF = glm::vec3(pos.x + width, pos.y - height, pos.z + Depth);
	 points[7] = RDF;
	 
}

void Bbox::Draw()
{
	
	GLfloat mat[16];
    body->getGLTransform(mat);
    if (body->getAwake()) glColor3f(1.0f,0.7f,0.7f);
    else glColor3f(0.7f,0.7f,1.0f);


	glPushMatrix();
	glMultMatrixf(mat);
    //glScalef(halfSize.x*2, halfSize.y*2, halfSize.z*2);
	//glutWireCube(1.0f);
	 
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(LTB.x, LTB.y, LTB.z);
	glVertex3f(LTF.x, LTF.y, LTF.z);
	glVertex3f(LTB.x, LTB.y, LTB.z);
	glVertex3f(RTB.x, RTB.y, RTB.z);
	glVertex3f(LTB.x, LTB.y, LTB.z);
	glVertex3f(LDB.x, LDB.y, LDB.z);
	glVertex3f(RTB.x, RTB.y, RTB.z);
	glVertex3f(RDB.x, RDB.y, RDB.z);
	glVertex3f(RTB.x, RTB.y, RTB.z);
	glVertex3f(RTF.x, RTF.y, RTF.z);
	glVertex3f(RTB.x, RTB.y, RTB.z);
	glVertex3f(RTF.x, RTF.y, RTF.z);
	glVertex3f(RDB.x, RDB.y, RDB.z);
	glVertex3f(LDB.x, LDB.y, LDB.z);
	glVertex3f(RTF.x, RTF.y, RTF.z);
	glVertex3f(LTF.x, LTF.y, LTF.z);
	glVertex3f(LDF.x, LDF.y, LDF.z);
	glVertex3f(LDB.x, LDB.y, LDB.z);
	glVertex3f(LDF.x, LDF.y, LDF.z);
	glVertex3f(LTF.x, LTF.y, LTF.z);
	glVertex3f(LDF.x, LDF.y, LDF.z);
	glVertex3f(RDF.x, RDF.y, RDF.z);
	glVertex3f(RDF.x, RDF.y, RDF.z);
	glVertex3f(RTF.x, RTF.y, RTF.z);
	glVertex3f(RDF.x, RDF.y, RDF.z);
    glVertex3f(RDB.x, RDB.y, RDB.z);
	glEnd();
	
	

	glPopMatrix();
}


Bbox::~Bbox(void)
{
}
