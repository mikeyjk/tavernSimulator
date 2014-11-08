//
//  TextureManager.h
//  TextureManager
//
//  Created by Liu Yi on 21/10/13.
//  Last Modified on 04/04/14.
//

#pragma once

#include "SOIL\SOIL.h"
#include <string>
#include <map>
#include "GL\freeglut.h"
#include "GL\glext.h"
#include <iostream>
using std::string;
using std::map;
using std::pair;

/**
 * @class Texture Manager
 * @brief Manages textures used by the game.
 *
 * @author Liu Yi and Robert Herne
 * @date 21/10/13
 * @version 2
 *
 * @bug None
 */

class TextureManager
{
public:

    /**
     * @brief Gets the instance of the texture manager.
     *
     * @param None.
	 *
	 * @pre None.
	 *
	 * @post The instance of the texture manager is returned.
     */
	static TextureManager* Instance();

	void printTexs();
	
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
    GLuint getTexture(string name);

	GLuint loadCube(char * front, char * back, char * top, char * bottom, char * left, char * right);

	void addCubeTexture(char * front, char * back, char * top, char * bottom, char * left, char * right, string name);
	

private:
	TextureManager(){}          	// Creates a texture manager object.
	~TextureManager(){}         	// Deletes the texture manager.
	GLuint loadPNG(char * name);    // Loads a texture from a PNG file.
	map<string, GLuint> textures;   // Map containing texture name and texture data.
};

