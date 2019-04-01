#ifndef __MLBTEAM_H_INCL__
#define __MLBTEAM_H_INCL__

/**
 * Contains information about a MLB Team and their Ballpark 
 * including available souvenirs
 * 
 * @author   edt
 */
class MLBTeam
{
public:
    // Constructor
    MLBTeam();

    // Destructor
    virtual ~MLBTeam();

    // Copy constructor
    MLBTeam(const MLBTeam& src);

    // Assignment operator
    MLBTeam& operator=(const MLBTeam& src);
private:
    static  int NextNumber;
    int     m_nNumber;
    string  m_sTeamName;
    string  m_sParkName;
    int     m_nSeatingCapcity;
    string  m_sLocation;
    string  m_sPlayingSuface;
    string  m_sLeague;
    int     m_nYearOpened;
    int     m_nDistCenterFieldFeet;
    int     m_nDistCenterFieldMeters;
    string  m_sParkToplolgy;
    string  m_sRoofType;
    bool    m_bInitialized;
    bool    m_bDeleted;
    vector<int> m_Distances;
    vector<MLBSouvenir> m_Souvenirs;
    vector<int> m_Vacations;
    vector<int> m_VisitedbyUsers;
};

// Constructor implementation
inline MLBTeam::MLBTeam()
{
}

// Destructor implementation
inline MLBTeam::~MLBTeam()
{
}

// TODO: Uncomment the copy constructor when you need it.
//inline MLBTeam::MLBTeam(const MLBTeam& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline MLBTeam& MLBTeam::operator=(const MLBTeam& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}

#endif // __MLBTEAM_H_INCL__
