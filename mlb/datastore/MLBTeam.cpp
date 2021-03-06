#include "MLBTeam.hpp"
#include <vector>
#include <string>
#include <ostream>
#include <iostream>

using namespace std;


MLBTeam::MLBTeam(int number, const string &teamname, const string &parkname,
                 int seatingcapcity, const string &location,
                 const string &surface, const string &league,
                 int yearopen, int distcenterfeet, int distcentermeters,
                 const string typology, const string roof,bool deleted,
                 const vector<TeamEdge> &distances, vector<MLB_Souvenir> &souvenirs,
                 int highestSouvenir)
                 : m_nNumber(number), m_sTeamName(teamname), m_sParkName(parkname),
                   m_nSeatingCapacity(seatingcapcity), m_sLocation(location),
                   m_sPlayingSurface(surface), m_sLeague(league), m_nYearOpened(yearopen),
                   m_nDistCenterFieldFeet(distcenterfeet), m_nDistCenterFieldMeters(distcentermeters),
                   m_sParkTyplolgy(typology), m_sRoofType(roof), m_bDeleted(deleted),
                   m_nHighestSouvenirsNumber(highestSouvenir), m_bVisited(false)
{
    for (int i = 0; i < distances.size(); i++)
    {
        m_Distances.push_back(distances[i]);
    }
    for (int i = 0; i < souvenirs.size(); i++)
    {
        m_Souvenirs.push(souvenirs[i]);  // sorted by name
    }
    m_bInitialized = true;
}

MLBTeam::MLBTeam(const MLBTeam& src)
{
    m_nNumber = src.m_nNumber;
    m_sTeamName = src.m_sTeamName;
    m_sParkName = src. m_sParkName;
    m_nSeatingCapacity = src.m_nSeatingCapacity;
    m_sLocation = src.m_sLocation;
    m_sPlayingSurface = src.m_sPlayingSurface;
    m_sLeague = src.m_sLeague;
    m_nYearOpened = src.m_nYearOpened;
    m_nDistCenterFieldFeet = src.m_nDistCenterFieldFeet;
    m_nDistCenterFieldMeters = src.m_nDistCenterFieldMeters;
    m_sParkTyplolgy = src.m_sParkTyplolgy;
    m_sRoofType = src.m_sRoofType;
    m_bInitialized = src.m_bInitialized;
    m_bDeleted = src.m_bDeleted;
    m_Distances = src.m_Distances;
    m_Souvenirs = src.m_Souvenirs;
    m_nHighestSouvenirsNumber = src.m_nHighestSouvenirsNumber;
}

MLBTeam& MLBTeam::operator=(const MLBTeam& rhs)
{
   if (this == &rhs) {
      return *this;
   }

   m_nNumber = rhs.m_nNumber;
   m_sTeamName = rhs.m_sTeamName;
   m_sParkName = rhs. m_sParkName;
   m_nSeatingCapacity = rhs.m_nSeatingCapacity;
   m_sLocation = rhs.m_sLocation;
   m_sPlayingSurface = rhs.m_sPlayingSurface;
   m_sLeague = rhs.m_sLeague;
   m_nYearOpened = rhs.m_nYearOpened;
   m_nDistCenterFieldFeet = rhs.m_nDistCenterFieldFeet;
   m_nDistCenterFieldMeters = rhs.m_nDistCenterFieldMeters;
   m_sParkTyplolgy = rhs.m_sParkTyplolgy;
   m_sRoofType = rhs.m_sRoofType;
   m_bInitialized = rhs.m_bInitialized;
   m_bDeleted = rhs.m_bDeleted;
   m_Distances = rhs.m_Distances;
   m_Souvenirs = rhs.m_Souvenirs;
   m_nHighestSouvenirsNumber = rhs.m_nHighestSouvenirsNumber;
   m_bVisited = rhs.m_bVisited;
   return *this;
}

bool MLBTeam::PrintAsDebug(bool print_endl, bool print_detail) const
{
    if (m_bInitialized)
    {
        if (print_endl)
        {
            cout << "ObjAddr     :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec << endl
                  << " Number    :" << m_nNumber << endl
                  << " Team Name :" << m_sTeamName << endl
                  << " Park Name :" << m_sParkName << endl
                  << " Capacity  :" << m_nSeatingCapacity << endl
                  << " Surface   :" << m_sPlayingSurface << endl
                  << " League    :" << m_sLeague << endl
                  << " Year Open :" << m_nYearOpened << endl
                  << " Center Ft :" << m_nDistCenterFieldFeet << endl
                  << " Typology  :" << m_sParkTyplolgy << endl
                  << " Roof      :" << m_sRoofType << endl
                  << " Inited    :" << m_bInitialized << endl
                  << " Deleted      :" << m_bDeleted << endl;

                  if (m_Souvenirs.size() > 0)
                  {
                      std::priority_queue<MLB_Souvenir, std::vector<MLB_Souvenir>, SouvenirbyName> Souvenirs = m_Souvenirs;
                      MLB_Souvenir tmp;
                      while (Souvenirs.size() > 0)
                      {
                          tmp = Souvenirs.top();
                          Souvenirs.pop();
                          cout << " #: " << tmp.m_nNumber
                               << " Name: " << tmp.m_sSouvenirName
                               << " Price: "<< tmp.m_fSouvenirPrice
                               << " Deleted: " << tmp.m_bDeleted << endl;
                      }
                  }
        }
        else
        {
            cout << "ObjAddr     :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec
                 << " Number     :" << m_nNumber
                 << " Team Name :" << m_sTeamName
                 << " Park Name :" << m_sParkName
                 << " Capacity  :" << m_nSeatingCapacity
                 << " Surface   :" << m_sPlayingSurface
                 << " League    :" << m_sLeague
                 << " Year Open :" << m_nYearOpened
                 << " Center Ft :" << m_nDistCenterFieldFeet
                 << " Typology  :" << m_sParkTyplolgy
                 << " Roof      :" << m_sRoofType
                 << " Inited    :" << m_bInitialized
                 << " Deleted      :" << m_bDeleted;

                if (m_Souvenirs.size() > 0)
                {
                    std::priority_queue<MLB_Souvenir, std::vector<MLB_Souvenir>, SouvenirbyName> Souvenirs = m_Souvenirs;
                    MLB_Souvenir tmp;
                    while (Souvenirs.size() > 0)
                    {
                        tmp = Souvenirs.top();
                        Souvenirs.pop();
                        cout << " #: " << tmp.m_nNumber
                             << " Name: " << tmp.m_sSouvenirName
                             << " Price: "<< tmp.m_fSouvenirPrice
                             << " Deleted: " << tmp.m_bDeleted;
                    }
                }
                cout << endl;
        }
        return true;
    }

    return false;
}

void MLBTeam::GetSouvenirs(vector<MLB_Souvenir> &souvenirs) const
{
    std::priority_queue<MLB_Souvenir, std::vector<MLB_Souvenir>, SouvenirbyName> Souvenirs = m_Souvenirs;
    MLB_Souvenir tmp;
    while (Souvenirs.size () > 0)
    {
        souvenirs.push_back(Souvenirs.top());
        Souvenirs.pop();
    }
}

void MLBTeam::addSouvenir(const string desc, float price)
{
    MLB_Souvenir tmp(++m_nHighestSouvenirsNumber, desc, price, false);
    m_Souvenirs.push(tmp);
}

bool MLBTeam::deleteSouvenir(int number)
{
    bool retcode = false;
    std::priority_queue<MLB_Souvenir, std::vector<MLB_Souvenir>, SouvenirbyNameRev> RevSouvenirs;
    MLB_Souvenir tmp;
    while (m_Souvenirs.size() > 0 && m_Souvenirs.top().m_nNumber != number)
    {
        retcode = true;
        m_Souvenirs.pop();  // delete the matching entry
        break;
    }
    while (RevSouvenirs.size () > 0)
    {
        tmp = RevSouvenirs.top();
        RevSouvenirs.pop();
        m_Souvenirs.push(tmp);
    }
    return retcode;
}
bool MLBTeam::updateSouvenir(int number, const string desc, float price)
{
    bool retcode = false;
    std::priority_queue<MLB_Souvenir, std::vector<MLB_Souvenir>, SouvenirbyNameRev> RevSouvenirs;
    MLB_Souvenir tmp;
    while (m_Souvenirs.size() > 0 && m_Souvenirs.top().m_nNumber != number)
    {
        retcode = true;
        tmp = m_Souvenirs.top();
        tmp.m_sSouvenirName = desc;
        tmp.m_fSouvenirPrice = price;

        m_Souvenirs.pop();  // delete the matching entry
        m_Souvenirs.push(tmp);  // add back the new entry
        break;
    }
    while (RevSouvenirs.size () > 0)
    {
        tmp = RevSouvenirs.top();
        RevSouvenirs.pop();
        m_Souvenirs.push(tmp);
    }
    return retcode;
}


MLB_Souvenir& MLB_Souvenir::operator=(const MLB_Souvenir& rhs)
{
    if (this == &rhs) {
       return *this;
    }

    m_nNumber        =  rhs.m_nNumber;
    m_bDeleted       =  rhs.m_bDeleted;
    m_sSouvenirName  =  rhs.m_sSouvenirName;
    m_fSouvenirPrice =  rhs.m_fSouvenirPrice;
    m_bInitialized   =  rhs.m_bInitialized;

    return *this;
}

TeamEdge &TeamEdge::operator=(const TeamEdge &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    m_nTeam = rhs.m_nTeam;
    m_nDistance = rhs.m_nDistance;
    m_bVisited = rhs.m_bVisited;
    return *this;
}
