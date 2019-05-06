#ifndef VACATION_H
#define VACATION_H

#include "mlbteam.h"
#include "reciept.h"
#include <QVector>
#include <QQueue>
#include <QString>
using namespace std;

class vacation{
public:
    //CONSTRUCTOR & DECONSTRUCTOR
    vacation(){name = ""; totalCost = 0; totalDistanceTraveled = 0;}
    vacation(QString t_name, float t_totalCost, float t_totalDistanceTraveled){name = t_name; totalCost = t_totalCost; totalDistanceTraveled = t_totalDistanceTraveled;}
    ~vacation(){}

    //MUTATORS
    void changeName(QString t_name){name = t_name;}
    void addLocation(MLBTeam loc){rList.enqueue(loc);}
    void removeLocation(){rList.dequeue();}
    void setTotalCost(float newTotalCost){totalCost = newTotalCost;}
    void setTotalDistance(float newTotalDistance){totalDistanceTraveled = newTotalDistance;}

    //ACCESSORS
    QString getName()const{return name;}
    MLBTeam getCurrentLocation(){return rList.head();}
    int getVacationSize()const{return rList.size();}
    MLBTeam getLocation(int key)const{return rList[key];}
    float getTotalCost()const{return totalCost;}
    float getTotalDistanceTraveled()const{return totalDistanceTraveled;}


private:
    QQueue<MLBTeam> rList;
    QString name;
    float totalCost;
    float totalDistanceTraveled;
};

#endif // VACATION_H
