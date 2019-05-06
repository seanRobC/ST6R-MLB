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

//! TeamDataStore - internal storage for Team objects
//!
//! \author edt (3/25/19)
class TeamDataStore
{
public:
    // Constructor
    TeamDataStore();

    // Destructor
    virtual ~TeamDataStore();

    void printAsDebug(bool printeol, bool printcontent) const;
    MLBTeam &FindbyNumber(int Number);
    std::vector<MLBTeam>::const_iterator getBeginIterator(void) {return m_TeamList.cbegin();};
    std::vector<MLBTeam>::const_iterator getEndIterator(void) {return m_TeamList.cend();};

    void load(const string path, bool ItemsAreAdditional = false);
    void save(const string path);
    void load_additional(const string path);


    void DijkstraComputePaths(int source,const std::vector<MLBTeam> teamlist,
                              const adjacency_list_t &adjacency_list,
                              std::vector<int> &min_distance,
                              std::vector<int> &previous, int num_vertices);

    std::list<string> DijkstraGetShortestPathTo(int vertex, const std::vector<MLBTeam> teamlist, const std::vector<int> &previous);
    int PlanTrip(int from, int to);
    const std::vector<TeamEdge> PlanMultTrip(int source_team);
    void primMST(int source_team, const std::vector<MLBTeam> teamlist);

    std::vector<MLBTeam> m_TeamList;
    static const int max_weight;

private:
    bool DuplicateNumPresent(int Number);

    // Copy constructor
    TeamDataStore(const TeamDataStore& src);

    // Assignment operator
    TeamDataStore& operator=(const TeamDataStore& src); 

} ;
