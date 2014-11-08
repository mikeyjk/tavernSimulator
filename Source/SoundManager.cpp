//
//  SoundManager.cpp
//  SoundManager
//
//	Edit - 02/09/14 - Michael J. Kiernan
//
//  Created by Robert Herne on 10/04/14.
//  Last Modified on 10/04/14.
//
//  Code based on the "Sound.cpp" example provided with SFML.
//

#include "SoundManager.h"

void SoundManager::FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

SoundManager::SoundManager()
{
	// Create FMOD interface object
	result = FMOD::System_Create(&system);

	// Get number of sound cards result = system->getNumDrivers(&numDrivers);
	FMODErrorCheck(result);
 
	// No sound cards (disable sound)
	if (numDrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(result);
	}
	else
	{
		// Get the capabilities of the default (0) sound card
		result = system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODErrorCheck(result);
 
		// Set the speaker mode to match that in Control Panel
		result = system->setSpeakerMode(speakerMode);
		FMODErrorCheck(result);
	}

	// Initialise FMOD
	result = system->init(100, FMOD_INIT_NORMAL, 0);
}

void SoundManager::playSound(const string& filePath)
{
	system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &soundFile);
	system->playSound(FMOD_CHANNEL_FREE, soundFile, false, 0);
}
    // Attempt to load the sound file.
	/**
    soundBuffer.loadFromFile(filePath);

    // Create an instance of sound and play the requested sound.
    sf::Sound sound(soundBuffer);
    sound.play();*/


/**
void SoundManager::playBackgroundSound(const string& filePath)
{
    // This method uses the music class to stream large sound files from the disk,
    // instead of loading them into memory.

    // Attempt to load the background sound file.
    backgroundBuffer.openFromFile(filePath);

    // Set the background sound to loop.
    backgroundBuffer.setLoop(true);

    // Play the background sound.
    backgroundBuffer.play();
}

void SoundManager::stopBackgroundSound()
{
    backgroundBuffer.stop();
}*/