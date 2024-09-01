#pragma once
#include <iostream>
#include "Projects/ProjectTwo.h"

enum class ONLIST
{
	NOTONLIST,
	OPEN,
	CLOSED
};

class P2_GridNode
{
public:
	P2_GridNode();
	bool operator==(const P2_GridNode& other) const;
	void setGridPos(const GridPos& pos);
	GridPos getGridpos() const;
	void setNodeStatus(ONLIST status);
	ONLIST getNodeStatus() const;
	void setGivenCost();
	void setGivenCost(float gs);
	float getGivenCost() const;
	float getHueristicCost(const GridPos& endPos, Heuristic heuristicType);
	void setFinalCost(float heuristicCost,float weight);
	void setFinalCost(float fc);
	float getFinalCost() const;
	void setParentNode(P2_GridNode& parentNode);
	P2_GridNode& getParentNode() const;
	void setGridPosWallStatus(bool iw);
	bool getGridPosWallStatus() const;
	const std::vector<std::pair<int, int>>& getWallCheck() const;
	void clearNode();

private:
	std::vector<std::pair<int, int>> validDirection;	//8x 4x5x 40
	P2_GridNode* parent;		//8
	GridPos gridPos;			//8 56
	float finalCost =0;			//4 60
	float givenCost = 0;		//4	64
	bool isWall = false;		//1	
	ONLIST gridStatus = ONLIST::NOTONLIST;	//1
	//62 < 140
	//40 - 120 
};

