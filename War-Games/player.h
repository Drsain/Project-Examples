#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

class player{
    public:
        ///default
        player();
        ///constructor with the name of a file to read in player stats
        player(string, int);
        player(string);
        ///destructor
        ~player();

        int playerStats[6];

        ///arrays of territories controlled for a player
        //territory controlled[50][50];

        ///a function that sets the player's name
        string getPlayerName();
        int getPlayerNumber();
        string getPlayerColor();

        ///functions that read in a player's stats from a file, save a player's stats to a file and then shows the players stats to the consul.
        void savePlayerStats(string);
        void getPlayerStats(string);
        void showPlayerStats();
    private:
        ///the player name
        string playerName;
        int playerNumber;
        string playerColor;

        ///array that hold the player's stats


};

#endif // PLAYER_H_INCLUDED
