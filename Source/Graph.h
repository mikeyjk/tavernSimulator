#pragma once

#include <vector>
#include <ctime> 
#include "Vec3.h"

using namespace std;


/*
 * @struct Connection
 * @brief Connection between two graph nodes
 */
struct Connection
{
	int index; //index to GraphNode list this connection represents
	int weight; //weight of the connection
};


/*
 * @struct GraphNode
 * @brief Connection between two graph nodes
 */
struct GraphNode 
{
	Vec3 point; //the node's world coordinate
	vector<Connection> connections; //this nodes connections
};


/**
 * @class Graph
 * @brief Graph class consisting of nodes and connections
 * @author Raymond Forster
 */
class Graph
{
	private:
		vector<GraphNode> waypoints; /**< list of waypoints */

	public:
		Graph(void);
		~Graph(void);

		/**
		 * @brief Returns the list of waypoints
		 * @author Raymond Forster
		 * @return vector<GraphNode> waypoints - the list of waypoints
		 */	
		vector<GraphNode> getWaypoints();

		/**
		 * @brief Adds a waypoint to the list of waypoints
		 * @author Raymond Forster
		 * @param Vec3 p - the coordinate of the waypoint
		 * @return void
		 */	
		void addWaypoint(Vec3 p);

		/**
		 * @brief Adds a connection from waypoint to other, and from other to waypoint
		 * @author Raymond Forster
		 * @param int waypoint - the current waypoint
		 * @param int other - the waypoint to connect to
		 * @param int weight - the weight of the connection
		 * @return void
		 */	
		void addBiDirectionalConnection(int waypoint, int other, int weight);

		/**
		 * @brief Adds a connection from waypoint to other, and from other to waypoint
		 * @author Raymond Forster
		 * @param int start - the search start node
		 * @return void
		 */
		int getNextWaypoint(int start);
};

