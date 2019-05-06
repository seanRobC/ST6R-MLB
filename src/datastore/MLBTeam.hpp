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

// used to describe the distance (edges) between Teams/Parks
class TeamEdge
{
public:
    int m_nTeam;
    int m_nDistance;
    bool m_bVisited;
    TeamEdge()
      : m_nTeam(0), m_nDistance(0), m_bVisited(false) {};
    TeamEdge(int teamx, int distancex)
      : m_nTeam(teamx), m_nDistance(distancex), m_bVisited(false) {};
    TeamEdge(const TeamEdge &src)
    : m_nTeam(src.m_nTeam), m_nDistance(src.m_nDistance), m_bVisited(src.m_bVisited) {};
    TeamEdge &operator=(const TeamEdge &rhs);
    void ClearVisited(void) { m_bVisited = false; };
    void SetVisited(void) { m_bVisited = true; };
    bool IsVisited(void) { return(m_bVisited); };
};

struct EdgeGreater
{
    bool operator()(const TeamEdge &s1, const TeamEdge &s2) const
    {
        return s1.m_nDistance > s2.m_nDistance;
    }
};

struct EdgeGreaterRev
{
    bool operator()(const TeamEdge &s1, const TeamEdge &s2) const
    {
        return s1.m_nDistance < s2.m_nDistance;
    }
};

class MLB_Souvenir
{
public:
    MLB_Souvenir()
      :  m_bInitialized(false) {};
 
    MLB_Souvenir(const int number, const string &name,
                 const float price, const bool deleted)
        : m_nNumber(number), m_bDeleted(deleted),
          m_sSouvenirName(name), m_fSouvenirPrice(price),
          m_bInitialized(true) {};

    ~MLB_Souvenir() {};

    MLB_Souvenir( MLB_Souvenir const &src)
      : m_nNumber(src.m_nNumber), m_bDeleted(src.m_bDeleted),
        m_sSouvenirName(src.m_sSouvenirName), m_fSouvenirPrice(src.m_fSouvenirPrice),
        m_bInitialized(src.m_bInitialized) {};

    MLB_Souvenir& operator=(const MLB_Souvenir& rhs);

    int     m_nNumber;
    string  m_sSouvenirName;
    float   m_fSouvenirPrice;
    bool    m_bDeleted;
    bool    m_bInitialized;
};

struct SouvenirbyName
{
    bool operator()(const MLB_Souvenir &s1, const MLB_Souvenir &s2)
    {
        return s1.m_sSouvenirName > s2.m_sSouvenirName;
    }
};

struct SouvenirbyNameRev
{
    bool operator()(const MLB_Souvenir &s1, const MLB_Souvenir &s2)
    {
        return s1.m_sSouvenirName < s2.m_sSouvenirName;
    }
};

class MLBTeam
{
friend class TeamDataStore;
public:
    // Constructor
    MLBTeam()
     : m_nNumber(0), m_bInitialized(false) { std::vector<TeamEdge> x; m_Distances = x; };

    // Destructor
    ~MLBTeam() {};

    // Copy constructor
    MLBTeam(const MLBTeam& src);

    // Assignment operator
    MLBTeam& operator=(const MLBTeam& rhs);

    // Getters
    int           getNumber(void)   const { return m_nNumber; };
    const string &getTeamName(void) const { return m_sTeamName; };
    const string &getStadiumName(void) const{return m_sParkName;};
    int           getCapacity(void) const { return m_nSeatingCapacity; };
    const string &getLocation(void) const {return m_sLocation;};
    const string &getSurface(void) const {return m_sPlayingSurface;};
    const string &getLeague(void) const {return m_sLeague;};
    int           getDateOpened(void) const { return m_nYearOpened; };
    int           getCenterField(void) const { return m_nDistCenterFieldFeet; };
    int           getDistCenterFieldFeet (void) const { return m_nDistCenterFieldFeet; };
    int           getDistCenterFieldMeters(void) const { return m_nDistCenterFieldMeters; };
    const string &getTypology(void) const {return m_sParkTyplolgy;};
    const string &getRoofType(void) const {return m_sRoofType;};

    const vector<TeamEdge> &GetDistances(void) const { return m_Distances; };

    // Setters
    void updateTeamName(const string &name) { m_sTeamName = name; };
    void updateStadiumName(const string &park) { m_sParkName = park; };
    void updateCapacity(int capacity) { m_nSeatingCapacity = capacity; };
    void updateLocation(const string &location) { m_sLocation = location; };
    void updateSurface(const string &surface) { m_sPlayingSurface = surface; };
    void updateLeague(const string &league) { m_sLeague = league; };
    void updateDateOpened(int opened) { m_nYearOpened = opened; };
    void updateCenterField(int centerfield) { m_nDistCenterFieldFeet = centerfield; m_nDistCenterFieldMeters = (int)(centerfield * 0.330f); };
    void updateDistCenterFieldFeet (int centerfieldft) { m_nDistCenterFieldFeet = centerfieldft; };
    void updateDistCenterFieldMeters(int centerfieldmtrs) { m_nDistCenterFieldMeters =centerfieldmtrs; };
    void updateTypology(const string &typology) { m_sParkTyplolgy = typology; };
    void updateRoofType(const string &roof) { m_sRoofType = roof; };
    // not used - void updateSouvenirs(const vector<MLB_Souvenir> &souvenirs) { m_Souvenirs = souvenirs; };

    // Helper functions for maintenance
    bool IsDeleted(void) const {return m_bDeleted;};
    bool SetDeleted(bool deleted) {return (m_bDeleted = deleted);}
    bool PrintAsDebug(bool print_endl, bool print_detail) const;

    // Souvenir Accessors
    void GetSouvenirs(vector<MLB_Souvenir> &souvenirs) const;
    void addSouvenir(const string desc, float price);
    bool deleteSouvenir(int number);
    bool updateSouvenir(int number, const string desc, float price);

    // DFS and BFS helpers
    void ClearVisited(void) { m_bVisited = false; };
    void SetVisited(void) { m_bVisited = true; };
    bool IsVisited(void) { return(m_bVisited); };
    void ClearVisited(int edge) { m_Distances[edge].m_bVisited = false; };
    void SetVisited(int edge) { m_Distances[edge].m_bVisited = true; };
    bool IsEdgeVisited(int edge) { return(m_Distances[edge].m_bVisited); };
    int GetDistance(int edge) { return(m_Distances[edge].m_nDistance); };
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


struct Cmp_by_teamnumber {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getNumber() < s2.getNumber());
    }
};

struct Cmp_by_teamname {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getTeamName() < s2.getTeamName());
    }
};

struct Cmp_by_stadiumname {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getStadiumName() < s2.getStadiumName());
    }
};

struct Cmp_by_seatcapacity {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getCapacity() < s2.getCapacity());
    } 
};

struct Cmp_by_seatcapacityrev {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getCapacity() > s2.getCapacity());
    } 
};

struct Cmp_by_typology {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getTypology() < s2.getTypology());
    } 
};

struct Cmp_by_yearopen {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getDateOpened() < s2.getDateOpened());
    } 
};

struct Cmp_by_distcenterfield {
    bool operator()(MLBTeam &s1, MLBTeam &s2) const
    {
        // dereference pointer, compare ids
        return (s1.getCenterField() < s2.getCenterField());
    } 
};

#endif // __MLBTEAM_H_INCL__
