#include "BSphere.h"
#include "GL\freeglut.h"

BSphere::BSphere(float radius, glm::vec3 position, float mass, cyclone::collisionType type)
{
	this->radius = radius;
	this->type = type;
    //this->body->type = type;
	this->position = cyclone::Vector3(position.x, position.y, position.z);
	this->body = new cyclone::RigidBody();
	this->body->setMass(mass);
	this->body->setDamping(0.9f, 0.9f);
	cyclone::Matrix3 it;
	it.setSphereInertialTensor(mass,radius);
	this->body->setInertiaTensor(it);

	if(type == cyclone::collisionType::STATIC)
	this->body->setAcceleration(cyclone::Vector3::NONE);
	else
	this->body->setAcceleration(cyclone::Vector3::GRAVITY);


	this->body->setCanSleep(true);
    this->body->setAwake(true);

	this->body->setPosition(this->position);
	this->body->setOrientation(1,0,0,0);
	this->body->setVelocity(4.0f, 4.0f, 0.0f);
	this->body->setRotation(0,0,0);
	//Set Transform Matrix by quaternion
	//Rotate intertial tersor
	this->body->calculateDerivedData();
	this->calculateInternals();
}


BSphere::~BSphere(void)
{
}


void BSphere::Draw()
{

	GLfloat mat[16];
    body->getGLTransform(mat);

	//cyclone::Quaternion orientation;
	//body->getOrientation(&orientation);
	this->position =  body->getPosition();

    if (body->getAwake()) glColor3f(1.0f,0.7f,0.7f);
    else glColor3f(0.7f,0.7f,1.0f);
	//orientation.normalise();

	glPushMatrix();
	
	glMultMatrixf(mat);
	/*
	//convert quternion to euler
	float xangle = atan2f( 2 * (orientation.r * orientation.i  + orientation.j *  orientation.k), 1 - 2 *( orientation.i * orientation.i + orientation.j * orientation.j)); 
	float yangle = asinf( 2 * (orientation.r * orientation.j  - orientation.i *  orientation.k));
	float zangle = atan2f(2 * (orientation.r * orientation.k  + orientation.j *  orientation.i), 1 - 2 * ( orientation.j * orientation.j +  orientation.k * orientation.k));
	glRotatef( xangle , 1.0, 0.0, 0.0);
	glRotatef( yangle, 0.0, 1.0, 0.0);
	glRotatef( zangle, 0.0, 0.0, 1.0);
	*/
	//glTranslatef(this->position.x, this->position.y, this->position.z);

	glutWireSphere(this->radius,20,20);
	glPopMatrix();

}