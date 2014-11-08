#pragma once

#include <cmath>

#ifndef NULL
#define NULL 0
#endif

const int WORLD_SIZE = 4096; //use to set the size of the world map

/**
 * @class PathNode
 * @brief PathNode class represents a position on the world map
 *
 * PathNode class represents a position on the world map represented
 * by an x, y, and z coordinate. Also stores cost to travel to the node 
 * and heuristic distance to target.
 *
 * @author Raymond Forster
 * @date 15/10/2014
 */
class PathNode
{
	public:
			/**
			 * @brief Constructor initialises Pathfinder object
			 * @param none
			 */
		PathNode(void);
		
			/**
			 * @brief Constructor initialises Pathfinder object
			 * @param int x - the x position
			 * @param int z - the z position
			 * @param PathNode *parent - the parent node
			 */
		PathNode(int x, int z, PathNode *parent);
			
			/**
			 * @brief Destructor clears all memory
			 * @param none
			 */
		~PathNode(void);

			/**
			 * @brief Sets the x coordinate
			 * @param int x - the x coordinate
			 */
		void SetXcoord(int x);
		
			/**
			 * @brief Sets the z coordinate
			 * @param int z - the z coordinate
			 */
		void SetZcoord(int z);
		
			/**
			 * @brief Sets this node's id
			 * @param int id - the node id
			 */
		void SetId(int id);
		
			/**
			 * @brief Sets the parent node
			 * @param PathNode *parent - the parent node
			 */
		void SetParent(PathNode *parent);
		
			/**
			 * @brief Sets this node's cost
			 * @param int g - the g value
			 */
		void SetGval(float g);
		
			/**
			 * @brief Sets this node's estimated distance to target
			 * @param float h - the heuristic value
			 */
		void SetHval(float h);

			/**
			 * @brief Gets the x coordinate
			 * @return int
			 */
		int GetXcoord();
		
			/**
			 * @brief Gets the z coordinate
			 * @return int
			 */
		int GetZcoord();
		
			/**
			 * @brief Gets the node's id
			 * @return int
			 */
		int GetId();
		
			/**
			 * @brief Gets the node's parent node
			 * @return PathNode*
			 */
		PathNode* GetParent();
		
			/**
			 * @brief Gets the node's cost
			 * @return float
			 */
		float GetGval();
		
			/**
			 * @brief Gets the nodes estimated distance to target
			 * @return float
			 */
		float GetHval();

			/**
			 * @brief Gets the total cost so far to this node
			 *
			 * Gets the total cost so far to this node. F(total cost) = G(cost) + H(heuristic)
			 *
			 * @return float
			 */
		float GetF();
		
			/**
			 * @brief Calculates the estimated distance to target using Manhattan Distance
			 *
			 * Calculates the estimated distance to target using Manhattan Distance.
			 * ManhattanDistance = total vertical distance + total horizontal distance
			 *
			 * @return float
			 */
		float GetManhattanDistance(PathNode *nodeEnd);

	private:
		int mX_coord, mZ_coord, mId;
		PathNode *mParent;
		float mG_val, mH_val;
};

