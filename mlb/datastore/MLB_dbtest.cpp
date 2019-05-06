// --------------------------------------------------------------------
//
// MLB_dbtest.cpp Test Program for MLB  data store
//
// Eugene Tyler -  CS1D - Project 2
//                        04/15/19

#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <list>

using namespace std;

#include "MLBTeam.hpp"
#include "MLBTeamDataStore.hpp"

//! print_state - helper function function to debug iostream issues
//!
//! \author edt (3/25/19)
//!
//! \param stream
void print_state (const std::ios& stream)
{
  std::cout << " good()=" << stream.good();
  std::cout << " eof()=" << stream.eof();
  std::cout << " fail()=" << stream.fail();
  std::cout << " bad()=" << stream.bad();
  cout << endl;
}

TeamDataStore Teams;
//! Main - function for testing MLB datastore classes
//!
//! \author edt (3/25/19)
//!
//! \param argc - number of commandline arguments
//! \param argv - list of command line arguments
//!
//! \return int - return code
int main (int argc, char *argv[])
{
    Teams.load("./TeamData.csv");
    //Teams.load("./TeamExpansionData.csv", true);  // verify dupes do not get loaded
    Teams.save("./TeamData.csv.tmp");


    //for (std::list<Restaurant>::iterator it = Restaurants.list.begin(); it != Restaurants.list.end(); ++it)

    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
       cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
               " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
               " - Year Open: " << (*it).getDateOpened() << " - Seats: " << (*it).getCenterField() << endl;
    }
    cout << endl << endl;                      // range-for-loop to print Teams

    cout << "Name from id test " << Teams.FindbyNumber(2).getTeamName() << endl;

    cout << "Add a souvenir item test" << endl;
    MLBTeam &myteam = Teams.FindbyNumber(2);
    myteam.PrintAsDebug(true, false);
    myteam.addSouvenir("Test Item", 9.89);
    myteam.PrintAsDebug(true, false);
    cout << endl << endl;

    // Test Requirement 3
    cout << "Display a single, specified team's data" << endl;
    MLBTeam &myteam2 = Teams.FindbyNumber(20);
    myteam2.PrintAsDebug(true, false);


    // Test Requirement 4
    cout << "Sort by Team Name - Test Requirement 4" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_teamname());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requirement 5
    cout << "Sort by Stadium Name - Test Requirement 5" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_stadiumname());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requirement 6
    cout << "Sort by Stadium Name - American League Only - Test Requirement 6" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_stadiumname());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getLeague() == "American")
            {
                cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                        " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                        " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
            }
        }
    }
    cout << endl << endl;

    // Test Requirement 7
    cout << "Sort by Team Name - National League Only - Test Requirement 7" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_teamname());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getLeague() == "National")
            {
                cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                        " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                        " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
            }
        }
    }
    cout << endl << endl;

    // Test Requiement 8
    cout << "Sort by Park Typology - Test Requirement 8" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_typology());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requirement 9
    cout << "Sort by Team Name - Open Roof Only - Test Requirement 9" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_teamname());
    int count_open = 0;
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getRoofType() == "Open")
            {
                count_open++;
                cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                        " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                        " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
            }
        }
    }
    cout << "Number of parks with open roof type is: " << count_open << endl;
    cout << endl << endl;

    // Test Requirement 10
    cout << "Sort by Year Park Opened - Test Requirement 10" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_yearopen());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requirement 11
    cout << "Sort by Park Capacity - Test Requirement 11" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_seatcapacity());
    int total_capacity = 0;
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
           total_capacity += (*it).getCapacity();
        }
    }
    cout << "total seating capacity of all MLB parks: " << total_capacity;
    cout << endl << endl;

    // Test Requirement 12
    cout << "Display Park(s) with greatest distance to center field - Test Requirement 12" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_distcenterfield());
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << "-------------------------------------------" << endl;
    int greatest_distance = 0;
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getCenterField() > greatest_distance)
            {
                greatest_distance = (*it).getCenterField();
            }
        }
    }
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getCenterField() == greatest_distance)
            {
                cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                        " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                        " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
            }
        }
    }
    cout << endl << endl;


    // Test Requirement 13
    cout << "Display Park(s) with smallest distance to center field - Test Requirement 13" << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_seatcapacity());
    int smallest_distance = 9999;
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getCenterField() < smallest_distance)
            {

                smallest_distance = (*it).getCenterField();
            }
        }
    }
    for (std::vector<MLBTeam>::iterator it = Teams.m_TeamList.begin(); it != Teams.m_TeamList.end(); ++it)
    {
        if (!it->IsDeleted())
        {
            if ((*it).getCenterField() == smallest_distance)
            {
                cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                        " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                        " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
            }
        }
    }
    cout << endl << endl;

    // Test Requirement: Planning Vacation 1 - Distance to arbitrary team
    cout << "Planning Vacation 1 - Distance to arbitrary team" << endl;
    int source_team = 13;
    int dest_team = 5;
    cout << "Distance from " << Teams.FindbyNumber(source_team).getStadiumName() << " to "  
         << Teams.FindbyNumber(dest_team).getStadiumName() <<  " " << Teams.PlanTrip(source_team,dest_team) << " miles" << endl;
    cout << endl << endl;

    // Test Requirement: Planning Vacation 2 - Distance to lists of arbitrary teams
    cout << "Planning Vacation 2 - Distance to lists of arbitrary teams" << endl;
    std::vector<int> vac_list;
    vac_list.push_back(12);
    vac_list.push_back(4);
    vac_list.push_back(8);
    vac_list.push_back(22);

    source_team = 999;
    dest_team = 999;
    int total_miles = 0;
    for (std::vector<int>::const_iterator it = vac_list.begin(); it != vac_list.end(); ++it)
    {
        if (source_team == 999)
        {
            source_team = *it;
            continue;
        }
        dest_team = *it;
        int miles = Teams.PlanTrip(source_team,dest_team);
        total_miles += miles;
        cout << "Distance from " << Teams.FindbyNumber(source_team).getStadiumName() << " to "  
             << Teams.FindbyNumber(dest_team).getStadiumName() <<  " " << miles << " miles" << endl;
        source_team = dest_team;
    }
    cout << "Total Miles Traveled: " << total_miles << endl;
    cout << endl << endl;

    // Test Requirement: Planning Vacation 3 - Distance to all teams from an arbitrary team (Detroit Tigers - Comerica)
    cout << "Planning Vacation 3 - Distance to all teams from an arbitrary team (Detroit Tigers - Comerica)" << endl;
    source_team = 10;
    dest_team = 999;
    total_miles = 0;

    std::vector<TeamEdge> distances = Teams.PlanMultTrip(source_team);

    source_team = 999;
    for (std::vector<TeamEdge>::iterator it = distances.begin(); it != distances.end(); ++it)
    {
        if (source_team == 999)
        {
            source_team = it->m_nTeam;
            continue;
        }
        dest_team = it->m_nTeam;
        int miles = it->m_nDistance;
        total_miles += miles;
        cout << "Distance from " << Teams.FindbyNumber(source_team).getStadiumName() << " to "  
             << Teams.FindbyNumber(dest_team).getStadiumName() <<  " " << miles << " miles" << endl;
        source_team = dest_team;
    }
    cout << "Total Miles Traveled: " << total_miles << endl;
    cout << endl << endl;

    // Test Requirement: Planning Vacation 4 - Shortest Trip visiting selected teams from an selected starting team 
    cout << "Planning Vacation 4 - Shortest Trip visiting selected teams from an selected starting team" << endl;
    source_team = 13;

    std::vector<int> vac_list4;
    vac_list4.push_back(12);
    vac_list4.push_back(4);
    vac_list4.push_back(8);
    vac_list4.push_back(22);

    std::vector<TeamEdge> distances4 = Teams.PlanShortestTrip(source_team, vac_list4, false);

    source_team = 999;
    total_miles = 0;
    for (std::vector<TeamEdge>::iterator it = distances4.begin(); it != distances4.end(); ++it)
    {
        if (source_team == 999)
        {
            source_team = it->m_nTeam;
            continue;
        }
        dest_team = it->m_nTeam;
        int miles = it->m_nDistance;
        total_miles += miles;
        cout << "Distance from " << Teams.FindbyNumber(source_team).getStadiumName() << " to "  
             << Teams.FindbyNumber(dest_team).getStadiumName() <<  " " << miles << " miles" << endl;
        source_team = dest_team;
    }
    cout << "Total Miles Traveled: " << total_miles << endl;
    cout << endl << endl;

    // Test Requirement: Planning Vacation 5 - Minimum Spanning Tree (MST) using Primm's Algorithm 
    cout << "Planning Vacation 5 - Minimum Spanning Tree (MST) using Primm's Algorithm starting at Angels Stadium" << endl;
    source_team = 13;
    Teams.primMST(source_team);

    cout << endl << endl;
    sort(Teams.m_TeamList.begin(), Teams.m_TeamList.end(), Cmp_by_teamnumber());

    // Test Requirement: Planning Vacation 6 - DFS Starting at Fenway 
    cout << "Planning Vacation 6 - DFS Starting at Fenway" << endl;
    //Teams.FindbyNumber(4).PrintAsDebug(true,true);
    Teams.InitVisited();
    total_miles = 0;
    Teams.DFS(4, total_miles);
    cout << endl;
    cout << "Total Miles: " << total_miles;

    cout << endl << endl;

    // Test Requirement: Planning Vacation 7 - BFS Starting at Coors 
    cout << "Planning Vacation 7 - BFS Starting at Coors" << endl;
    //Teams.FindbyNumber(9).PrintAsDebug(true,true);
    Teams.InitVisited();
    total_miles = 0;
    Teams.BFS(9, total_miles);
    cout << endl;
    cout << "Total Miles: " << total_miles;

    cout << endl << endl;
}

