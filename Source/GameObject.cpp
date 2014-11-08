#include "GameObject.h"

GameObject::GameObject()
{
	m_position = Vec3(0, 0, 0);
	m_rotation = Vec3(0, 0, 0);
	model = "";
	texture = "";
	trans = 1.0;
	RederingHandle = RederingHandle = RenderingEngine::Instance();
	IdGen = IdGenerator::Instance();
	m_objectID = IdGen->GetID();
	Bounding = nullptr;
}

GameObject::GameObject(RenderingEngine* ref, Vec3 pos, float rotX, float rotY, 
					   std::string model, std::string texture, bool Isbound, float transparency, float weight)
{
	RederingHandle = ref;
	IdGen = IdGenerator::Instance();
	m_objectID = IdGen->GetID();

	m_position = pos;
	m_rotation.X = rotX;
	m_rotation.Y = rotY;
	trans = transparency;

	if(model != "" && model != "NULL")
	{
		Vec3* min = new Vec3(10000000,10000000,10000000);
		Vec3* max = new Vec3(0,0,0);
		std::string modelPath = "Models/" + model + ".obj";
		ResourceManager::Instance()->addModel(modelPath, model, min, max);
		isBounding = Isbound;
		if(Isbound)
		{
			glm::vec3 glmPos(pos.X, pos.Y, pos.Z);
			if(weight <= 0)
				weight = 10;
			
			Bounding = new Bbox(  (max->getX() - min->getX())/2,  
				                  (max->getY() - min->getY())/2,  
								  (max->getZ() - min->getZ())/2,
								  glmPos,
								  weight,
								  cyclone::collisionType::NORMAL,
								  0.0001,0.00001,0.0001);

		  Bounding->myGameObject = this;

		  PhysicEngine::Instance()->WorldSimu->AddBBox(Bounding);
			
		}
		this->model = model;
	}

	if(texture != "" && texture != "NULL")
	{
		std::string texPath = "Textures/" + texture + ".png";
		char* tex = strdup(texPath.c_str());
		ResourceManager::Instance()->addTexture(tex, texture);
		this->texture = texture;
	}
}

GameObject::~GameObject()
{
	RederingHandle = nullptr;
	IdGen = nullptr;
}

void GameObject::setPosition(Vec3 pos)
{
	m_position = pos;
}

void GameObject::setPosition(float x, float y, float z)
{
	m_position.setX(x);
	m_position.setY(y);
	m_position.setZ(z);
}

Vec3 GameObject::getPos()
{
	return m_position;
}

void GameObject::setRotation(float rotX, float rotY, float rotZ)
{
	m_rotation.X = rotX;
	m_rotation.Y = rotY;
	m_rotation.Z = rotZ;
	Bounding->body->setRotation(rotX, rotY, rotZ);
}

float GameObject::getRotationX()
{
	return(m_rotation.X);
}

float GameObject::getRotationY()
{
	return(m_rotation.Y);
}

Vec3 GameObject::getRotation()
{
	return(m_rotation);
}

void GameObject::setTexture(std::string tex)
{
	texture = tex;
}

void GameObject::setModel(std::string mod)
{
	model = mod;
}

std::string GameObject::getTexture()
{
	return texture;
}

std::string GameObject::getModel()
{
	return model;
}

// assumes that the gameObject has a model
void GameObject::setBBox()
{
	// ModelManager::instance()->getModel
	// Bounding = new Bbox(w, h, d);
}

void GameObject::setAffordances(std::vector<Affordance> affordances)
{
	m_affordances = affordances;
}

vector<Affordance> GameObject::getAffordances() const
{
	return(m_affordances);
}

void GameObject::addAffordance(const Affordance newAffordance)
{
	m_affordances.push_back(newAffordance);
}