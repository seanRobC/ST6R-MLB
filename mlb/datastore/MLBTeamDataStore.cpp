/**
 * CS1D - MLB
 *
 * Implements a data storage mechanism for Team objects. These
 * objects are contained in a vector that supports
 * iterators and a comparable interface
 *
 * @author   edt
 */

#include "MLBTeamDataStore.hpp"
#include "MLBTeam.hpp"
#include <stdio.h>
#include <fstream>
#include <stdexcept>
#include <ostream>
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <iterator>

using namespace std;

const int TeamDataStore::max_weight = 999999;
TeamEdge TeamDataStore::m_DistancesArray[31+1][31+1]; // Adjacency Matrix
//memset(TeamDataStore::m_DistancesArray, 0 sizeof(MLBTeam::m_DistancesArray));
//std::vector<std::vector<TeamEdge>> TeamDataStore::m_DistancesArrayV;
static const int max_level = 8;
vector<int> Levels[max_level];

//! default constuctor
//!
//! \author edt (3/25/19)
TeamDataStore::TeamDataStore()
{
};

//! TeamDataStore::load - get object data from file
//!
//! \author edt (3/25/19)
//!
//! \param path - location of CSV file to load
//! \param ItemsAreAdditional - add items to existing datastore
void TeamDataStore::load(const string path, bool ItemsAreAdditional)
{
    //string fullpath = path + "TeamData.csv";
    if (!ItemsAreAdditional)
    {
        MLBTeam *tmp = new MLBTeam();
        tmp->m_bDeleted = true;
        m_TeamList.push_back(*tmp);
    }
    std::ifstream infile(path, ios::in);
    int line_count = 0;
    if (infile.is_open())
    {
        std::string inputline;
        while (infile.good())
        {
            std::getline(infile, inputline);
            if (!infile.eof())
            {
                if (inputline[0] == '#')
                {
                    continue;  // ignore comment lines
                }
                line_count++;
                std::vector<std::string> commaSeparated(1);
                int commaCounter = 0;
                for (int i=0; i < inputline.size(); i++)
                {
                    if (inputline[i] == ',')
                    {
                        commaSeparated.push_back("");
                        commaCounter++;
                    } else
                    {
                        commaSeparated.at(commaCounter) += inputline[i];
                    }
                }
                // We now have a vector of strings that represent the data members
                // of our object
                // The serialized data looks like:
                // 1,Arizona Diamondbacks,Chase Field,48686,Phoenix Arizona,Grass,National,1998,407,124,Retro Modern,Retractable,0
                //    [1]                      [2]       3      [4]       [5]       [6]      7   8   9    [10]          [11]     [12]
                //
                // Distance Data is appended to the distance count and looks like
                //  number,distance) for each edge in the graph
                // 3,1,345,2,987
                //
                // Souvenir data is appended to the souverir count and looks like
                // (number, description,price,deleted

                int nNumber = std::stoi(commaSeparated[0]);
                // prevent loading of duplicate numbers by silently rejecting the load for this record
                if (DuplicateNumPresent(nNumber))
                {
                    continue;
                }

                int nSeatingCapacity = std::stoi(commaSeparated[3]);
                int nYearOpened = std::stoi(commaSeparated[7]);
                int nDistCenterFieldFeet = std::stoi(commaSeparated[8]);
                int nDistCenterFieldMeters = std::stoi(commaSeparated[9]);
                int nDeleted = std::stoi(commaSeparated[12]);

                // parse the list of Team Distances
                std::vector<TeamEdge> Distances;
                int nDistances = std::stoi(commaSeparated[13]);
                int it = 14;
                if (nDistances > 0)
                {
                    TeamEdge tmp;
                    while(it < (14 + 2*nDistances))
                    {
                        tmp.m_nTeam = std::stoi(commaSeparated[it]);
                        tmp.m_nDistance = std::stof(commaSeparated[it+1]);
                        Distances.push_back(tmp);
                        it += 2;
                    }
                }

                // Parse the list of Souvenirs
                std::vector<MLB_Souvenir> Souvenirs;
                int it2 = it + 1;
                int nSouvenirs = std::stoi(commaSeparated[it]);
                int nHighestSouvenirsNumber = 0;
                if (nSouvenirs > 0)
                {
                    while (it2 < (it + 1 + (4*nSouvenirs)))
                    {
                        int num = std::stoi(commaSeparated[it2++]);
                        string name = commaSeparated[it2++];
                        float price = std::stof(commaSeparated[it2++]);
                        int del = std::stoi(commaSeparated[it2++]);
                        MLB_Souvenir tmp(num,name,price,del);
                        Souvenirs.push_back(tmp);

                        if (num > nHighestSouvenirsNumber)
                        {
                            nHighestSouvenirsNumber = num;
                        }
                    }
                }

                // call the private constructor
                MLBTeam *pTeam = new MLBTeam(nNumber,
                                 commaSeparated[1],
                                 commaSeparated[2],
                                 nSeatingCapacity,
                                 commaSeparated[4],
                                 commaSeparated[5],
                                 commaSeparated[6],
                                 nYearOpened,
                                 nDistCenterFieldFeet,
                                 nDistCenterFieldMeters,
                                 commaSeparated[10],
                                 commaSeparated[11],
                                 nDeleted,
                                 Distances,
                                 Souvenirs,
                                 nHighestSouvenirsNumber);
                m_TeamList.push_back(*pTeam);
            }
        }
    }
    else
    {
        throw std::invalid_argument("Team File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("Team File Empty");
    }

    // after instantating all of the Teams, including newly added teams - clear and reinit the array
    InitVisitedArray();
}

//! TeamDataStore::save - save objects to external CSV file
//!
//! \author edt (3/25/19)
//!
//! \param path - location of external file (will be overwritten)
void TeamDataStore::save(const string path)
{
    //string fullpath = path + "TeamData.csv.tmp";
    string outline;
    int line_count = 0;

    std::ofstream outfile(path, ios::trunc);
    if (outfile.is_open())
    {
        for (std::vector<MLBTeam>::iterator it = m_TeamList.begin(); it != m_TeamList.end(); it++)
        {
            line_count++;

            outfile << (*it).m_nNumber << ",";
            outfile << (*it).m_sTeamName << ",";
            outfile << (*it).m_sParkName << ",";
            outfile << (*it).m_nSeatingCapacity << ",";
            outfile << (*it).m_sLocation << ",";
            outfile << (*it).m_sPlayingSurface << ",";
            outfile << (*it).m_sLeague << ",";
            outfile << (*it).m_nYearOpened << ",";
            outfile << (*it).m_nDistCenterFieldFeet << ",";
            outfile << (*it).m_nDistCenterFieldMeters << ",";
            outfile << (*it).m_sParkTyplolgy << ",";
            outfile << (*it).m_sRoofType << ",";
            outfile << (*it).m_bDeleted << ",";
            int num_dists = (*it).m_Distances.size();
            outfile << num_dists << ",";
            if (num_dists > 0)
            {
                for (std::vector<TeamEdge>::const_iterator itd = (*it).m_Distances.begin();
                                                                     itd != (*it).m_Distances.end(); itd++)
                {
                    outfile << (*itd).m_nTeam << ",";
                    outfile << (*itd).m_nDistance << ",";
                }
            }

            int num_Souvenirs = (*it).m_Souvenirs.size();
            outfile << num_Souvenirs << ",";
            if (num_Souvenirs > 0)
            {
                std::vector<MLB_Souvenir> Souvenirs;
                (*it).GetSouvenirs(Souvenirs);
                for (std::vector<MLB_Souvenir>::const_iterator itm = Souvenirs.begin();
                                                           itm != Souvenirs.end(); itm++)
                {
                    outfile << (*itm).m_nNumber << ",";
                    outfile << (*itm).m_sSouvenirName << ",";
                    outfile << (*itm).m_fSouvenirPrice << ",";
                    outfile << (*itm).m_bDeleted << ",";
                }
            }

            outfile << endl;
        }

    }
    else
    {
        throw std::invalid_argument("Team Save File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("Team Save File Empty");
    }
}

//! TeamDataStore::load_additional - helper function to add Teams to existing datastore
//!
//! \author edt (3/25/19)
//!
//! \param path - location of CSV file to load
void TeamDataStore::load_additional(const string path)
{
    load(path, true);
}

//! TeamDataStore::FindbyNumber - locate Team in datastore by number
//!
//! \author edt (3/25/19)
//!
//! \param Number - number to locate
//!
//! \return Team&amp; - pointer to Team or NULL if not found
MLBTeam &TeamDataStore::FindbyNumber(int Number)
{
    for (std::vector<MLBTeam>::iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            return *it;
        }
    }
    return *(m_TeamList.end());  // never reached  - should throw exception
}

//! TeamDataStore::DuplicateNumPresent - internal helper to determine if
//!  this number already in datastore
//!
//! \author edt (3/25/19)
//!
//! \param Number - number to search for
//!
//! \return bool - true if Team already in datastore
bool TeamDataStore::DuplicateNumPresent(int Number)
{
    bool dupe_found = false;
    for (std::vector<MLBTeam>::iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            dupe_found = true;
            break;
        }
    }
    return dupe_found;
}


void TeamDataStore::InitVisited(void)
{
    for (int team = 1; team <= m_TeamList.size(); team++)
    {
        MLBTeam *pTeam = &m_TeamList[team];
        pTeam->m_bVisited = false;
        for (int i = 0; i < pTeam->m_Distances.size(); i++)
        {
            pTeam->m_Distances[i].m_bVisited = false;
            //pTeam->m_Distances[i].discovery = false;
            //pTeam->m_Distances[i].back = false;
            //pTeam->m_Distances[i].forward = false;
            //pTeam->m_Distances[i].cross = false;
        }
    }
}

void TeamDataStore::InitVisitedArray(void)
{
#if 0
    for (std::vector<std::vector<TeamEdge>>::iterator it = m_DistancesArrayV.begin(); it != m_DistancesArrayV.end(); ++it)
    {
        (*it).clear();
    }

    std::vector<TeamEdge> vte;
    TeamEdge te(0,0);
    for (int i = 0; i < 31; i++)
    {
        m_DistancesArrayV.push_back(vte);
        for (int j = 0; j < 31; j ++)
        {
            m_DistancesArrayV[i].push_back(te);
        }
    }
#endif

    for (int i = 1; i < m_TeamList.size(); i++)
    {
        for (int j = 1; j < m_TeamList.size(); j++)
        {
            m_DistancesArray[i][j].m_nTeam = 0;
            m_DistancesArray[i][j].m_nDistance = 0;
            m_DistancesArray[i][j].m_bVisited = false;
            //m_DistancesArray[i][j].discovery = false;
            //m_DistancesArray[i][j].back = false;
            //m_DistancesArray[i][j].forward = false;
            //m_DistancesArray[i][j].cross = false;
        }
    }
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        for (std::vector<TeamEdge>::const_iterator ite = (*it).m_Distances.begin(); ite != (*it).m_Distances.end(); ++ite)
        {
            m_DistancesArray[(*it).m_nNumber][(*ite).m_nTeam].m_nDistance = ite->m_nDistance;
            m_DistancesArray[(*it).m_nNumber][(*ite).m_nTeam].m_nDistance = ite->m_nDistance;
            m_DistancesArray[(*ite).m_nTeam][(*it).m_nNumber].m_nTeam = ite->m_nTeam;
            m_DistancesArray[(*ite).m_nTeam][(*it).m_nNumber].m_nTeam = ite->m_nTeam;
        }
    }
#if 0
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        int tnum = (*it).m_nNumber;
        cout << "Team:" << (*it).m_nNumber << " ";
        for (int y = 0; y <= Teams.size(); y++)
        {
            cout << m_DistancesArray[tnum][y].m_nDistance << " ";
        }
        cout << endl;
    }
#endif   
}


void TeamDataStore::DijkstraComputePaths(int source, const std::vector<MLBTeam> teamlist, 
                          const adjacency_list_t &adjacency_list,
                          std::vector<int> &min_distance,
                          std::vector<int> &previous, int num_vertices)
{
    int n = num_vertices + 1; //adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    // we use greater instead of less to turn max-heap into min-heap
    std::priority_queue<TeamEdge, std::vector<TeamEdge>, EdgeGreater>  vertex_queue;
    vertex_queue.push(TeamEdge(source, min_distance[source]));

    while (!vertex_queue.empty())
    {
        int dist = vertex_queue.top().m_nDistance;
        int u = vertex_queue.top().m_nTeam;
        vertex_queue.pop();

    	// Because we leave old copies of the vertex in the priority queue
    	// (with outdated higher distances), we need to ignore it when we come
    	// across it again, by checking its distance against the minimum distance
    	if (dist > min_distance[u])
    	    continue;

        // Visit each edge exiting u
    	const std::vector<TeamEdge> &neighbors = teamlist[u].m_Distances;
        for (std::vector<TeamEdge>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            int v = neighbor_iter->m_nTeam;
            int weight = neighbor_iter->m_nDistance;
            int distance_through_u = dist + weight;
    	    if (distance_through_u < min_distance[v])
            {
    	        min_distance[v] = distance_through_u;
    	        previous[v] = u;
    	        vertex_queue.push(TeamEdge(v, min_distance[v]));
    	    }
        }
    }
}


std::list<string> TeamDataStore::DijkstraGetShortestPathTo(int vertex, const std::vector<MLBTeam> teamlist, const std::vector<int> &previous)
{
    std::list<string> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(teamlist[vertex].getStadiumName());
    return path;
}

// Prints shortest paths from src to all other vertices
void TeamDataStore::primMST(int source_team)
{
    std::vector<MLBTeam> teamlist;
    MLBTeam *dummyzero = new MLBTeam();
    teamlist.push_back(*dummyzero);
    delete dummyzero;
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        teamlist.push_back(*it);
    }
    // Note - this puts each team's data in the vector element that corresponds to the team number.
    //        if the numbers are discontinuous, this will present a problem
    sort(teamlist.begin(), teamlist.end(), Cmp_by_teamnumber());

    // Create a priority queue to store vertices that
    // are being preinMST.
    std::priority_queue<TeamEdge, std::vector<TeamEdge>, EdgeGreater> pq;

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(teamlist.size(), max_weight);

    // To store parent array which in turn store MST
    vector<int> parent(teamlist.size(), -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(teamlist.size(), false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(TeamEdge(source_team, 0));
    key[source_team] = 0;

    /* Looping till priority queue becomes empty */
    while (!pq.empty())
    {
        // The first vertex in pair is the minm_TeamListimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)
        int u = pq.top().m_nTeam;
        pq.pop();

        inMST[u] = true;  // Include vertex in MST

        // 'i' is used to get all adjacent vertices of a vertex
        for (std::vector<TeamEdge>::const_iterator i = teamlist[u].GetDistances().begin(); i != teamlist[u].GetDistances().end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).m_nTeam;
            int weight = (*i).m_nDistance;

            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                key[v] = weight;
                pq.push(TeamEdge(v, weight));
                parent[v] = u;
            }
        }
    }

    int total_mileage = 0;
    cout << "Minimum Spanning Tree (MST) starting at " << teamlist[source_team].getStadiumName() << " : " << endl;
    // Print edges of MST using parent array
    for (int i = 1; i < teamlist.size(); ++i)
    {
        int par = parent[i];
        if (par != -1)
        {
            cout << "From " << teamlist[par].getStadiumName() << " to " << teamlist[i].getStadiumName() << " " << key[i] << " miles" << endl;
            total_mileage += key[i];
        }
        //printf("%d - %d\n", parent[i], i);
    }
    cout << "Total mileage : " << total_mileage << endl;
}

//! TeamDataStore::printAsDebug - helper function to print internal state of
//! all objects in datastore
//!
//! \author edt (3/25/19)
//!
//! \param printeol - print end of lines after each data element
//! \param printcontent - print internal data of Teams
void TeamDataStore::printAsDebug(bool printeol, bool printcontent) const
{
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        it->PrintAsDebug(printeol, printcontent);
    }
}

//! TeamDataStore::~TeamDataStore - Destructor
//!
//! \author edt (3/25/19)
TeamDataStore::~TeamDataStore()
{

};

int TeamDataStore::PlanTrip(int from, int to)
{
    std::vector<MLBTeam> teamlist;
    MLBTeam *dummyzero = new MLBTeam();
    teamlist.push_back(*dummyzero);
    delete dummyzero;
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        teamlist.push_back(*it);
    }
    // Note - this puts each team's data in the vector element that corresponds to the team number.
    //        if the numbers are discontinuous, this will present a problem
    sort(teamlist.begin(), teamlist.end(), Cmp_by_teamnumber());

    int source_num = 999;
    int dest_num = 999;
    int i = 0;
    // convert source Team number to a vector index
    for (std::vector<MLBTeam>::const_iterator it = teamlist.begin(); it != teamlist.end(); ++it)
    {
        if (it->getNumber() == from)
        {
            source_num = i;
        }
        if (it->getNumber() == to)
        {
            dest_num = i;
        }
        i++;
    }
    if (source_num != 999 && dest_num != 999)
    {
        std::vector<int> min_distance(teamlist.size());
        std::vector<int> previous(teamlist.size());
        DijkstraComputePaths(source_num, teamlist, teamlist[from].GetDistances(), min_distance, previous, teamlist.size());
        return min_distance[dest_num];
    }
    else
    {
        return 0; // invalid team numbers passed
    }
}

const std::vector<TeamEdge> TeamDataStore::PlanMultTrip(int from)
{
    std::vector<TeamEdge> distances;
    std::vector<MLBTeam> teamlist;
    MLBTeam *dummyzero = new MLBTeam();
    teamlist.push_back(*dummyzero);
    delete dummyzero;
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        teamlist.push_back(*it);
    }
    // Note - this puts each team's data in the vector element that corresponds to the team number.
    //        if the numbers are discontinuous, this will present a problem
    sort(teamlist.begin(), teamlist.end(), Cmp_by_teamnumber());

    int source_num = 999;
    int dest_num = 999;
    int i = 0;
    // convert source Team number to a vector index
    for (std::vector<MLBTeam>::const_iterator it = teamlist.begin(); it != teamlist.end(); ++it)
    {
        if (it->getNumber() == from)
        {
            source_num = i;
        }
        i++;
    }
    if (source_num != 999)
    {
        TeamEdge te(source_num,0);
        distances.push_back(te);
        while (source_num != 0)
        {
            std::vector<int> min_distance(teamlist.size());
            std::vector<int> previous(teamlist.size());
            int mindist = 99999;
            int minteam = 0;
            DijkstraComputePaths(source_num, teamlist, teamlist[from].GetDistances(), min_distance, previous, teamlist.size());
            for (int i = 1; i < min_distance.size(); i++)
            {
                if (i != source_num && mindist > min_distance[i])
                {
                    bool found = false;
                    for (std::vector<TeamEdge>::const_iterator it = distances.begin(); it != distances.end(); ++it)
                    {
                        if ((*it).m_nTeam == i)
                        {
                            found = true;
                        }
                    }
                    if (!found)
                    {
                        mindist = min_distance[i];
                        minteam = i;
                    }
                }
            }
            if (minteam != 0)
            {
                TeamEdge te(minteam,mindist);
                distances.push_back( te);
                source_num = minteam;
            }
            else
            {
                break;  // no more entries 
            }
        }

    }
    return distances; // invalid team number passed

}

const std::vector<TeamEdge> TeamDataStore::PlanShortestTrip(int from, std::vector<int> dests, bool ordered)
{
    std::vector<TeamEdge> distances;
    std::vector<MLBTeam> teamlist;
    MLBTeam *dummyzero = new MLBTeam();
    teamlist.push_back(*dummyzero);
    delete dummyzero;
    for (std::vector<MLBTeam>::const_iterator it = m_TeamList.begin(); it != m_TeamList.end(); ++it)
    {
        teamlist.push_back(*it);
    }
    // Note - this puts each team's data in the vector element that corresponds to the team number.
    //        if the numbers are discontinuous, this will present a problem
    sort(teamlist.begin(), teamlist.end(), Cmp_by_teamnumber());

    int source_num = 999;
    int dest_num = 999;
    int i = 0;
    // convert source Team number to a vector index
    for (std::vector<MLBTeam>::const_iterator it = teamlist.begin(); it != teamlist.end(); ++it)
    {
        if (it->getNumber() == from)
        {
            source_num = i;
        }
        i++;
    }
    if (source_num != 999)
    {
        TeamEdge te(source_num,0);
        distances.push_back(te);
        while (source_num != 0)
        {
            std::vector<int> min_distance(teamlist.size());
            std::vector<int> previous(teamlist.size());
            int mindist = 99999;
            int minteam = 0;
            std::vector<int>::iterator minit;
            DijkstraComputePaths(source_num, teamlist, teamlist[from].GetDistances(), min_distance, previous, teamlist.size());
            for (std::vector<int>::iterator iti = dests.begin(); iti != dests.end(); iti++)
            {
                if (*iti != source_num && mindist > min_distance[*iti])
                {
                    bool found = false;
                    for (std::vector<TeamEdge>::const_iterator it = distances.begin(); it != distances.end(); ++it)
                    {
                        if ((*it).m_nTeam == *iti)
                        {
                            found = true;
                        }
                    }
                    if (!found)
                    {
                        mindist = min_distance[*iti];
                        minteam = *iti;
                        minit = iti;
                    }
                }
            }
            if (minteam != 0)
            {
                TeamEdge te(minteam,mindist);
                distances.push_back(te);
                dests.erase(minit);
                source_num = minteam;
            }
            else
            {
                break;  // no more entries 
            }
        }

    }
    return distances;
}


void TeamDataStore::DFS(const int vertice, int &total_miles)
{
    // label v as Visited
    m_TeamList[vertice].SetVisited();
    cout << "Visited Vertice #" << vertice << " :" << m_TeamList[vertice].getStadiumName() << endl;

    // process the edges from this city
    //vector<CityEdge> dist = m_TeamList[vertice].GetDistances();
    for (int outedge = 0; outedge < m_TeamList[vertice].GetDistances().size(); outedge++)
    {
        int shortest_dist = 99999;
        int shortest_city = 0;
        int shortest_edge = 0;
        for (int edge = 0; edge < m_TeamList[vertice].GetDistances().size(); edge++)
        {
            if (!m_TeamList[vertice].IsEdgeVisited(edge))
            {
                // edge not visited
                int adjcity = m_TeamList[vertice].GetAdjacentCity(edge);
                if (!m_TeamList[adjcity].IsVisited())
                {
                    // city not yet visted
                    if (m_TeamList[vertice].GetDistance(edge) < shortest_dist)
                    {
                        shortest_dist = m_TeamList[vertice].GetDistance(edge);
                        shortest_city = adjcity;
                        shortest_edge = edge;
                    }
                }
                else
                {
                    //cout << "Back edge:" << vertice << ":::" << adjcity << " Miles-" << m_TeamList[vertice].GetDistance(edge) << endl;
                    //m_TeamList[vertice].SetBack(edge);
                }
            }
        }
        // visit closest unvisited City, add total mileage, set edge as discovery
        if (shortest_city != 0)
        {
            total_miles += shortest_dist;
            //m_TeamList[vertice].SetDiscovered(shortest_edge);
            //m_TeamList[vertice].ClearBack(shortest_edge);
            m_TeamList[vertice].SetVisited(shortest_edge);
#if 0
            cout << "Discovery edge:" << vertice << ":::" << shortest_city << " Miles-" << shortest_dist << endl;
#endif
            DFS(shortest_city, total_miles);
        }
        else
        {
            // No unvisted citys for this vertice, go back to prior vertice
            break;
        }
    }
}

void TeamDataStore::BFS(const int vertice, int &total_miles)
{
    int cur_level = 0;
    int prev_level;

    int num_teams = m_TeamList.size();

    // label v as Visited
    m_TeamList[vertice].SetVisited();

    cout << endl << "-------- Level " << cur_level << endl;
    cout << "Starting Vertice #" << vertice << " :" << m_TeamList[vertice].getStadiumName() << endl;

    vector<int> Levels[4];

    Levels[0].push_back(vertice);
    while (!Levels[cur_level].empty())
    {
        bool vertices_discovered = false;
        prev_level = cur_level;
        cur_level++;
        cout << endl << "-------- Level " << cur_level << endl;
        if (cur_level >= max_level)
        {
            // error - could have used a vector instead of a fixed size array
            cout << "======================= !!!!!!!!!!!!!!!!!! ==================" << endl;
            throw("Too many Levels");
        }

        for (std::vector<int>::iterator it = Levels[prev_level].begin(); it != Levels[prev_level].end(); it++)
        {
            // process the edges from this city in the IncidentArray
            for (int outedge = 1; outedge <= num_teams; outedge++)
            {
                int team_number = *it;
#if 0
                TeamEdge test[32];
                for (int x = 0; x < 32; x++)
                {
                    test[x] = m_DistancesArray[team_number][x];
                }
#endif
                if (m_DistancesArray[team_number][outedge].m_nTeam != 0)
                {
                    int shortest_dist = 99999;
                    int shortest_team = 0;
                    for (int edge = 1; edge <= num_teams; edge++)
                    {
                        if (m_DistancesArray[team_number][edge].m_nTeam != 0)
                        {
                            if ( (m_DistancesArray[team_number][edge].m_nDistance < shortest_dist) &&
                                 (!m_DistancesArray[team_number][edge].IsVisited()) )  // edge unexplored
                            {
                                shortest_dist = m_DistancesArray[team_number][edge].m_nDistance;
                                shortest_team = edge;
                            }
                        }
                    }

                    if (shortest_team != 0)
                    {

                        if (!m_TeamList[shortest_team].IsVisited())
                        {
                            //MLBTeam::m_DistancesArray[city_number][shortest_city].SetDiscovered();
                            m_DistancesArray[team_number][shortest_team].SetVisited();
                            Levels[cur_level].push_back(shortest_team);
                            total_miles += shortest_dist;
                            vertices_discovered = true;
                            m_TeamList[shortest_team].SetVisited();
                            cout << "Discovered Vertice #" << shortest_team << " :" << m_TeamList[shortest_team].getStadiumName() << " Parent#:" << team_number << "  Miles - " << shortest_dist << endl;
                        }
                        else
                        {
                            //m_DistancesArray[city_number][shortest_team].SetBack();
                            m_DistancesArray[team_number][shortest_team].SetVisited();
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        if (!vertices_discovered)
        {
            cout << "No Undicovered Vertices Remaining" << endl;
            break;  // exit - all vertices discovered in prior level
        }
    }
}
