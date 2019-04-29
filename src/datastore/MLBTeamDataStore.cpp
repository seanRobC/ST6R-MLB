/**
 * CS1D - MLB
 *
 * Implements a data storage mechanism for User objects. These
 * objects are contained in a doubly linked list that supports
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

using namespace std;

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
                    while(it < (8 + 2*nDistances))
                    {
                        tmp.m_nTeam = std::stoi(commaSeparated[it]);
                        tmp.m_nDistance = std::stof(commaSeparated[it+1]);
                        tmp.m_bVisited = false;
                        tmp.m_bDiscovery = false;
                        tmp.m_bBack = false;
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
                list.push_back(*pTeam);
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
        for (std::vector<MLBTeam>::iterator it = list.begin(); it != list.end(); it++)
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
                for (std::vector<MLB_Souvenir>::const_iterator itm = (*it).m_Souvenirs.begin();
                                                           itm != (*it).m_Souvenirs.end(); itm++)
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
    for (std::vector<MLBTeam>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            return *it;
        }
    }
    return *(list.end());  // never reached  - should throw exception
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
    for (std::vector<MLBTeam>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            dupe_found = true;
            break;
        }
    }
    return dupe_found;
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
    for (std::vector<MLBTeam>::const_iterator it = list.begin(); it != list.end(); ++it)
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


