//
//  ResourceManager.h
//  ResourceManager
//
//  Created by Robert Herne on 30/03/14.
//  Last Modified on 04/04/14.
//

#pragma once

#ifndef __ResourceManager__ResourceManager__
#define __ResourceManager__ResourceManager__

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"

/**
 * @class Resource Manager
 * @brief Encapsulates the model, sound and texture managers inside a unified resource manager.
 *
 * @author Robert Herne
 * @date 04/04/14
 * @version 1
 *
 * @bug None
 */

class ResourceManager
{
public:  
    

	static ResourceManager* Instance();

	/**
     * @brief Adds a texture to the texture manager by the file's path, which will become known to the texture manager by the passed name.
     *
     * @param char * Path, string Name
	 *
	 * @pre None.
	 *
	 * @post The texture is added to the texture manager and is known by the manager by the name given.
     */
	void addTexture(char * Path, string Name);

	/**
     * @brief Adds a precreated texture to the texture manager, which will become known to the texture manager by the passed name.
     *
     * @param GLuint tex, string Name
	 *
	 * @pre None.
	 *
	 * @post The texture is added to the texture manager and is known by the manager by the name given.
     */
	void addCreatedTexture(GLuint tex, string Name);

	/**
     * @brief Gets the texture from the texture manager with the matching name.
     *
     * @param string Name
	 *
	 * @pre A texture with a name matching the passed name must exist.
	 *
	 * @post The texture with the matching name is returned.
     */
	GLuint getTexture(string Name);

	/**
     * @brief Adds a model to the model manager by the file's path, which will become known to the model manager by the passed name.
     *
     * @param string Path, string Name
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The model is added into the model manager and is known by the model manager by the name given.
     */
	void addModel(string Path, string Name, Vec3 *min, Vec3 *max);

	/**
     * @brief Draws a model to the screen.
     *
     * @param string Name, string TName,  float transparency , Vec3 transition, float rotation
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The model is drawn.
     */
	void drawModel(string Name, string TName,  float transparency , Vec3 transition, Vec3 rotation);

	void drawModel(string Name, string TName,  float transparency ,Vec3 transition, Vec3 rotation, Vec3 scale);

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


	void GenerateShader(char * VS, char * PS, string name);

    GLuint GetShaderProram(string name);

	void addCubeTexture(char * front, char * back, char * top, char * bottom, char * left, char * right, string name);

private:
	ResourceManager(){}		// Creates a resource manager object.
	~ResourceManager(){}	// Deletes the resource manager.
};

#endif /* defined(__ResourceManager__ResourceManager__) */
