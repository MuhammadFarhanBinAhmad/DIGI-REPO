#include <pch.h>
#include <cmath>
#include "P2_GridNode.h"
const float SQRT_TWO = 1.4142135f;

P2_GridNode::P2_GridNode() : parent(nullptr), finalCost(0), givenCost(0), gridStatus(ONLIST::NOTONLIST) {
    gridPos.col = 0;
    gridPos.row = 0;
}

bool P2_GridNode::operator==(const P2_GridNode& other) const {
    return gridPos.col == other.getGridpos().col && gridPos.row == other.getGridpos().row;
}

void P2_GridNode::setGridPos(const GridPos& pos) {
    gridPos.col = pos.col;
    gridPos.row = pos.row;
    isWall = terrain->is_wall(gridPos);
    validDirection.clear();

    if (!isWall) {
        GridPos temp = gridPos;

        validDirection = { {1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1} };

        std::set<std::pair<int, int>> toRemove;

        // Check walls in adjacent positions and remove invalid directions
        //(0,1)
        temp.col += 1; // Right
        if (temp.col < terrain->get_map_width() && terrain->is_wall(temp)) 
        {
            toRemove.insert({ 0, 1 });
            toRemove.insert({ 1, 1 });
            toRemove.insert({ -1, 1 });

        }
        //(0,-1)
        temp = gridPos; temp.col -= 1; // Left
        if (temp.col >= 0 && terrain->is_wall(temp)) 
        {
            toRemove.insert({ 0, -1 });
            toRemove.insert({ 1, -1 });
            toRemove.insert({ -1, -1 });

        }
        //(1,0)
        temp = gridPos; temp.row += 1; // Up
        if (temp.row < terrain->get_map_height() && terrain->is_wall(temp)) 
        {
            toRemove.insert({ 1, 0 });
            toRemove.insert({ 1, -1 });
            toRemove.insert({ 1, 1 });

        }
        //(-1,0)
        temp = gridPos; temp.row -= 1; // Down
        if (temp.row >= 0 && terrain->is_wall(temp)) 
        {
            toRemove.insert({ -1, 0 });
            toRemove.insert({ -1, -1 });
            toRemove.insert({ -1, 1 });

        }

        validDirection.erase(std::remove_if(validDirection.begin(), validDirection.end(),
            [&toRemove](const std::pair<int, int>& elem) {
                return toRemove.find(elem) != toRemove.end();
            }), validDirection.end());
    }
}

GridPos P2_GridNode::getGridpos() const {
    return gridPos;
}

void P2_GridNode::setNodeStatus(ONLIST status) {
    gridStatus = status;
}

ONLIST P2_GridNode::getNodeStatus() const {
    return gridStatus;
}

void P2_GridNode::setGivenCost() {
    if (parent != nullptr) {
        GridPos parentPos = parent->getGridpos();
        if (gridPos.row == parentPos.row || gridPos.col == parentPos.col) {
            givenCost = parent->getGivenCost() + 1;
        }
        else {
            givenCost = parent->getGivenCost() + SQRT_TWO;
        }
    }
}
void P2_GridNode::setGivenCost(float gs) {
    givenCost = gs;
}

float P2_GridNode::getGivenCost() const {
    return givenCost;
}

float P2_GridNode::getHueristicCost(const GridPos& endPos, Heuristic heuristicType) {
    float xDiff = (float)(abs(endPos.col - gridPos.col));
    float yDiff = (float)(abs(endPos.row - gridPos.row));

    switch (heuristicType) 
    {
        case Heuristic::OCTILE: 
        {
            float minDiff = std::min(xDiff, yDiff);
            return (minDiff * SQRT_TWO + std::max(xDiff, yDiff) - minDiff);
        }
        case Heuristic::CHEBYSHEV:
            return std::max(xDiff, yDiff);
        case Heuristic::INCONSISTENT:
            if ((gridPos.row + gridPos.col) % 2 > 0) 
            {
                return std::sqrt((xDiff * xDiff) + (yDiff * yDiff)) ;
            }
            break;
        case Heuristic::MANHATTAN:
            return (xDiff + yDiff);
        case Heuristic::EUCLIDEAN:
            return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
    }
    return 0.0f;
}

void P2_GridNode::setFinalCost(float heuristicCost,float weight) 
{
    finalCost = givenCost + (heuristicCost * weight);
}
void P2_GridNode::setFinalCost(float fc)
{
    finalCost =fc;
}

float P2_GridNode::getFinalCost() const {
    return finalCost;
}

void P2_GridNode::setParentNode(P2_GridNode& parentNode) {
    parent = &parentNode;
}

P2_GridNode& P2_GridNode::getParentNode() const {
    return *parent;
}

void P2_GridNode::setGridPosWallStatus(bool iw) {
    isWall = iw;
}

bool P2_GridNode::getGridPosWallStatus() const {
    return isWall;
}

const std::vector<std::pair<int, int>>& P2_GridNode::getWallCheck() const {
    return validDirection;
}

void P2_GridNode::clearNode() {
    parent = nullptr;
    finalCost = 0;
    givenCost = 0;
    gridStatus = ONLIST::NOTONLIST;
}
