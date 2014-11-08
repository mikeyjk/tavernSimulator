#include "Graph.h"


Graph::Graph(void)
{
	srand (time(NULL));
}


Graph::~Graph(void)
{
}


vector<GraphNode> Graph::getWaypoints()
{
	return waypoints;
}


void Graph::addWaypoint(Vec3 p)
{
	GraphNode gn; //create a new graph node

	//set the node's x, y, z values
	gn.point.setX(p.getX());
	gn.point.setY(p.getY());
	gn.point.setZ(p.getZ());

	waypoints.push_back(gn); //add node to list of waypoints
}


void Graph::addBiDirectionalConnection(int waypoint, int other, int weight)
{
	Connection c1, c2;

	//connection from waypoint to other
	c1.index = other;
	c1.weight = weight;

	//connection from other to waypoint
	c2.index = other;
	c2.weight = weight;

	waypoints[waypoint].connections.push_back(c1); //add parent->child connection to waypoint's connection list
	waypoints[other].connections.push_back(c2); //add child->parent connection to other's connection list
}

int Graph::getNextWaypoint(int start)
{
	//get number of exit paths
	int numExits  = waypoints[start].connections.size();
	//pick a random exit
	int randExit = (rand()%(numExits-1)); 
	//return exit
	return randExit;
}