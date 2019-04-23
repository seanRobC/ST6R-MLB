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

// used to describe the distance (edges) between Teams/Parks
class TeamEdge
{
public:
    int m_nTeam;
    int m_nDistance;
    bool m_bVisited;
    bool m_bDiscovery;
    bool m_bBack;
    void ClearVisited(void) { m_bVisited = false; };
    void SetVisited(void) { m_bVisited = true; };
    bool IsVisited(void) { return(m_bVisited); };
    void ClearDiscovered(void) { m_bDiscovery = false; };
    void SetDiscovered(void) { m_bDiscovery = true; };
    void ClearBack(void) { m_bBack = false; };
    void SetBack(void) { m_bBack = true; };
};

class MLB_Souvenir
{
public:
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

class MLBTeam
{
friend class TeamDataStore;
public:
    // Constructor
    MLBTeam() { m_nNumber = -1; m_bInitialized = false; };

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
    void updateSouvenirs(const vector<MLB_Souvenir> &souvenirs) { m_Souvenirs = souvenirs; };

    // Helper functions for maintenance
    bool IsDeleted(void) const {return m_bDeleted;};
    bool SetDeleted(bool deleted) {return (m_bDeleted = deleted);}
    bool PrintAsDebug(bool print_endl, bool print_detail) const;

    // Souvenir Accessors
    const vector<MLB_Souvenir> &GetSouvenirs(void) const {return m_Souvenirs;};
    void addSouvenir(const string desc, float price);
    bool deleteSouvenir(int number);
    bool updateSouvenir(int number, const string desc, float price);
        

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
    vector<MLB_Souvenir> m_Souvenirs;
    int     m_nHighestSouvenirsNumber;


    // private members to prevent use

    // Constructor - used by TeamDataSttore class as a friend to create
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
