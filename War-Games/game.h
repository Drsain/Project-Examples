#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "player.h"
#include "territory.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

class game{
    public:
        ///default
        game();
        ///a game with the number of users
        game(int);
        ///a game with a save file
        game(string);
        ///destructor
        ~game();

        ///the array of players
        player playerArray[5];
        ///the array of territories
        territory gameBoard[8][8];

        ///a function to save a game
        bool saveGame(string);
        ///a function to load a game
        void loadGame(string);

        ///a function that sets the size of the board
        void setSize(int,int);
        ///a function that gets the individual sizes of the board
        int getX();
        int getY();

        ///a function that ends the current turn
        void endTurn();

        ///a function that is called each turn. It takes in the name of the current player then lets the player decide what to do. It calls other functions until the turn limit has been reached, then calls the endTurn function.
        void turn();

        ///a function that is called during turn 5 times to figure out what the user wants to do
        void userTurn(player);
        ///a function that is called during turn 5 times and randomly does something for the cpu
        void cpuTurn(int, player);

        ///a function that checks the controlled array in the player class for each player to see if they have complete control of the map. If they do it returns true and the game is over
        bool isOver();

        void coutBoard();

        void FindNewColor(int);
        void ResetColor();

        int menuCheck(string);

    private:
        int xSize,ySize,numPlayers;
        bool over = false;
};

#endif // GAME_H_INCLUDED
