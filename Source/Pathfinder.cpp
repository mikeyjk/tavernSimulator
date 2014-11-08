#include "Pathfinder.h"


Pathfinder::Pathfinder(void)
{
	mStartAndTargetInitialised = false; //start and target nodes not initialised to begin
	mTargetFound = false; //target not found to begin
}


Pathfinder::~Pathfinder(void)
{
	//clear start node memory and set to null
	delete mStartNode;
	mStartNode = NULL;

	//clear target node memory and set to null
	delete mTargetNode;
	mTargetNode = NULL;

	//clear memory of each node in open list
	for(int i=0; i<mOpenList.size(); i++)
	{
		delete mOpenList[i];
	}

	ClearOpenList(); //clear vector

	//clear memory of each node in closed list
	for(int i=0; i<mClosedList.size(); i++)
	{
		delete mClosedList[i];
	}

	ClearClosedList(); //clear vector

	//clear memory of each point in path to target list
	for(int i=0; i<mPathToTarget.size(); i++)
	{
		delete mPathToTarget[i];
	}

	ClearPathToTarget();  //clear vector
}


void Pathfinder::FindPath(Vec3 currentPos, Vec3 targetPos)
{
	if(!mStartAndTargetInitialised)
	{
		for(int i=0; i<mOpenList.size(); i++)
		{
			delete mOpenList[i];
		}

		ClearOpenList();

		for(int i=0; i<mClosedList.size(); i++)
		{
			delete mClosedList[i];
		}

		ClearClosedList();

		for(int i=0; i<mPathToTarget.size(); i++)
		{
			delete mPathToTarget[i];
		}

		ClearPathToTarget();

		//initialise start
		PathNode start;
		start.SetXcoord(currentPos.getX());
		start.SetZcoord(currentPos.getZ());

		//initialise target
		PathNode target;
		target.SetXcoord(targetPos.getX());
		target.SetZcoord(targetPos.getZ());

		SetStartAndTarget(start, target);
		mStartAndTargetInitialised = true;
	}

	if(mStartAndTargetInitialised)
	{
		ContinuePath();
	}
}


void Pathfinder::SetStartAndTarget(PathNode start, PathNode target)
{
	mStartNode = new PathNode(start.GetXcoord(), start.GetZcoord(), NULL);
	mTargetNode = new PathNode(target.GetXcoord(), target.GetZcoord(), &target);

	mStartNode->SetGval(0);
	mStartNode->SetHval(mStartNode->GetManhattanDistance(mTargetNode));
	mStartNode->SetParent(NULL);

	mOpenList.push_back(mStartNode);

}


PathNode* Pathfinder::GetNextNode()
{
	float bestFval = mOpenList[0]->GetF();
	int index = -1;
	PathNode *nextNode = NULL;

	for(int i=1; i< mOpenList.size(); i++)
	{
		if(mOpenList[i]->GetF() < bestFval)
		{
			bestFval = mOpenList[i]->GetF();
			index = i;
		}
	}

	if(index >= 0)
	{
		nextNode = mOpenList[index];
		mClosedList.push_back(nextNode);
		mOpenList.erase(mOpenList.begin() + index);
	}

	return nextNode;
}


void Pathfinder::ClearOpenList()
{
	mOpenList.clear();
}


void Pathfinder::ClearClosedList()
{
	mClosedList.clear();
}


void Pathfinder::ClearPathToTarget()
{
	mPathToTarget.clear();
}


bool Pathfinder::StartTargetlInitialised()
{
	return mStartAndTargetInitialised;
}


bool Pathfinder::TargetFound()
{
	return mTargetFound;
}


void Pathfinder::PathOpened(int x, int z, float newCost, PathNode *parent)
{
	//if(NODE_BLOCKED)
	//	return;

	int id = z * WORLD_SIZE + z;
	float newFval;

	for(int i=0; i<mClosedList.size(); i++)
	{
		if(id == mClosedList[i]->GetId())
			return;
	}

	PathNode* newChildNode = new PathNode(x, z, parent);
	newChildNode->SetGval(newCost);
	newChildNode->SetHval(parent->GetManhattanDistance(mTargetNode));

	for(int i=0; i<mOpenList.size(); i++)
	{
		if(id == mOpenList[i]->GetId())
		{
			newFval = newChildNode->GetGval() + newCost + mOpenList[i]->GetHval();

			if(mOpenList[i]->GetF() > newFval)
			{
				mOpenList[i]->SetGval(newChildNode->GetGval() + newCost);
				mOpenList[i]->SetParent(newChildNode);
			}
			else //if the F value isnt better
			{
				delete newChildNode;
				return;
			}
		}
	}

	mOpenList.push_back(newChildNode);
}


void Pathfinder::ContinuePath()
{
	if(!mOpenList.empty())
	{
		PathNode *currentNode = GetNextNode();

		if(currentNode->GetId() == mTargetNode->GetId())
		{
			mTargetNode->SetParent(currentNode->GetParent());

			PathNode *getPath;

			for(getPath = mTargetNode; getPath != NULL; getPath = getPath->GetParent())
			{
				mPathToTarget.push_back(new Vec3(getPath->GetXcoord(), 0, getPath->GetZcoord()));
			}

			mTargetFound = true;
		}
		else
		{
			//west node
			PathOpened(currentNode->GetXcoord() - 1, currentNode->GetZcoord(), currentNode->GetGval() + 1, currentNode);
			//east node
			PathOpened(currentNode->GetXcoord() + 1, currentNode->GetZcoord(), currentNode->GetGval() + 1, currentNode);
			//north node
			PathOpened(currentNode->GetXcoord(), currentNode->GetZcoord() + 1, currentNode->GetGval() + 1, currentNode);
			//south node
			PathOpened(currentNode->GetXcoord(), currentNode->GetZcoord() - 1, currentNode->GetGval() + 1, currentNode);

			//north west node
			PathOpened(currentNode->GetXcoord() - 1, currentNode->GetZcoord() + 1, currentNode->GetGval() + 1.414f, currentNode);
			//north east node
			PathOpened(currentNode->GetXcoord() + 1, currentNode->GetZcoord() + 1, currentNode->GetGval() + 1.414f, currentNode);
			//south east node
			PathOpened(currentNode->GetXcoord() + 1, currentNode->GetZcoord() - 1, currentNode->GetGval() + 1.414f, currentNode);
			//south west node
			PathOpened(currentNode->GetXcoord() - 1, currentNode->GetZcoord() - 1, currentNode->GetGval() + 1.414f, currentNode);

			for(int i=0; i<mOpenList.size(); i++)
			{
				if(currentNode->GetId() == mOpenList[i]->GetId())
				{
					mOpenList.erase(mOpenList.begin() + i);
				}
			}
		}
	}
}


Vec3 Pathfinder::NextPathPosition(NPC *npc)
{
	int index = 1;
	Vec3 nextPosition;
	int radius = 30;

	nextPosition.setX(mPathToTarget[mPathToTarget.size()-index]->getX());
	nextPosition.setX(mPathToTarget[mPathToTarget.size()-index]->getZ());

	if(index < mPathToTarget.size())
	{
		if((nextPosition - npc->getPos()).length() < radius)//npc->GetRadius())
		{
			mPathToTarget.erase(mPathToTarget.end() - index);
		}
	}

	return nextPosition;
}