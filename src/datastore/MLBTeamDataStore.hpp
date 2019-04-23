/**
 * CS1D - MLB
 *
 * Defines a data storage mechanism for Team objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#pragma once

#include "MLBTeam.hpp"
#include <list>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//! TeamDataStore - internal storage for Team objects
//!
//! \author edt (3/25/19)
class TeamDataStore
{
public:
    // Constructor
    TeamDataStore();

    // Destructor
    virtual ~TeamDataStore();

    void printAsDebug(bool printeol, bool printcontent) const;
    MLBTeam &FindbyNumber(int Number);
    std::vector<MLBTeam>::const_iterator getBeginIterator(void) {return list.cbegin();};
    std::vector<MLBTeam>::const_iterator getEndIterator(void) {return list.cend();};

    void load(const string path, bool ItemsAreAdditional = false);
    void save(const string path);
    void load_additional(const string path);

    std::vector<MLBTeam> list;

private:
    bool DuplicateNumPresent(int Number);

    // Copy constructor
    TeamDataStore(const TeamDataStore& src);

    // Assignment operator
    TeamDataStore& operator=(const TeamDataStore& src); } ;
