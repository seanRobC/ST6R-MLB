#ifndef RECIEPT_H
#define RECIEPT_H

#include "mlbteam.h"

using namespace std;

//struct representing a customer's selection at the restaurant, contains an item and the quantity

class reciept
{
public:
    reciept(){Total = 0;}
    ~reciept(){}

    void addVisit(MLBTeam newRestaurant){
        myreciept.push_back(newRestaurant);
    }

    double getTotal()
    {
        Total = 0;
        for(int i = 0; i < myreciept.size(); i++)
        {
            for(int j = 0; j < myreciept[i].getMenuSize(); j++)
            {
                Total += (myreciept[i].getSouvenirPrice(j) * myreciept[i].getItemQuantity(j));
            }
        }

        return Total;
    }

    MLBTeam getLastVisit(){return myreciept.back();}

    MLBTeam getVisit(int key){return myreciept[key];}

    int getRecieptSize(){return myreciept.size();}

private:
    double Total;
    //a vector of selections (items and their quantities), representing our cart
    QVector<MLBTeam> myreciept;
};

#endif // RECIEPT_H
