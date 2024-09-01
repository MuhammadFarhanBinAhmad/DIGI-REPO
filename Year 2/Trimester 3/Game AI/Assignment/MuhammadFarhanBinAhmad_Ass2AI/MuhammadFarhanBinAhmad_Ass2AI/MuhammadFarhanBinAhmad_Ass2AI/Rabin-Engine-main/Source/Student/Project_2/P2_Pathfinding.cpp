#include <pch.h>
#include <iostream>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"
#include "P2_GridNode.h"
const float SQRT_TWO = 1.414f;

std::vector<P2_GridNode*> OpenList;
std::vector<P2_GridNode*> ClosedList;


P2_GridNode gridNode[40][40];
bool debugColors = false;
#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}

bool ProjectTwo::implemented_jps_plus()
{
    return false;
}
#pragma endregion

bool AStarPather::initialize()
{
    // handle any one-time setup requirements you have
    //pre compute neighboure
    Callback cb = std::bind(&AStarPather::SetGridStatus, this);
    Messenger::listen_for_message(Messages::MAP_CHANGE, cb);
    //Callback cb = std::bind(&AStarPather::your_function_name, this);
    //Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

    return true; // return false if any errors actually occur, to stop engine initialization
}
void AStarPather::SetGridStatus()
{
    GridPos temp;
    for (short row = 0; row < terrain->get_map_height(); row++)
    {
        temp.row = row;
        for (short col = 0; col < terrain->get_map_width(); col++)
        {
            temp.col = col;
            gridNode[row][col].setGridPos(temp);
        }
        temp.col = 0;
    }
}
void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */

}
P2_GridNode* getSmallestNode(const std::vector<P2_GridNode*>& list)
{
    if (list.empty()) return nullptr;

    P2_GridNode* smallestNode = list[0];
    for (const auto& node : list) 
    {
        if (node->getFinalCost() < smallestNode->getFinalCost()) 
        {
            smallestNode = node;
        }
    }

    return smallestNode;
}
void RemoveNode(std::vector<P2_GridNode*>& list,P2_GridNode& nodeToRemove)
{
    auto it = std::find(list.begin(), list.end(), &nodeToRemove);
    if (it != list.end())
    {
        list.erase(it);
    }
}

void DebugNode(const P2_GridNode& node)
{
    std::cout
        << "Final Cost: " << node.getFinalCost() << '\n';
        //<< "CurrentNode Pos: " << node.getGridpos().row << ',' << node.getGridpos().col << '\n';
        //<< "ParentNode Pos: " << node.getParentNode().getGridpos().row << ',' << node.getParentNode().getGridpos().col << '\n';
        //for (const auto& p : node.getWallCheck()) {
        //    std::cout<< "ValidNeighbour: (" << p.first << ", " << p.second << ")\n";
        //}

}
void Smoothing(PathRequest& request)
{
    if (request.path.size() > 4)
    {
        int index = 0;
        int offset = 0;
        int counter = 0;

        Vec3 firstVec3, secondVec3, thridVec3, fourthVec3;
        Vec3 resultOneVec3, resultTwoVec3, resultThreeVec3, resultFourVec3;
        std::list<Vec3>::iterator it;
        std::list<Vec3> copy;

        it = request.path.begin();

        //(1,1,2,3)
        firstVec3.x = it->x;
        firstVec3.z = it->z;
        secondVec3.x = it->x;
        secondVec3.z = it->z;
        it++;
        thridVec3.x = it->x;
        thridVec3.z = it->z;
        it++;
        fourthVec3.x = it->x;
        fourthVec3.z = it->z;

        resultOneVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.0f);
        resultTwoVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.25f);
        resultThreeVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.5f);
        resultFourVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.75f);

        copy.push_back(resultOneVec3);
        copy.push_back(resultTwoVec3);
        copy.push_back(resultThreeVec3);
        copy.push_back(resultFourVec3);

        //reset
        it = request.path.begin();

        while (it != request.path.end())
        {
            std::advance(it, offset);//offset starting iterator
            firstVec3.x = it->x;
            firstVec3.z = it->z;
            it++;
            if (it == request.path.end())
            {
                break;
            }
            secondVec3.x = it->x;
            secondVec3.z = it->z;
            it++;
            if (it == request.path.end())
            {
                break;
            }
            thridVec3.x = it->x;
            thridVec3.z = it->z;
            it++;
            if (it == request.path.end())
            {
                break;
            }
            fourthVec3.x = it->x;
            fourthVec3.z = it->z;

            resultOneVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.0f);
            resultTwoVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.25f);
            resultThreeVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.5f);
            resultFourVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.75f);

            copy.push_back(resultOneVec3);
            copy.push_back(resultTwoVec3);
            copy.push_back(resultThreeVec3);
            copy.push_back(resultFourVec3);

            it = request.path.begin();
            offset++;
        }
        //(n-2,n-1,n,n)
        if (it == request.path.end())
        {
            //reverse path list
            auto Rit = request.path.rbegin();
            //go back by 3
            std::advance(Rit, 3);
            auto nIt = Rit.base();

            firstVec3.x = nIt->x;
            firstVec3.z = nIt->z;
            nIt++;
            secondVec3.x = nIt->x;
            secondVec3.z = nIt->z;
            nIt++;
            thridVec3.x = nIt->x;
            thridVec3.z = nIt->z;
            fourthVec3.x = nIt->x;
            fourthVec3.z = nIt->z;

            resultOneVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.0f);
            resultTwoVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.25f);
            resultThreeVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.5f);
            resultFourVec3 = SimpleMath::Vector3::CatmullRom(firstVec3, secondVec3, thridVec3, fourthVec3, 0.75f);

            copy.push_back(resultOneVec3);
            copy.push_back(resultTwoVec3);
            copy.push_back(resultThreeVec3);
            copy.push_back(resultFourVec3);
        }
        //clear old path to insert new data into new path
        request.path.clear();
        

        for (auto element : copy)
        {
            request.path.push_back(element);
        }
    }
   
}
bool Split(WaypointList::iterator const& a, WaypointList::iterator const& b, WaypointList& path)
{
    float SplitDistance = 0;
    float oneDistance = DirectX::SimpleMath::Vector3::Distance(terrain->get_world_position(0, 0), terrain->get_world_position(0, 1));
    SplitDistance = oneDistance + oneDistance / 2.0f;

    if (DirectX::SimpleMath::Vector3::Distance(*a, *b) <= SplitDistance)
    {
        return false;

    }
    else
    {
        Vec3 midPoint = (*a + *b) / 2;
        WaypointList::iterator newIterator = path.emplace(b, midPoint);
        return Split(a, newIterator, path) || Split(newIterator, b, path);
    }
}
void RubberBandSmooth(PathRequest& request)
{
    WaypointList::iterator first = request.path.begin();
    WaypointList::iterator second = request.path.begin();
    std::advance(second, 1);

    while (second != request.path.end())
    {
        Split(first, second,request.path);
        first = second;
        second++;
    }
}
//return false if no wall. return true if got wall
void RubberBanding(PathRequest& request)
{
    int counter = 0;
    int offset = 0;
    
    Vec3 startPosVec3, endPosVec3;
    GridPos startNodePos, endNodePos;
    std::list<Vec3>::iterator it;
    it = request.path.begin();

    while(it != request.path.end())
    {
        switch (counter)
        {
            case (0):
            {
                //convert from world space to gridpos
                //I hate doing this
                startPosVec3.x = it->x;
                startPosVec3.z = it->z;
                startNodePos = terrain->get_grid_position(startPosVec3);
                counter++;
                it++;
                break;
            }
            case(1):
            {
                counter++;
                it++;
                break;
            }
            case(2):
            {
                endPosVec3.x = it->x;
                endPosVec3.z = it->z;
                endNodePos = terrain->get_grid_position(endPosVec3);
                //Check for wall inbetween 1st and 3rd node position
                GridPos minPos, maxPos;
                minPos.row = (startNodePos.row < endNodePos.row) ? startNodePos.row : endNodePos.row;
                minPos.col = (startNodePos.col < endNodePos.col) ? startNodePos.col : endNodePos.col;
                maxPos.row = (startNodePos.row > endNodePos.row) ? startNodePos.row : endNodePos.row;
                maxPos.col = (startNodePos.col > endNodePos.col) ? startNodePos.col : endNodePos.col;

                bool wallFound = false;

                for (short row = minPos.row; row <= maxPos.row && !wallFound; row++)
                {
                    for (short col = minPos.col; col <= maxPos.col; col++)
                    {
                        if (terrain->is_wall(row, col))
                        {
                            offset++;
                            wallFound = true;
                            it = request.path.begin();
                            std::advance(it, offset);
                            break;
                        }
                    }
                }
                if (!wallFound)
                {
                    //no wall
                    it = request.path.begin();//reset to start of iterator
                    //erase middle child
                    std::advance(it, offset + 1);//offset for previous occurance when got wall and needed to plus one. Plus one is to get middle child position
                    it = request.path.erase(it);//remove middle child
                    //Reset iterator to startnode
                    it = request.path.begin();
                    std::advance(it, offset);
                }

                counter = 0;
                break;
            }
        }
    }

}
PathResult AStarPather::compute_path(PathRequest &request)
{
    P2_GridNode* currNode = NULL;
    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);
    //Set Path
    if (request.newRequest)
    {
        for (unsigned __int8 row = 0; row < terrain->get_map_width(); row++)
        {
            for (unsigned __int8 col = 0; col < terrain->get_map_height(); col++)
            {
                gridNode[row][col].clearNode();
            }
        }
        //Clear all past data
        OpenList.clear();
        ClosedList.clear();
        request.path.clear();
        //Initalize first guy
        currNode = &(gridNode[start.row][start.col]);
        //currNode->setParentNode(*currNode);//set parent to self
        currNode->setGivenCost(0);
        currNode->setFinalCost(currNode->getHueristicCost(goal,request.settings.heuristic), request.settings.weight);
        currNode->setNodeStatus(ONLIST::OPEN);
        //DebugNode(*currNode);
        OpenList.push_back(currNode);

        if (debugColors)
        terrain->set_color(currNode->getGridpos(), Colors::Blue);
    }
 
    while (!OpenList.empty())
    {
        //Find smallest fella from list
        currNode = getSmallestNode(OpenList);
        //DebugNode(*currNode);
        RemoveNode(OpenList, *currNode);
        //Remove from openlist and plac them into close list

        //Check if he is goal
        if (currNode->getGridpos().col == goal.col &&
            currNode->getGridpos().row == goal.row)
        {


            //Draw Path
            while (&(currNode->getParentNode()) != NULL)
            {
                request.path.push_front(terrain->get_world_position(currNode->getGridpos()));
                //DebugNode(*currNode);
                currNode = &currNode->getParentNode();
            }
            //DebugNode(*currNode);
            request.path.push_front(terrain->get_world_position(currNode->getGridpos()));
            //apply smoothing

            //apply rubberbanding
            if (request.settings.rubberBanding)
            {
                RubberBanding(request);
            }
            if (request.settings.smoothing)
            {
                //Special child
                if (request.settings.rubberBanding)
                {
                    RubberBandSmooth(request);
                    Smoothing(request);
                }
                else
                {
                    Smoothing(request);
                }
            }
            if (request.settings.debugColoring)
            {
                debugColors = true;
            }
            else
            {
                debugColors = false;
            }
            return PathResult::COMPLETE;
        }
        
        currNode->setNodeStatus(ONLIST::CLOSED);
        ClosedList.push_back(currNode);
        //DebugNode(*currNode);
        if (debugColors)
        terrain->set_color(currNode->getGridpos(), Colors::Yellow);

        for (auto dir : currNode->getWallCheck())
        {
            {
                //Check neighbour
                if ((currNode->getGridpos().row + dir.first) >= 0 &&
                    (currNode->getGridpos().col + dir.second) >= 0 &&
                    (currNode->getGridpos().row + dir.first) < terrain->get_map_width() &&
                    (currNode->getGridpos().col + dir.second) < terrain->get_map_height())
                {
                    GridPos temp;
                    temp.row = currNode->getGridpos().row + dir.first;
                    temp.col = currNode->getGridpos().col + dir.second;

                    P2_GridNode* neighbourNode = &(gridNode[temp.row][temp.col]);

                    if (!neighbourNode->getGridPosWallStatus())
                    {
                        //technically this 2 if i can combine.See if got time
                        //need check also if out of bound
                        if (neighbourNode->getNodeStatus() == ONLIST::NOTONLIST)
                        {
                            neighbourNode->setNodeStatus(ONLIST::OPEN);
                            neighbourNode->setParentNode(*currNode);
                            neighbourNode->setGivenCost();

                            //Vec3::CatmullRom
                            //Apply catmullrom to all my node gridpos
                            //RubberBanding
                            //Get 3 node, make box and 
                            neighbourNode->setFinalCost(neighbourNode->getHueristicCost(goal,request.settings.heuristic),request.settings.weight);
                            OpenList.push_back(neighbourNode);

                            if (debugColors)
                            terrain->set_color(neighbourNode->getGridpos(), Colors::Blue);
                        }

                        else if (neighbourNode->getNodeStatus() == ONLIST::OPEN || neighbourNode->getNodeStatus() == ONLIST::CLOSED)
                        {
                            //since neighbour is in list, need compare if this new route to neighbour is cheaper
                            //Need get neighbour node from list and compare with this new neighbour

                            float FinalCost = neighbourNode->getHueristicCost(goal, request.settings.heuristic) * request.settings.weight;
                            GridPos parentPos = currNode->getGridpos();
                            float givenCost;
                            if (neighbourNode->getGridpos().row == parentPos.row || neighbourNode->getGridpos().col == parentPos.col) 
                            {
                                givenCost = currNode->getGivenCost() + 1;
                            }
                            else {
                                givenCost = currNode->getGivenCost() + SQRT_TWO;
                            }

                            FinalCost += givenCost;

                            if (FinalCost < neighbourNode->getFinalCost())
                            {
                                neighbourNode->setGivenCost(givenCost);
                                neighbourNode->setFinalCost(FinalCost);
                                neighbourNode->setParentNode(*currNode);

                                if (debugColors)
                                terrain->set_color(neighbourNode->getGridpos(), Colors::Blue);

                                if (neighbourNode->getNodeStatus() == ONLIST::CLOSED)
                                {
                                    neighbourNode->setNodeStatus(ONLIST::OPEN);
                                    OpenList.push_back(neighbourNode);//add new neighbour
                                }
                            }

                        }
                    }
                    
                }
            }
        }
        if (request.settings.singleStep == true)
        {
            return PathResult::PROCESSING;
        }
    }
    return PathResult::IMPOSSIBLE;
    /*
        This is where you handle pathing requests, each request has several fields:

        start/goal - start and goal world positions
        path - where you will build the path upon completion, path should be
            start to goal, not goal to start
        heuristic - which heuristic calculation to use
        weight - the heuristic weight to be applied
        newRequest - whether this is the first request for this path, should generally
            be true, unless single step is on

        smoothing - whether to apply smoothing to the path
        rubberBanding - whether to apply rubber banding
        singleStep - whether to perform only a single A* step
        debugColoring - whether to color the grid based on the A* state:
            closed list nodes - yellow
            open list nodes - blue

            use terrain->set_color(row, col, Colors::YourColor);
            also it can be helpful to temporarily use other colors for specific states
            when you are testing your algorithms

        method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
            will be A* generally, unless you implement extra credit features

        The return values are:
            PROCESSING - a path hasn't been found yet, should only be returned in
                single step mode until a path is found
            COMPLETE - a path to the goal was found and has been built in request.path
            IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
    */

}
