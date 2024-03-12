/******************************************************************************/
/*!
\file:		ALGraph.cpp
\author:    b.muhammafarhan
\par email: b.muhammafarhan@digipen.edu
\date:		3/9/24
\brief		This file contains the definitions needed to construct a graph and 
            implementing Dijkstra's algorithm.
*/
/******************************************************************************/
#include "ALGraph.h"

const unsigned INFINITY_ = static_cast<unsigned>(-1);

/******************************************************************************/
/*!
\fn     bool ALGraph::AdjInfo::operator < (const AdjInfo& rhs) const 
\brief  Compares to AdjacencyInfo node for sorting 
\param  rhs - right hand side node 
\return Returns true if weight less than rhs.weight
*/
/******************************************************************************/
bool ALGraph::AdjInfo::operator < (const AdjInfo& rhs) const 
{    
    return weight < rhs.weight;
}

/******************************************************************************/
/*!
\fn     bool ALGraph::AdjInfo::operator > (const AdjInfo& rhs) const 
\brief  Compares to AdjacencyInfo node for sorting
\param  rhs - right hand side node 
\return Returns true if weight is more than rhs.wight, else, return false. 
*/
/******************************************************************************/
bool ALGraph::AdjInfo::operator > (const AdjInfo& rhs) const 
{
    return weight > rhs.weight;
}
/******************************************************************************/
/*!
\fn     void ALGraph::AddUEdge(unsigned node1, unsigned node2, unsigned weight)
\brief  Adds undirected nodes between two nodes 
\param  node1 - first node
\param  node2 - second node
\param  weight - cost to get from node1 to node 2 and vice versa

*/
/******************************************************************************/
void ALGraph::AddUEdge(unsigned node1, unsigned node2, unsigned weight)
{
    AddDEdge(node1, node2, weight);
    AddDEdge(node2, node1, weight);
}
/******************************************************************************/
/*!
\fn     ALGraph::ALGraph(unsigned size)
\brief  Constructor for ALGraph
*/
/******************************************************************************/
ALGraph::ALGraph(unsigned size):size_{size}
{
    for(size_t i = 0; i < size; i++)
    {
        graph.push_back(std::vector<AdjInfo>());
    }
}

/******************************************************************************/
/*!
\fn     ALGraph::~ALGraph(void)
\brief  Destructor for ALGraph
*/
/******************************************************************************/
ALGraph::~ALGraph(void){}

/******************************************************************************/
/*!
\fn     void ALGraph::AddDEdge(unsigned source, unsigned destination, unsigned weight)
\brief  Adds directed edge between two nodes. 
\param  source -  starting node  
\param  destination -  destination node 
\param  weight - cost to get from source to destination

*/
/******************************************************************************/
void ALGraph::AddDEdge(unsigned source, unsigned destination, unsigned weight)
{   
    size_t i = source - 1;
    graph[i].push_back(AdjInfo{destination, weight});
    
    // Define a comparison function for sorting AdjInfo objects
    struct CompareAdjInfo 
    {
        bool operator()(const AdjInfo& LHS, const AdjInfo& RHS) const 
        {
            if (LHS.weight == RHS.weight)
            {
                return LHS.id < RHS.id;
            }
            return LHS.weight < RHS.weight;
        }
    };

    // Sort the vector using the comparison function
    std::sort(graph[i].begin(), graph[i].end(), CompareAdjInfo());
}
/******************************************************************************/
/*!
\fn     unsigned ALGraph::extract_min(std::vector<AdjacencyInfo>& pq) const
\brief  Extract node with the minimum cost
\param  pq - priorty queue containing vector of nodes
\return Returns  node index with the minimum cost 
*/
/******************************************************************************/
unsigned ALGraph::extract_min(std::vector<AdjacencyInfo>& pq) const
{
    if(pq.empty())
    {
        return 0;
    }

    size_t min_weight = INFINITY_;
    size_t id = pq[0].id;

    for(size_t i = 0; i < pq.size(); i++)
    {        
        if(pq[i].weight < min_weight)
        {
            min_weight = pq[i].weight;
            id = pq[i].id;
        }
    }
    
    return (unsigned)id;
}

/******************************************************************************/
/*!
\fn     std::vector<DijkstraInfo> ALGraph::Dijkstra(unsigned start_node) const

\brief  Performs Dijkstra's algorithm on  graph to find shortest path from starting node to every possible node. 

\param  start_node - start node

\return Returns result of the Dijkstra algorithm
*/
/******************************************************************************/
std::vector<DijkstraInfo> ALGraph::Dijkstra(unsigned start_node) const
{   
    std::vector<AdjacencyInfo> pq;
    std::vector<DijkstraInfo> dijkstra;
    
    for(unsigned i = 0; i < size_ ; i++)
    {
        DijkstraInfo di;
           
        if(i + 1 == start_node)
        {
            di.cost = 0;
            di.path.push_back(start_node);
        }
        else 
        {
            di.cost = INFINITY_;
        }
        
        dijkstra.push_back(di);
        pq.push_back(AdjacencyInfo{i+1, di.cost});
    }
    
    do
    {
        //Returns index of min cost node  
        size_t u = extract_min(pq);
        
        //if not updated and is not connected to any nodesif cost = infinite 
        if(dijkstra[u-1].cost == INFINITY_)
        {
            break;  
        }
        
        //for each neighbour v of u 
        for(size_t v = 0; v < graph[u - 1].size(); v++)
        {
            if(dijkstra[u - 1].cost + graph[u-1][v].weight <
               dijkstra[graph[u-1][v].id-1].cost)
            {
                //update cost
                dijkstra[graph[u-1][v].id-1].cost = dijkstra[u-1].cost + graph[u-1][v].weight;
                
                //update previous path 
                dijkstra[graph[u-1][v].id-1].path = dijkstra[u-1].path;
                dijkstra[graph[u-1][v].id-1].path.push_back(graph[u-1][v].id);
                
                //Update info in priority_queue
                for(size_t i = 0; i < pq.size(); ++i)
                {
                    if(pq[i].id == graph[u-1][v].id)
                    {
                        //update cost 
                        pq[i].weight = dijkstra[graph[u-1][v].id-1].cost;
                    }
                }
            }
        }
        
        //Remove minimum cost node from priority queue 
        for(size_t i = 0; i < pq.size(); i++)
        {
            if(pq[i].id == u)
            {
                pq.erase(pq.begin() + i);
                break;
            }
        }
    } while (!pq.empty());
    
    return dijkstra;
}

/******************************************************************************/
/*!
\fn     ALIST ALGraph::GetAList(void) const

\brief  Gets adjacency matrix

\return Returns adjacency matrix
*/
/******************************************************************************/
ALIST ALGraph::GetAList(void) const
{
    ALIST adjList;
    
    // Copy graph to adjList matrix 
    for(const std::vector<AdjInfo>& i : graph)
    {
        std::vector<AdjacencyInfo> v;
        
        for(const AdjInfo& j : i)
        {
            AdjacencyInfo info;
            info.id = j.id;
            info.weight = j.weight;
            v.push_back(info);
        }
        
        adjList.push_back(v);
    }
    return adjList;
}

