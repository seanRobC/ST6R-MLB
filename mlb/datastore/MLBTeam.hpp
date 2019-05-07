#ifndef __MLBTEAM_H_INCL__
#define __MLBTEAM_H_INCL__

/**
 * Contains information about a MLB Team and their Ballpark 
 * including available souvenirs
 * 
 * @author   edt
 */

 #include <vector>
 #include <queue>
 #include <string>

using namespace std;

struct EdgeGreater;
struct EdgeGreaterRev;

//! TeamEdge Class - used to describe the distance (edges) between Teams/Parks
//!
//! \author edt (5/6/19)
class TeamEdge
{
public:
    int m_nTeam;
    int m_nDistance;
    bool m_bVisited;
    //! TeamEdge - default constructor
    //!
    //! \author edt (5/6/19)
    TeamEdge()
      : m_nTeam(0), m_nDistance(0), m_bVisited(false) {};

    //! TeamEdge - constuctor used to load distances from the CSV file
    //!
    //! \author edt (5/6/19)
    //!
    //! \param teamx - team number
    //! \param distancex - dictance to that team's stadium
    TeamEdge(int teamx, int distancex)
      : m_nTeam(teamx), m_nDistance(distancex), m_bVisited(false) {};

    //! TeamEdge Copy constructor
    //!
    //! \author edt (5/6/19)
    //!
    //! \param src - item to be duplicated
    TeamEdge(const TeamEdge &src)
    : m_nTeam(src.m_nTeam), m_nDistance(src.m_nDistance), m_bVisited(src.m_bVisited) {};

    //! TeamEdge - operator =
    //!
    //! \author edt (5/6/19)
    //!
    //! \param rhs - Item being duplicated
    //!
    //! \return TeamEdge&amp; 
    TeamEdge &operator=(const TeamEdge &rhs);

    //! ClearVisited - marks this edge not visited for DFS and BFS traversals
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    void ClearVisited(void) { m_bVisited = false; };

    //! SetVisited - marks this edge visted for DFS/BFS traversals
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    void SetVisited(void) { m_bVisited = true; };

    //! IsVisited - determines if this edge visited
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return bool - true if visited, false otherwise
    bool IsVisited(void) { return(m_bVisited); };
};

//! EdgeGreater - function object used to sort TeamEdges by ascending distance
//!
//! \author edt (5/6/19)
struct EdgeGreater
{
    bool operator()(const TeamEdge &s1, const TeamEdge &s2) const
    {
        return s1.m_nDistance > s2.m_nDistance;
    }
};

//! EdgeGreaterRev - function object used to sort TeamEdges by descending distance
//!
//! \author edt (5/6/19)
struct EdgeGreaterRev
{
    bool operator()(const TeamEdge &s1, const TeamEdge &s2) const
    {
        return s1.m_nDistance < s2.m_nDistance;
    }
};

//! MLB_Souvenir class - stores number, name, price of Souvenirs
//!
//! \author edt (5/6/19)
class MLB_Souvenir
{
public:
    //! MLB_Souvenir default constructor
    //!
    //! \author edt (5/6/19)
    MLB_Souvenir()
      :  m_bInitialized(false) {};
 
    //! MLB_Souvenir - used to load Souvenirs from csv data store
    //!
    //! \author edt (5/6/19)
    //!
    //! \param number 
    //! \param name 
    //! \param price 
    //! \param deleted 
    MLB_Souvenir(const int number, const string &name,
                 const float price, const bool deleted)
        : m_nNumber(number), m_bDeleted(deleted),
          m_sSouvenirName(name), m_fSouvenirPrice(price),
          m_bInitialized(true) {};

    ~MLB_Souvenir() {};

    //! MLB_Souvenir copy constructor
    //!
    //! \author edt (5/6/19)
    //!
    //! \param src - item being duplicated
    MLB_Souvenir( MLB_Souvenir const &src)
      : m_nNumber(src.m_nNumber), m_bDeleted(src.m_bDeleted),
        m_sSouvenirName(src.m_sSouvenirName), m_fSouvenirPrice(src.m_fSouvenirPrice),
        m_bInitialized(src.m_bInitialized) {};

    //! MLB_Souvenir - operator =
    //!
    //! \author edt (5/6/19)
    //!
    //! \param rhs - item being duplicated
    //!
    //! \return MLB_Souvenir&amp; 
    MLB_Souvenir& operator=(const MLB_Souvenir& rhs);

    int     m_nNumber;
    string  m_sSouvenirName;
    float   m_fSouvenirPrice;
    bool    m_bDeleted;
    bool    m_bInitialized;
};

//! SouvenirbyName - used to sort by name (ascending) for the priority_queue
//!
//! \author edt (5/6/19)
struct SouvenirbyName
{
    bool operator()(const MLB_Souvenir &s1, const MLB_Souvenir &s2)
    {
        return s1.m_sSouvenirName > s2.m_sSouvenirName;
    }
};

//! SouvenirbyNameRev- used to sort by name (descending) for the priority_queue
//!
//! \author edt (5/6/19)
struct SouvenirbyNameRev
{
    bool operator()(const MLB_Souvenir &s1, const MLB_Souvenir &s2)
    {
        return s1.m_sSouvenirName < s2.m_sSouvenirName;
    }
};

//! MLBTeam - contains information about a team and its Stadium, available souvenirs, and distances to other stadiums
//!
//! \author edt (5/6/19)
class MLBTeam
{
friend class TeamDataStore;
public:
    //! MLBTeam default constructor
    //!
    //! \author edt (5/6/19)
    MLBTeam()
     : m_nNumber(0), m_bInitialized(false) { std::vector<TeamEdge> x; m_Distances = x; };

    // Destructor
    ~MLBTeam() {};

    // Copy constructor
    MLBTeam(const MLBTeam& src);

    // Assignment operator
    MLBTeam& operator=(const MLBTeam& rhs);

    // Getters

    //! getNumber - returns team number
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return int - team number
    int           getNumber(void)   const { return m_nNumber; };

    //! getTeamName - returns team name
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp; - team name
    const string &getTeamName(void) const { return m_sTeamName; };

    //! getStadiumName - returns stadium name
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp; - stadium name
    const string &getStadiumName(void) const{return m_sParkName;};

    //! getCapacity - returns stadium capacity
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return int - stadium capacity
    int           getCapacity(void) const { return m_nSeatingCapacity; };

    //! getLocation - returns city and state of stadium
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp; - city and state of stadium
    const string &getLocation(void) const {return m_sLocation;};

    //! getSurface - returns stadium surface type
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp; - stadium surface type
    const string &getSurface(void) const {return m_sPlayingSurface;};

    //! getLeague - returns MLB (National, American) the team plays in
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp; - MLB (National, American) the team plays in
    const string &getLeague(void) const {return m_sLeague;};

    //! getDateOpened - returns year park opened
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return int - year park opened
    int           getDateOpened(void) const { return m_nYearOpened; };

    //! getCenterField - returns distance in feet to center field wall
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return int - distance in feet to center field wall
    int           getCenterField(void) const { return m_nDistCenterFieldFeet; };
    int           getDistCenterFieldFeet (void) const { return m_nDistCenterFieldFeet; };
    int           getDistCenterFieldMeters(void) const { return m_nDistCenterFieldMeters; };

    //! getTypology - returns type of stadium
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp; -type of stadium 
    const string &getTypology(void) const {return m_sParkTyplolgy;};

    //! getRoofType - returns type of roof on stadium
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return const string&amp;  - type of roof on stadium
    const string &getRoofType(void) const {return m_sRoofType;};

    const vector<TeamEdge> &GetDistances(void) const { return m_Distances; };

    // Setters

    //! updateTeamName sets new team name
    //!
    //! \author edt (5/6/19)
    //!
    //! \param name - new team name
    void updateTeamName(const string &name) { m_sTeamName = name; };

    //! updateStadiumName - sets new stadium name
    //!
    //! \author edt (5/6/19)
    //!
    //! \param park - new stadium name
    void updateStadiumName(const string &park) { m_sParkName = park; };

    //! updateCapacity - sets new stadium capacity
    //!
    //! \author edt (5/6/19)
    //!
    //! \param capacity - new stadium capacity
    void updateCapacity(int capacity) { m_nSeatingCapacity = capacity; };

    //! updateLocation - sets new stadium location city/state
    //!
    //! \author edt (5/6/19)
    //!
    //! \param location - new stadium location city/state
    void updateLocation(const string &location) { m_sLocation = location; };

    //! updateSurface - sets new stadium surface
    //!
    //! \author edt (5/6/19)
    //!
    //! \param surface - new stadium surface
    void updateSurface(const string &surface) { m_sPlayingSurface = surface; };

    //! updateLeague - sets new MLB designation
    //!
    //! \author edt (5/6/19)
    //!
    //! \param league - new MLB designation
    void updateLeague(const string &league) { m_sLeague = league; };

    //! updateDateOpened - sets new date opened
    //!
    //! \author edt (5/6/19)
    //!
    //! \param opened - new date opened
    void updateDateOpened(int opened) { m_nYearOpened = opened; };

    //! updateCenterField - set new center field distance in feet
    //!
    //! \author edt (5/6/19)
    //!
    //! \param centerfield new center field distance in feet
    void updateCenterField(int centerfield) { m_nDistCenterFieldFeet = centerfield; m_nDistCenterFieldMeters = (int)(centerfield * 0.330f); };
    void updateDistCenterFieldFeet (int centerfieldft) { m_nDistCenterFieldFeet = centerfieldft; };
    void updateDistCenterFieldMeters(int centerfieldmtrs) { m_nDistCenterFieldMeters =centerfieldmtrs; };

    //! updateTypology - set new stadium typeology
    //!
    //! \author edt (5/6/19)
    //!
    //! \param typology - new stadium typeology
    void updateTypology(const string &typology) { m_sParkTyplolgy = typology; };

    //! updateRoofType - set new stadium roof type
    //!
    //! \author edt (5/6/19)
    //!
    //! \param roof - new stadium roof type
    void updateRoofType(const string &roof) { m_sRoofType = roof; };

    // Helper functions for maintenance
    //! IsDeleted - query if team deleted and should not display in UI
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return bool - true if team deleted and should not display in UI
    bool IsDeleted(void) const {return m_bDeleted || m_bInitialized;};

    //! SetDeleted - set team deleted status
    //!
    //! \author edt (5/6/19)
    //!
    //! \param deleted - team deleted status
    //!
    //! \return bool - team deleted status
    bool SetDeleted(bool deleted) {return (m_bDeleted = deleted);}

    //! PrintAsDebug - prints state of team object
    //!
    //! \author edt (5/6/19)
    //!
    //! \param print_endl 
    //! \param print_detail 
    //!
    //! \return bool - true if object printed
    bool PrintAsDebug(bool print_endl, bool print_detail) const;

    // Souvenir Accessors
    //!
   
    //! GetSouvenirs - returns a vector of Souvenirs
    //!
    //! \author edt (5/6/19)
    //!
    //! \param souvenirs - vector of Souvenirs
    void GetSouvenirs(vector<MLB_Souvenir> &souvenirs) const;

    //! addSouvenir - add a new Souvenir
    //!
    //! \author edt (5/6/19)
    //!
    //! \param desc - description
    //! \param price - price
    void addSouvenir(const string desc, float price);

    //! deleteSouvenir - deleets a Souvenir
    //!
    //! \author edt (5/6/19)
    //!
    //! \param number - souvenir number
    //!
    //! \return bool - true if deleted
    bool deleteSouvenir(int number);

    //! updateSouvenir - updates an existing Souvenir
    //!
    //! \author edt (5/6/19)
    //!
    //! \param number - number used to locate item ti be updates
    //! \param desc - new description
    //! \param price - new price
    //!
    //! \return bool - true if update succeeded 
    bool updateSouvenir(int number, const string desc, float price);

    // DFS and BFS helpers

    //! ClearVisited - clear DFS/BFS visited flag
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    void ClearVisited(void) { m_bVisited = false; };

    //! SetVisited - sets DFS/BFS visited flag
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    void SetVisited(void) { m_bVisited = true; };

    //! IsVisited - query if visited during traversal
    //!
    //! \author edt (5/6/19)
    //!
    //! \param void 
    //!
    //! \return bool - true if visited
    bool IsVisited(void) { return(m_bVisited); };

    //! ClearVisited - clears visited flag on a specific edge
    //!
    //! \author edt (5/6/19)
    //!
    //! \param edge - edge number to clear
    void ClearVisited(int edge) { m_Distances[edge].m_bVisited = false; };


    //! SetVisited - sets visited flag on a specific edge
    //!
    //! \author edt (5/6/19)
    //!
    //! \param edge - edge number to set
    void SetVisited(int edge) { m_Distances[edge].m_bVisited = true; };

    //! IsEdgeVisited - query if this edge visited during traversal
    //!
    //! \author edt (5/6/19)
    //!
    //! \param edge - number to query
    //!
    //! \return bool - true if visited
    bool IsEdgeVisited(int edge) { return(m_Distances[edge].m_bVisited); };

    //! GetDistance - get the distance for this edge
    //!
    //! \author edt (5/6/19)
    //!
    //! \param edge - number to query
    //!
    //! \return int - edge distance
    int GetDistance(int edge) { return(m_Distances[edge].m_nDistance); };

    //! GetAdjacentCity - get adjacent team number for this edge
    //!
    //! \author edt (5/6/19)
    //!
    //! \param edge - edge number to query
    //!
    //! \return int - adjacent team number 
    int GetAdjacentCity(int edge) { return(m_Distances[edge].m_nTeam); };
        

private:
    static  int NextNumber;
    int     m_nNumber;
    string  m_sTeamName;
    string  m_sParkName;
    int     m_nSeatingCapacity;
    string  m_sLocation;
    string  m_sPlayingSurface;
    string  m_sLeague;
    int     m_nYearOpened;
    int     m_nDistCenterFieldFeet;
    int     m_nDistCenterFieldMeters;
    string  m_sParkTyplolgy;
    string  m_sRoofType;
    bool    m_bInitialized;
    bool    m_bDeleted;
    vector<TeamEdge> m_Distances;
    std::priority_queue<MLB_Souvenir, std::vector<MLB_Souvenir>, SouvenirbyName> m_Souvenirs;
    int     m_nHighestSouvenirsNumber;
    bool    m_bVisited;


    // private members to prevent use

    // Constructor - used by TeamDataStore class as a friend to create
    // restaurant objects from input file
    MLBTeam(int number, const string &teamname, const string &parkname,
            int seatingcapcity, const string &location,
            const string &surface, const string &league,
            int yearopen, int distcenterfeet, int distcentermeters,
            const string typology, const string roof,bool deleted,
            const vector<TeamEdge> &distances, vector<MLB_Souvenir> &souvenirs,
            int highestSouvenir);
};


//! Cmp_by_teamnumber - function object used to sort MLBTeams by ascending number
//!
//! \author edt (5/6/19)
struct Cmp_by_teamnumber {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getNumber() < s2.getNumber());
    }
};

//! Cmp_by_teamname - function object used to sort MLBTeams by ascending team name
//!
//! \author edt (5/6/19)
struct Cmp_by_teamname {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getTeamName() < s2.getTeamName());
    }
};

//! Cmp_by_stadiumname - function object used to sort MLBTeams by ascending stadium name
//!
//! \author edt (5/6/19)
struct Cmp_by_stadiumname {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getStadiumName() < s2.getStadiumName());
    }
};

//! Cmp_by_seatcapacity - function object used to sort MLBTeams by ascending number of seats
//!
//! \author edt (5/6/19)
struct Cmp_by_seatcapacity {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getCapacity() < s2.getCapacity());
    } 
};

//! Cmp_by_seatcapacityrev - function object used to sort MLBTeams by decending number of seats
//!
//! \author edt (5/6/19)
struct Cmp_by_seatcapacityrev {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getCapacity() > s2.getCapacity());
    } 
};

//! Cmp_by_typology - function object used to sort MLBTeams by ascending park typology
//!
//! \author edt (5/6/19)
struct Cmp_by_typology {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getTypology() < s2.getTypology());
    } 
};

//! Cmp_by_yearopen - function object used to sort MLBTeams by ascending year park opened
//!
//! \author edt (5/6/19)
struct Cmp_by_yearopen {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getDateOpened() < s2.getDateOpened());
    } 
};

//! Cmp_by_distcenterfield - function object used to sort MLBTeams by ascending distance to center field
//!
//! \author edt (5/6/19)
struct Cmp_by_distcenterfield {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getCenterField() < s2.getCenterField());
    } 
};

#endif // __MLBTEAM_H_INCL__
