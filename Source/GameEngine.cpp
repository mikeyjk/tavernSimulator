#include "GameEngine.h"
#include "RNG.h"

// default constructor
GameEngine::GameEngine()
{
	myRenderingEngine = RenderingEngine::Instance();
	myWorld = World::Instance();
	myMenuSystem = MenuSystem::Instance();
	myControlSystem = ControlSystem::Instance(); 
	EngineInstance = this;
	m_assetFile = "ScriptData/AssetList.txt";
	EngineTime = new Timer();
	RNG::Instance()->randomSeed();
}

// destructor
GameEngine::~GameEngine()
{
}

void GameEngine::start(char* name, int& argc, char** argv, int Windowswidth, int WindowsHeight, char* Gamename)
{
	myRenderingEngine->CreateRenderAPI(name);
	// implementation independent
	m_soundManager = new SoundManager();
	//m_soundManager->playSound("Sounds/perth artists song 7 for soundcloud.mp3");

	// opengl dependent implementation
	// the sequence of calls in this function is important
	if(find_first(name, "OpenGL"))
	{
		OpenGL * Open = static_cast<OpenGL*>(myRenderingEngine->GetRenderHandle());
		Open->Init(argc,argv,Windowswidth,WindowsHeight,Gamename);
		Open->SetCallBackProcess(&update);

		myInputEngine = InputEngine::Instance();
		myInputEngine->initInputControl("OpenGL");
		myInputEngine->setMouseFixed(false);

		myControlSystem->init();

		LightEngine::Instance()->Initialise();

		loadAssets(); // load game resources
		myMenuSystem->MenuInit();
		Open->loop();

	} // direct x dependent implementation 
	else if(find_first(name, "DirectX")) 
	{
	}
	else // unsupported
	{
		throw std::exception("Unsupported Graphics Interface!");
	}
	
}

/**
	* @Function loadAssets()
	* @Summary loads models/object data from file.
	* I'm not sure if I should make these vectors there own classes?
	* I'm just mimicking the way we currently load assets
	* not 100% if it is the best design choice though
	*
	// store vector data into actual game objects
	// TODO: Should I do this instead of storing in vectors?
	// this seemed better at the time
	*
	// TODO: filthy hard coded value, this should be set somewhere else
*/
void GameEngine::loadAssets()
{
	std::string assetLine; // store each line of the asset file
	std::ifstream fileData; // file stream to asset file

	std::vector<std::string> musicVec; // vector of bg sounds
	std::vector<std::string> cubeTexVec; // vector of cube textures (currently engine only supports 1)

	std::vector<std::vector<std::string>> entityVec; // vector of game entities (vector of strings)
	std::vector<std::vector<std::string>> affordVec; 
	std::vector<std::vector<std::string>> traitVec; 
	std::vector<std::vector<Affordance>> entityAffordances;

	bool skybox = false; // false by default, with no skybox

	try // attempt file I/O
	{
		fileData.open(m_assetFile); // open the file stream
	}
	catch(const std::exception &err) // catch all
	{
		std::cout << "Error: " << err.what() << std::endl;
	}

	// verify file stream was opened
	if(fileData.fail())
	{
		std::cout << "Error: Unable to open asset file! (" << m_assetFile << ")." << std::endl;
	}
	else // file stream opened successfully
	{
		// store file data in temporary vectors

		// while getline() is able to retrieve a value
		while(std::getline(fileData, assetLine))
		{
			trim(assetLine); // trim whitespace at beginning/end

			// if not a comment / not empty
			if(!assetLine.empty() && assetLine.at(0) != '#')
			{
				// store skybox info
				if(find_first(assetLine, "Skybox:"))
				{
					vector<std::string> tokens;

					split(tokens, assetLine, is_any_of(", "), token_compress_on);
				
					for(auto& token : tokens)
					{
						try
						{
							if(find_first(token, "true") ||  find_first(token, "True") || 
							   find_first(token, "TRUE"))
							{
								skybox = true;
							}
						} 
						catch(const std::exception &err) // catch all
						{
							std::cout << "Error: " << err.what() << std::endl;
						}
					}
				}	

				// store cube texture info (for skybox)
				// don't check for skybox == true in case we put 
				// the cube textures above in the document
				if(find_first(assetLine, "CubeTexture:"))
				{
					vector<std::string> tokens;

					split(tokens, assetLine, is_any_of(", "), token_compress_on);
				
					for(auto& token : tokens)
					{
						try
						{
							if(!find_first(token, "CubeTexture:"))
							{
								cubeTexVec.emplace(cubeTexVec.cend(), token);
							}
						} 
						catch(const std::exception &err) // catch all
						{
							std::cout << "Error: " << err.what() << std::endl;
						}
					}
				}

				// attempt to store entities
				if(find_first(assetLine, "Entity:"))
				{
					std::vector<std::string> tokens;
					std::vector<std::string> tempEntity;
					std::vector<std::string> tempAffordance;
					std::vector<std::string> tempTrait;

					split(tokens, assetLine, is_any_of(", "), token_compress_on);
				
					for(auto& token : tokens)
					{
						try
						{
 							if(!find_first(token, "Entity:"))
							{
								if(find_first(token, "(")) // denotes affordance
								{
									tempAffordance.push_back(token);
								}
								else if(find_first(token, "::")) // denotes trait
								{
									tempTrait.push_back(token);
								}
								else
								{
									tempEntity.push_back(token);
								}
							}
						} 
						catch(const std::exception& ex) 
						{
							std::cout << "Error: " << ex.what() << std::endl;
						}
					}

					entityVec.emplace(entityVec.cend(), tempEntity); // store vector of strings for entity
					affordVec.emplace(affordVec.cend(), tempAffordance); // store vector of strings for affordance
					traitVec.emplace(traitVec.cend(), tempTrait); // store vector of strings for traits
				}		
			}
		}
	}

	// if the cube textures have the right amount of textures
	if(!cubeTexVec.empty() && cubeTexVec.size() == 7)
	{
		ResourceManager::Instance()->addCubeTexture
		(
			const_cast<char*>(cubeTexVec[0].c_str()), 
			const_cast<char*>(cubeTexVec[1].c_str()), 
			const_cast<char*>(cubeTexVec[2].c_str()), 
			const_cast<char*>(cubeTexVec[3].c_str()), 
			const_cast<char*>(cubeTexVec[4].c_str()),
			const_cast<char*>(cubeTexVec[5].c_str()), 
			const_cast<char*>(cubeTexVec[6].c_str())
		);
	}
	else
	{
		std::cout << "Error: Incorrect amount of skybox textures (" 
			<< cubeTexVec.size() << ")." << std::endl;
	}

	// now we want to populate the affordance and trait vectors for addEntity
	// they should be the exact same size as the entity vector

	if(entityVec.size() != affordVec.size() || entityVec.size() != traitVec.size())
	{
		throw "error, entity vector should be of the same size as the affordance \
			  and trait vector.";
		exit(-1);
	}

	// populate vector of affordances
	for(auto& vec : affordVec)
	{
		std::vector<Affordance> tempAffordance;

		for(auto& affordance : vec)
		{
			std::vector<std::string> descr;
			std::vector<std::string> val;

			// store tag description
			split(descr, affordance, is_any_of("( "), token_compress_on);
			Affordance temp;
			temp.setTag(descr[0]);

			// store tag value
			split(val, descr[1], is_any_of(") "), token_compress_on);
			temp.setValue(lexical_cast<float>(val[0]));

			tempAffordance.push_back(temp);
		}

		entityAffordances.push_back(tempAffordance);
	}

	for(auto itr = entityVec.cbegin(); itr != entityVec.cend(); ++itr)
	{
		try // catch boost cast errors
		{
			// couldn't work out legit boost bool casting :(
			bool boolVal = false;
			if(find_first((*itr)[8], "true")) { boolVal = true; }
			if(find_first((*itr)[8], "TRUE")) { boolVal = true; }
			if(find_first((*itr)[8], "True")) { boolVal = true; }

			myWorld->AddEntity
			(
				(*itr)[0].c_str(), // string name
				Vec3(lexical_cast<float>((*itr)[1]), // vec3 posx
				lexical_cast<float>((*itr)[2]), // vec3 posy
				lexical_cast<float>((*itr)[3])), // vec3 posz
				lexical_cast<float>((*itr)[4]), // float rotX
				lexical_cast<float>((*itr)[5]), // float rotY
				(*itr)[6].c_str(), // string model
				(*itr)[7].c_str(),  // string texture
				boolVal, // bool bound
				lexical_cast<float>((*itr)[9]), // float transparency
				lexical_cast<float>((*itr)[10]), // float weight
				entityAffordances.at(std::distance(entityVec.cbegin(), itr)),
				traitVec.at(std::distance(entityVec.cbegin(), itr))
			);
		}
		catch(const std::exception &err) // catch all
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
	}

	if(skybox)
	{
		myWorld->AddSkybox();
	}

	// fileData.close() // close file stream, automatic upon destruction
}

void GameEngine::update(double deltaTime)
{
	EngineInstance->EngineTime->updateTime();
	deltaTime = EngineInstance->EngineTime->getDeltaTime();
	//game system update is the user of the engines update function
	if(EngineInstance->myControlSystem != NULL)
	{
		EngineInstance->myControlSystem->Update(deltaTime);
		if(EngineInstance->myWorld && EngineInstance->myControlSystem->getStatus() == GAME_RUN)
		{
			EngineInstance->myWorld->Update(deltaTime);
			if(PhysicEngine::Instance())
			{
				PhysicEngine::Instance()->Update(0);
			}
		}
	}

	//resets the press down, and release key arrays.
	if(EngineInstance->myInputEngine)
	{
		EngineInstance->myInputEngine->resetAllKeys();
	}
}

GameEngine* GameEngine::instance()
{
	static GameEngine temp;
	return(&temp);
}