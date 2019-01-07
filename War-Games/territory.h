#ifndef TERRITORY_H_INCLUDED
#define TERRITORY_H_INCLUDED

#include "player.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;


class territory{
    public:
        ///default
        territory();
        ///constructor with the number of armies and owning player
        territory(int, player*);
        ///destructor
        ~territory();

        ///a function that takes in the number of attacking armies then returns true if taken and false if failed
        bool isTaken(int);
        ///given two armies is calculates the number of armies left after attacking
        int newArmy(bool, int, player*);
        ///a function that adds the two numbers together
        void addArmy(int);

        int getArmies();

        player* getPlayer();
    private:

        ///a variable for the number of armies
        int numArmies;
        player* playerControlled;
};

#endif // TERRITORY_H_INCLUDED
