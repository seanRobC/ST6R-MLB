/**
 * CS1D - MLB
 *
 * Defines a data storage mechanism for Team objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#pragma once

#include "MLBTeam.hpp"
#include <list>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
#include <algorithm>
#include <iterator>

using namespace std;

typedef std::vector<TeamEdge> adjacency_list_t;
static const int max_bfs_level = 8;

//! TeamDataStore - internal storage for Team objects
//!
//! \author edt (3/25/19)
class TeamDataStore
{
public:

    //! TeamDataStore - default constructor
    //!
    //! \author edt (5/6/19)
    TeamDataStore();

    // Destructor
    virtual ~TeamDataStore();


    //! PrintAsDebug - prints state of teams list object
    //!
    //! \author edt (5/6/19)
    //!
    //! \param print_endl 
    //! \param print_detail 
    //!
    //! \return bool - true if object printed
    void printAsDebug(bool printeol, bool printcontent) const;

    //! FindbyNumber - Return a MLBTeam object based on supplied number
    //!
    //! \author edt (5/6/19)
    //!
    //! \param Number - team number to locate
    //!
    //! \return MLBTeam&amp; - reference to MLBTeam object
    MLBTeam &FindbyNumber(int Number);

    std::vector<MLBTeam>::const_iterator getBeginIterator(void) {return m_TeamList.cbegin();};
    std::vector<MLBTeam>::const_iterator getEndIterator(void) {return m_TeamList.cend();};

    //! load - load the m_TeamList member from user specified csv file
    //!
    //! \author edt (5/6/19)
    //!
    //! \param path - path to csv file
    //! \param ItemsAreAdditional - true if append csv items to m_TeamList
    void load(const string path, bool ItemsAreAdditional = false);

    //! save - store the contents from m_TeamList into specified csv file
    //!
    //! \author edt (5/6/19)
    //!
    //! \param path - location to store csv file (.tmp suffix)
    void save(const string path);

    //! load_additional - helper to allow appending to m_TeamList
    //!
    //! \author edt (5/6/19)
    //!
    //! \param path 
    void load_additional(const string path);

    // DFS and BFS Helpers
    // Note extra row/column to allow 1 based vertice numbers
    static TeamEdge m_DistancesArray[31+1][31+1]; // Adjacency Array
    static std::vector<std::vector<TeamEdge>> m_DistancesArrayV; // Adjacency Array

    //! InitVisited - clear all MLBTeam adjacency lists visited flag
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    void InitVisited(void);

    //! InitVisitedArray - clear adjacency array, then load distances from all MLBTeam objects
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    void InitVisitedArray(void);

    //! DijkstraComputePaths - determine shortest distance to all teams
    //!
    //! \author edt (5/6/19)
    //!
    //! \param source - starting team number
    //! \param teamlist - list of all MLBTeams
    //! \param adjacency_list - priority_queue used to sort distances
    //! \param min_distance - vecor of distances to all cities
    //! \param previous - vector of all parents used in search
    //! \param num_vertices - number of teams
    void DijkstraComputePaths(int source,const std::vector<MLBTeam> teamlist,
                              const adjacency_list_t &adjacency_list,
                              std::vector<int> &min_distance,
                              std::vector<int> &previous, int num_vertices);

    //! DijkstraGetShortestPathTo - get list of stadium names used to get to specified team
    //!
    //! \author edt (5/6/19)
    //!
    //! \param vertex - team number to search for
    //! \param teamlist - list of all MLBTeams
    //! \param previous - list of parent nodes
    //!
    //! \return std::list&lt;string&gt; - vector of team names in path order
    std::list<string> DijkstraGetShortestPathTo(int vertex, const std::vector<MLBTeam> teamlist, const std::vector<int> &previous);

    //! PlanTrip - get shortest distance from source to destination team 
    //!
    //! \author edt (5/6/19)
    //!
    //! \param from - starting team
    //! \param to - ending team
    //!
    //! \return int - shortest distance to destination
    int PlanTrip(int from, int to);

    //! PlanShortestTrip - shortest distance from startingteam through specified list of teams
    //!
    //! \author edt (5/6/19)
    //!
    //! \param from - starting team
    //! \param dests- vector of teams to visit
    //! \param ordered - true if teams should be visited in order specified - not shortest distance
    //!
    //! \return const std::vector&lt;TeamEdge&gt; - vector if teams to visit in order
    const std::vector<TeamEdge> PlanShortestTrip(int from, std::vector<int> dests, bool ordered);


    //! PlanMultTrip - visit all teams starting at specified team
    //!
    //! \author edt (5/6/19)
    //!
    //! \param source_team - location to start
    //!
    //! \return const std::vector&lt;TeamEdge&gt; 
    const std::vector<TeamEdge> PlanMultTrip(int source_team);

    //! primMST - determine Minimum Spanning Tree (MST) from specifed starting team
    //!           using Prim Algorithm
    //!
    //! \author edt (5/6/19)
    //!
    //! \param source_team - starting team number
    void primMST(int source_team);

    //! DFS - preform a depth first traversal starting at specified location, 
    //!       calculate total length 
    //!
    //! \author edt (5/6/19)
    //!
    //! \param vertice  - starting team
    //! \param total_miles - pointer to location to store total distance
    //! \param edgelist - vector containing edges used in traversal
    //! \param thisedge_distance - distance to this vertice on edge used
    void DFS(const int vertice, int &total_miles, std::vector<TeamEdge> &edgelist, int thisedge_distance = 0);

    struct BFS_traversal
    {
        int team;
        int parent;
        int distance;
    };

    //! BFS - preform a breadth first traversal starting at specified location, 
    //!       calculate total length 
    //!
    //! \author edt (5/6/19)
    //!
    //! \param vertice  - starting team
    //! \param total_miles - pointer to location to store total distance
    //! \param Levels - array of vectors that contain discovered team information
    //!
    //! \return const std::vector&lt;TeamEdge&gt; 
    void BFS(const int vertice, int &total_miles, vector<BFS_traversal>(&Levels)[max_bfs_level]);

    std::vector<MLBTeam> m_TeamList;
    static const int max_weight;

private:
    //! DuplicateNumPresent - verify team number not already in m_TeamList
    //!
    //! \author edt (5/6/19)
    //!
    //! \param Number - team number to search for
    //!
    //! \return bool - true if duplicate team number
    bool DuplicateNumPresent(int Number);

    // Copy constructor
    TeamDataStore(const TeamDataStore& src);

    // Assignment operator
    TeamDataStore& operator=(const TeamDataStore& src); 

} ;
