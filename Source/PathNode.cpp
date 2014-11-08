#include "PathNode.h"


PathNode::PathNode(void)
{
	mParent = NULL;
}


PathNode::PathNode(int x, int z, PathNode *parent)
{
	 mX_coord = x;
	 mZ_coord = z;
	 mParent = parent;
	 mId = (z * WORLD_SIZE) + z;
	 mG_val = 0;
	 mH_val = 0;
}


PathNode::~PathNode(void)
{
}


void PathNode::SetXcoord(int x)
{
	mX_coord = x;
}


void PathNode::SetZcoord(int z)
{
	mZ_coord = z;
}


void PathNode::SetId(int id)
{
	mId = id;
}


void PathNode::SetParent(PathNode *parent)
{
	mParent = parent;
}


void PathNode::SetGval(float g)
{
	mG_val = g;
}


void PathNode::SetHval(float h)
{
	mH_val = h;
}


int PathNode::GetXcoord()
{
	return mX_coord;
}


int PathNode::GetZcoord()
{
	return mZ_coord;
}


int PathNode::GetId()
{
	return mId;
}


PathNode* PathNode::GetParent()
{
	return mParent;
}


float PathNode::GetGval()
{
	return mG_val;
}


float PathNode::GetHval()
{
	return mH_val;
}


float PathNode::GetF()  
{ 
	return mG_val + mH_val; 
}


float PathNode::GetManhattanDistance(PathNode *nodeEnd)
{
	float x = (float)(fabs((float)this->mX_coord - (float)nodeEnd->mX_coord));
	float z = (float)(fabs((float)this->mZ_coord - (float)nodeEnd->mZ_coord));

	return x + z;
}

