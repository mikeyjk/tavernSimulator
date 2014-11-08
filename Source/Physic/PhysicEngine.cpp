#include "PhysicEngine.h"

PhysicEngine * PhysicEngine::Instance()
{
	static PhysicEngine instance;
	return &instance;
}

void PhysicEngine::loadAssets()
{
	vector<vector<string>> m_spheres;
	vector<vector<string>> m_boxes;

	string assetLine; // store each line of the asset file
	ifstream fileData; // file stream to asset file

	try // attempt file I/O
	{
		fileData.open(m_assetFile); // open the file stream
	}
	catch(const std::exception &err) // catch all
	{
		cout << "Error: " << err.what() << endl;
	}

	// verify file stream was opened
	if(fileData.fail())
	{
		cout << "Error: Unable to open asset file! (" << m_assetFile << ")." << endl;
	}
	else // file stream opened successfully
	{
		// while getline() is able to retrieve a value
		while(getline(fileData, assetLine))
		{
			trim(assetLine); // trim whitespace at beginning/end

			// if not a comment / not empty
			if(!assetLine.empty() && assetLine.at(0) != '#')
			{

				if(find_first(assetLine, "Sphere:"))
				{
					vector<string> sphere;
					vector<string> tokens;

					split(tokens, assetLine, is_any_of(", "), token_compress_on);

					for(auto itr : tokens) // for the tokens
					{
						try
						{
 							if(!find_first(itr, "Sphere:"))
							{
								trim(itr);
								sphere.emplace(sphere.cend(), itr);
							}
						}
						catch(bad_lexical_cast &) {}
					}

					// store entity in vector
					m_spheres.emplace(m_spheres.cend(), sphere);
				}

				if(find_first(assetLine, "Box:"))
				{
					vector<string> box;
					vector<string> tokens;

					split(tokens, assetLine, is_any_of(", "), token_compress_on);

					for(auto itr : tokens)
					{
						try
						{
 							if(!find_first(itr, "Box:"))
							{
								trim(itr);

								box.emplace(box.cend(), itr);
							}
						}
						catch(bad_lexical_cast &) {}
					}

					// store entity in vector
					m_boxes.emplace(m_boxes.cend(), box);
				}
			}
		}
	}

	// SPHERE
	for(auto itr = m_spheres.cbegin(); itr != m_spheres.cend(); ++itr)
	{
		try
		{
			cyclone::collisionType colType;

			if(find_first((*itr)[5], "normal"))
			{
				colType = cyclone::collisionType::NORMAL;
			}

			if(find_first((*itr)[5], "static"))
			{
				colType = cyclone::collisionType::STATIC;
			}

			WorldSimu->AddBSphere(lexical_cast<float>((*itr)[0]),
								  glm::vec3(lexical_cast<float>((*itr)[1]),
										    lexical_cast<float>((*itr)[2]),
										    lexical_cast<float>((*itr)[3])),
								  lexical_cast<float>((*itr)[4]),
								  colType);
		}
		catch(bad_lexical_cast &)
		{
			cout << "Error converting asset data. Likely unanticipated input value." << endl;
		}
	}

	// BOXES
	for(auto itr = m_boxes.cbegin(); itr != m_boxes.cend(); ++itr)
	{
		try
		{
			cyclone::collisionType colType;

			if(find_first((*itr)[7], "normal"))
			{
				colType = cyclone::collisionType::NORMAL;
			}

			if(find_first((*itr)[7], "static"))
			{
				colType = cyclone::collisionType::STATIC;
			}

			
			WorldSimu->AddBBox(lexical_cast<float>((*itr)[0]),
							   lexical_cast<float>((*itr)[1]),
							   lexical_cast<float>((*itr)[2]),
								  glm::vec3(lexical_cast<float>((*itr)[3]),
										    lexical_cast<float>((*itr)[4]),
										    lexical_cast<float>((*itr)[5])),
								  lexical_cast<float>((*itr)[6]),
								  colType,
								  lexical_cast<float>((*itr)[8]),
								  lexical_cast<float>((*itr)[9]),
								  lexical_cast<float>((*itr)[10]));
		}
		catch(bad_lexical_cast &)
		{
			cout << "Error converting asset data. Likely unanticipated input value." << endl;
		}
	}

	// fileData.close() // close file stream, automatic upon destruction
}

PhysicEngine::PhysicEngine(void)
{
	m_assetFile = "ScriptData/PhysicsObjects.txt";
	WorldSimu = PhysicalWorldSimulation::Instance();
	WorldSimu->init();

	float wallweight = 99999999999999999;
	loadAssets();
	renderBBoxes = false;
}

PhysicEngine::~PhysicEngine(void)
{
}

/**
  * Add physics objects from file.
  */
void PhysicEngine::addObjects()
{

}

void PhysicEngine::Update(double deltaTime)
{
	float dt = 60/ 1000.0f;
	float maxPossible_dt = 0.002;

	int steptimes = (int)(dt/maxPossible_dt) + 1;

	if(steptimes != 0)
	{
		dt = dt / steptimes;
	}

	for(int a =0; a < steptimes; ++a)
	{

		if(WorldSimu != nullptr)
			WorldSimu->Update(dt);
	}
}

void PhysicEngine::Draw()
{
	if(WorldSimu != nullptr)
	{
		if(renderBBoxes)
			WorldSimu->Display();

	}
}
