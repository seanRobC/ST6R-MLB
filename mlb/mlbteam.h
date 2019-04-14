#ifndef MLBTEAM_H
#define MLBTEAM_H
#include <QString>
#include <QVector>
using namespace std;

struct item{
    //constructor for easily initializing new items
    item(){}
    item(QString newItemName, float newItemPrice, int newItemId)
    {
        itemName = newItemName;
        price = newItemPrice;
        itemId = newItemId;
    }
    QString itemName;
    float price;
    int itemId;
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
    void addMenuItem(QString iName,float iPrice,int iId){
        //create new item
        item newItem(iName, iPrice, iId);

        //push new item onto the menu
        menu.push_back(newItem);
    }

    void removeMenuItem(int key){
        bool found = false;
        int count = 0;

        while(!found && count < menu.size()){
            if(key == menu[count].itemId){
                found = true;
                menu.remove(count);
            }
            count++;
        }
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
