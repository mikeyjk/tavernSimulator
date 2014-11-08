//
//  ModelManager.h
//  ModelManager
//
//  Created by Liu Yi on 28/10/13.
//  Last Modified on 04/04/14.
//

#pragma once

#include "GL\freeglut.h"
#include <map>
#include <string>
#include "ObjLoader.h"
#include "TextureManager.h"
#include <vector>
#include "Vec3.h"
#include <boost/math/constants/constants.hpp>

using std::string;
using std::map;
using std::pair;
using std::iterator;
using std::end;
using std::begin;
using std::vector;
using namespace boost;

struct MinMax
{
	Vec3 min;
	Vec3 max;
};

/**
 * @class Model Manager
 * @brief Manages models used by the game.
 *
 * @author Liu Yi and Robert Herne
 * @date 28/10/13
 * @version 2
 *
 * @bug None
 */

class ModelManager
{
public:

    /**
     * @brief Gets the instance of the model manager.
     *
     * @param None.
	 *
	 * @pre None.
	 *
	 * @post The instance of the model manager is returned.
     */
	static ModelManager* instance();

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
     * @brief Gets the vertex buffer of the model with the matching name.
     *
     * @param string Name
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The vertex buffer is returned.
     */
	GLuint getModelVertex(string name);
	
	/**
     * @Gets the ID of the texture of the model with the matching name.
     *
     * @param string name
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The texture's ID is returned.
     */
	GLuint getTexture(string name);
	
	/**
     * @brief Gets the model's normal buffer of the model with the matching name.
     *
     * @param string Name
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The model's normal buffer is returned.
     */
	GLuint getNormal(string name);
	
	/**
     * @brief Gets the number of vertices the model with the matching name has.
     *
     * @param string Name
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The number of vertices the model has is returned.
     */
	int getNumberOfVertices(string name);

	/**
     * @brief Draws a model to the screen with a specified texture and translates it by a specified amount.
     *
     * @param string mName, string tName, float trans
	 *
	 * @pre A model with a matching name exists.
	 *
	 * @post The model is drawn with the specified texture and translation amount.
     */
	void draw(string mName, string tName,  float transparency , Vec3 transition, Vec3 rotation);

	void draw(string mName,string tName, float transparency , Vec3 transition, Vec3 rotation, Vec3 scale);

private:
	ModelManager(){}					// Creates a model manager object.
	~ModelManager(){}					// Deletes the model manager.
	map<string, ObjMesh> models;		// Stores the model data.
	map<string, GLuint> modelvertex;	// Stores data on a model's vertices.
	map<string, int> NumberOfVertex;	// Stores the number of vertices a model has.
	map<string, GLuint> modeltexture;	// Stores the coordinate buffers of the textures used by the models.
	map<string, GLuint> modelNormal;	// Stores a model's normals.
	map<string, MinMax> modelMinMax;
};

