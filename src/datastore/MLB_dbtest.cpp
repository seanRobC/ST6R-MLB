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

    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
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
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_teamname());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
    }
    cout << endl << endl;

    // Test Requirement 5
    cout << "Sort by Stadium Name - Test Requirement 5" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_teamname());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
    }
    cout << endl << endl;

    // Test Requirement 6
    cout << "Sort by Stadium Name - American League Only - Test Requirement 6" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_stadiumname());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getLeague() == "American")
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requirement 7
    cout << "Sort by Team Name - National League Only - Test Requirement 7" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_teamname());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getLeague() == "National")
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requiement 8
    cout << "Sort by Park Typology - Test Requirement 8" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_typology());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
    }
    cout << endl << endl;

    // Test Requirement 9
    cout << "Sort by Team Name - Open Roof Only - Test Requirement 9" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_teamname());
    int count_open = 0;
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getRoofType() == "Open")
        {
            count_open++;
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
        cout << "Number of parks with open roof type is: " << count_open << endl;
    }
    cout << endl << endl;

    // Test Requirement 10
    cout << "Sort by Year Park Opened - Test Requirement 10" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_yearopen());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
    }
    cout << endl << endl;

    // Test Requirement 11
    cout << "Sort by Park Capacity - Test Requirement 11" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_seatcapacity());
    int total_capacity = 0;
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
       total_capacity += (*it).getCapacity();
    }
    cout << "total seating capacity of all MLB parks: " << total_capacity;
    cout << endl << endl;

    // Test Requirement 12
    cout << "Display Park(s) with greatest distance to center field - Test Requirement 12" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_distcenterfield());
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
    }
    cout << "-------------------------------------------" << endl;
    int greatest_distance = 0;
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getCenterField() > greatest_distance)
        {
            greatest_distance = (*it).getCenterField();
        }
    }
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getCenterField() == greatest_distance)
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;

    // Test Requirement 13
    cout << "Display Park(s) with smallest distance to center field - Test Requirement 13" << endl;
    sort(Teams.list.begin(), Teams.list.end(), Cmp_by_seatcapacity());
    int smallest_distance = 9999;
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getCenterField() < smallest_distance)
        {

            smallest_distance = (*it).getCenterField();
        }
    }
    for (std::vector<MLBTeam>::iterator it = Teams.list.begin(); it != Teams.list.end(); ++it)
    {
        if ((*it).getCenterField() == smallest_distance)
        {
            cout << "#" << (*it).getNumber() << "  Team name:" << (*it).getTeamName() << " - Stadium Name: " << (*it).getStadiumName() <<
                    " - Seats: " << (*it).getCapacity() <<  " - Typology: " << (*it).getTypology() << 
                    " - Year Open: " << (*it).getDateOpened() << " - Center Field Distance: " << (*it).getCenterField() << endl;
        }
    }
    cout << endl << endl;
    
#if 0
    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #3 - start at Saddleback, visit 10 Restaurants" << endl;
    int myTrip3x = Trips.StoreTripNumRest("Trip Test Req3", 0, 10, Restaurants, Users.list.front());
    Trip &myTrip3 = Trips.FindbyNumber(myTrip3x);
    myTrip3.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #4 - start at Dominos, visit N (5) Restaurants" << endl;
    int myTrip4x = Trips.StoreTripNumRest("Trip Test Req4", 3, 5, Restaurants, Users.list.front());
    Trip &myTrip4 = Trips.FindbyNumber(myTrip4x);
    myTrip4.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #5a - start at Saddleback, visit selected Restaurants" << endl;
    vector<int> myrests5a = { 2, 6, 3, 1, 8 };
    int myTrip5ax = Trips.StoreTrip("Trip Test Req5a", myrests5a, Restaurants, Users.list.front(), true);
    Trip &myTrip5a = Trips.FindbyNumber(myTrip5ax);
    myTrip5a.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #5b - visit selected Restaurants" << endl;
    vector<int> myrests5b = { 2, 9, 3, 1, 4, 8 };
    int myTrip5bx = Trips.StoreTrip("Trip Test Req5b", myrests5b, Restaurants, Users.list.front(), false);
    Trip &myTrip5b = Trips.FindbyNumber(myTrip5bx);
    myTrip5b.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << "Add  2 more restaurants to Restaurants list" << endl;
    Restaurants.load_additional("./ExtraRestaurantData.csv");
    Restaurants.load("./ExtraStacksRestaurantData.csv", true);  // verify dupes do not get loaded
    Restaurants.save("./RestaurantDataStore.csv.tmp2");
    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #6 - start at Saddleback, visit 12 Restaurants" << endl;
    int myTrip6x = Trips.StoreTripNumRest("Trip Test Req6", 0, 12, Restaurants, Users.list.front());
    Trip &myTrip6 = Trips.FindbyNumber(myTrip6x);
    myTrip6.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    for (MyDblLinkList<User>::iterator it = Users.list.begin(); it != Users.list.end(); ++it)
    {
        cout << "User name:" << (*it).GetName() << " Total Purchases $" << (*it).GetTotalPurchase() << endl;
    }
    cout << endl << endl;                      // range-for-loop to print Restaurants

#endif

    //Users.printAsDebug(true, true);
    //system("ls -l");
}

