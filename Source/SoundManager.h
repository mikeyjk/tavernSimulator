//
//  SoundManager.h
//  SoundManager
//
//  Edit 02/09/2014 - Michael J. Kiernan
//	SFML removed in lieu of FMOD.
//
//  Version 2 created by Robert Herne on 10/04/14.
//  Last Modified on 10/04/14.
//

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

#include <iostream>
#include <string>

using namespace std;

/**
 * @class Sound Manager
 * @brief Plays sounds used by the game.
 *
 * @author Robert Herne
 * @date 10/04/14
 * @version 2
 *
 * @bug None
 */

class SoundManager
{
public:

    SoundManager();            // Sound Manager default constructor.

    ~SoundManager(){};         // Sound Manager destructor.

    /**
     * @brief Loads a sound from a file and plays it.
     *
     * @param const string& filePath
     *
     * @pre None.
     *
     * @post The sound is played once.
     */
    void playSound(const string& filePath);

    /**
     * @brief Streams a background sound from a file and loops it.
     *
     * @param const string& filePath
     *
     * @pre None.
     *
     * @post The background is played and looped.
     */
    void playBackgroundSound(const string& filePath);

    /**
     * @brief Stops the playback of a background sound.
     *
     * @param const string& filePath
     *
     * @pre None.
     *
     * @post The background sound is stopped.
     */
    void stopBackgroundSound();

private:
    
	FMOD::System *system;
	FMOD_RESULT result;
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];
	FMOD::Sound* soundFile;

    //sf::SoundBuffer soundBuffer;    // Sound buffer.
    //sf::Music backgroundBuffer;      // Background sound buffer.

	void FMODErrorCheck(FMOD_RESULT result);
};

#endif // SOUNDMANAGER_H