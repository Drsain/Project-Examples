#include <iostream>
#include "game.h"
#include "player.h"
#include "territory.h"


using namespace std;

int main(){
    bool valid = false;
    string str;

    while(valid == false){
        cout<<"Welcome to the game!"<<endl;
        cout<<"Would you like to load a save game, or start a new game."<<endl;
        cout<<"Enter a 1 to start a new game, and 2 to load a save game: ";
        getline(cin, str);
        if(str[0] == '2'){
            cout<<"Please enter the name of the save file: ";
            getline(cin, str);
            valid = true;
            for(int i = 0; i < 5; i++){
                cout<<endl;
            }
            game loadGame(str);
        }
        else if(str[0] == '1'){
            cout<<"Please enter the number of players: ";
            getline(cin, str);
            valid = true;
            int players = stoi(str);
            if(players > 4 || players < 1){
                valid = false;
                while(valid == false){
                    cout<<"INVALID INPUT PLEASE TRY AGAIN!!!"<<endl<<endl<<endl;
                    cout<<"Please enter the number of players: ";
                    getline(cin, str);
                    valid = true;
                    int players = stoi(str);
                    if(players > 4 || players < 1){
                        valid = false;
                    }
                }
            }
            for(int i = 0; i < 5; i++){
                cout<<endl;
            }
            game newGame(players);
        }
        else{
            cout<<"INVALID INPUT PLEASE TRY AGAIN!!!"<<endl<<endl<<endl;
            valid = false;
        }
    }


    //for(int i = 0; i < 5; i++){
        //cout<<startGame.playerArray[i].getPlayerName()<< " player" << i << "s name"<<endl;
    //}
    //cout<<startGame.gameBoard[0][0].getPlayer()->getPlayerName()<<endl;
    //cout<<startGame.gameBoard[7][7].getPlayer()->getPlayerName()<<endl;



    return 0;
}
