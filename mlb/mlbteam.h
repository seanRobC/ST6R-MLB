#ifndef MLBTEAM_H
#define MLBTEAM_H
#include <QString>
#include <QVector>
using namespace std;

struct item{
    //constructor for easily initializing new items
    item(){}
    item(QString newItemName, double newItemPrice,int newItemQuantity)
    {
        itemName = newItemName;
        price = newItemPrice;
        itemQuantity = newItemQuantity;
    }
    QString itemName;
    double price;
    int itemQuantity;
};

class TeamEdge{
public:
    int m_nTeam;
    int m_nDistance;
    bool m_bVisited;
    bool m_bDiscovery;
    bool m_bBack;
    void ClearVisited(void) { m_bVisited = false; }
    void SetVisited(void) { m_bVisited = true; }
    bool IsVisited(void) { return(m_bVisited); }
    void ClearDiscovered(void) { m_bDiscovery = false; }
    void SetDiscovered(void) { m_bDiscovery = true; }
    void ClearBack(void) { m_bBack = false; }
    void SetBack(void) { m_bBack = true; }
};

class MLBTeam{
public:
    //Constructor
    MLBTeam(){
        teamName    = "";
        stadiumName = "";
        location    = "";
        surface     = "";
        league      = "";
        typelogy    = "";
        roofType    = "";
        id          = 0;
        capacity    = 0;
        dateOpened  = 0;
        centerField = 0;
    }

    MLBTeam(QString a,QString b,QString c,QString d,QString e,QString f,QString g,int h,int i,int j,int k){
        teamName    = a;
        stadiumName = b;
        location    = c;
        surface     = d;
        league      = e;
        typelogy    = f;
        roofType    = g;
        id          = h;
        capacity    = i;
        dateOpened  = j;
        centerField = k;
    }

    ~MLBTeam(){
        teamName    = "";
        stadiumName = "";
        location    = "";
        surface     = "";
        league      = "";
        typelogy    = "";
        roofType    = "";
        id          = 0;
        capacity    = 0;
        dateOpened  = 0;
        centerField = 0;
    }

    //Mutator
    void changeteamName(QString d){teamName = d;}
    void changeStadiumName(QString d){stadiumName = d;}
    void changeLocation(QString d){location = d;}
    void changeSurface(QString d){surface = d;}
    void changeLeague(QString d){league = d;}
    void changeTypelogy(QString d){typelogy = d;}
    void changeRoofType(QString d){roofType = d;}
    void changeId(int d){id = d;}
    void changeCapacity(int d){capacity = d;}
    void changeDateOpened(int d){dateOpened = d;}
    void changeCenterField(int d){centerField = d;}
    void changeSouvenirName(int key,QString d){menu[key].itemName = d;}
    void changeSouvenirPrice(int key,double d){menu[key].price = d;}
    void addMenuItem(QString iName,double iPrice,int iQuan){
        //create new item
        item newItem(iName, iPrice,iQuan);

        //push new item onto the menu
        menu.push_back(newItem);
    }

    void removeMenuItem(int key){
        menu.removeAt(key);
    }
    void addEdge(int d, int q){
        TeamEdge t;
        t.m_nTeam = d;
        t.m_nDistance = q;
        m_Distances.push_back(t);
    }
    void removeEdge(int key){
        m_Distances.remove(key);
    }


    //Accessor
    QString getTeamName(){return teamName;}
    QString getStadiumName(){return stadiumName;}
    QString getLocation(){return location;}
    QString getSurface(){return surface;}
    QString getLeague(){return league;}
    QString getTypelogy(){return typelogy;}
    QString getRoofType(){return roofType;}
    int     getId(){return id;}
    int     getCapacity(){return capacity;}
    int     getDateOpened(){return dateOpened;}
    int     getCenterField(){return centerField;}
    QString getSouvenirName(int key){return menu[key].itemName;}
    double  getSouvenirPrice(int key){return menu[key].price;}
    int     getMenuSize(){return menu.size();}
    int     getItemQuantity(int key){return menu[key].itemQuantity;}
    int     getEdgeSize(){return m_Distances.size();}
    int     getEdgeId(int key){return m_Distances[key].m_nTeam;}
    int     getEdgeDistance(int key){return m_Distances[key].m_nDistance;}

private:
    QString teamName;
    QString stadiumName;
    QString location;    //City Name, State Name
    QString surface;     //Grass or astroturf
    QString league;      //Either National or American
    QString typelogy;    //Either Retro Modern, Retro Classic, Jewel Box, Contemporary, or Multipurpose
    QString roofType;    //Either Retractable, Fixed, or Open
    int id;
    int capacity;
    int dateOpened;
    int centerField;     //distance to center field
    QVector<item> menu;
    QVector<TeamEdge> m_Distances;
};

#endif // MLBTEAM_H
