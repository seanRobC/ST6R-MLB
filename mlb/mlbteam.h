#ifndef MLBTEAM_H
#define MLBTEAM_H
#include <QString>
#include <QVector>
using namespace std;

struct item{
    //constructor for easily initializing new items
    item(){}
    item(QString newItemName, double newItemPrice)
    {
        itemName = newItemName;
        price = newItemPrice;
    }
    QString itemName;
    double price;
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
    void addMenuItem(QString iName,double iPrice){
        //create new item
        item newItem(iName, iPrice);

        //push new item onto the menu
        menu.push_back(newItem);
    }

    void removeMenuItem(int key){
        menu.removeAt(key);
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
};

#endif // MLBTEAM_H
