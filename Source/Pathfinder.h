#pragma once

#include <vector>
#include "PathNode.h"
#include "Vec3.h"
#include "NPC.h"

using namespace std;

/**
 * @class Pathfinder
 * @brief Pathfinding class implementing the A* algorithm
 *
 * Pathfinding class finds the shortest path to a target location
 * from a given start location using the A* pathfinding algorithm
 *
 * @author Raymond Forster
 * @date 15/10/2014
 */
class Pathfinder
{
	public:
			/**
			 * @brief Constructor initialises Pathfinder object
			 * @param none
			 */
		Pathfinder(void);

			/**
			 * @brief Destructor clears all memory
			 * @param none
			 */
		~Pathfinder(void);

			/**
			 * @brief Initialise the world map
			 * @param none
			 * @return void
			 */
		void initMap();

			/**
			 * @brief Find the best path from current position to target position
			 * @param Vec3 currentPos - the starting position
			 * @param Vec3 targetPos - the target position
			 * @return void
			 */
		void FindPath(Vec3 currentPos, Vec3 targetPos);

			/**
			 * @brief Returns the next node to be travelled to from the best path
			 * @param NPC *npc - the traveller
			 * @return Vec3 
			 */
		Vec3 NextPathPosition(NPC *npc);
		
			/**
			 * @brief Empties and frees memory of the open list
			 * @return void
			 */
		void ClearOpenList();
		
			/**
			 * @brief Empties and frees memory of the closed list
			 * @return void
			 */
		void ClearClosedList();
		
			/**
			 * @brief Empties and frees memory of the pathToTarget list
			 * @return void
			 */
		void ClearPathToTarget();
		
			/**
			 * @brief Determines whether or not start and target positions have been initialised
			 * @return bool
			 */
		bool StartTargetlInitialised();
		
			/**
			 * @brief Determines if the target has been found
			 * @return bool
			 */
		bool TargetFound();

	private:
		PathNode *mStartNode;
		PathNode *mTargetNode;
		vector<PathNode*> mOpenList;
		vector<PathNode*> mClosedList;
		vector<Vec3*> mPathToTarget;
		bool mStartAndTargetInitialised;
		bool mTargetFound;

			/**
			 * @brief Set the start and target positions
			 * @return void
			 */
		void SetStartAndTarget(PathNode start, PathNode target);
		
			/**
			 * @brief Populate the open list
			 * @param int x - the x position
			 * @param int z - the z position
			 * @param float newCost  - the cost to move to the node
			 * @param PathNode *parent - the parent node
			 * @return void
			 */
		void PathOpened(int x, int z, float newCost, PathNode *parent);
		
			/**
			 * @brief Get the node with the lowest cost
			 * @return PathNode* 
			 */
		PathNode* GetNextNode();
		
			/**
			 * @brief Continues looking for the best path
			 * @return void
			 */
		void ContinuePath();
};

