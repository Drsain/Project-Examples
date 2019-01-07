#include "territory.h"

territory::territory(){
}
territory::territory(int a, player* pointer){
    numArmies = a;
    playerControlled = pointer;
}
territory::~territory(){

}

player* territory::getPlayer(){
    return playerControlled;
}

int territory::getArmies(){
    return numArmies;
}

void territory::addArmy(int num){
    numArmies+= num;
}

bool territory::isTaken(int attackingNum){
    if(attackingNum > numArmies){
        return true;
    }
    else{
        return false;
    }
}
int territory::newArmy(bool taken, int attackingNum, player* attackingPlayer){
    if(taken == true){
        (playerControlled->playerStats[3])++;
        (playerControlled->playerStats[5])++;
        playerControlled = attackingPlayer;
        (playerControlled->playerStats[2])++;
        (playerControlled->playerStats[4])++;
        numArmies = attackingNum-numArmies;
        return attackingNum-numArmies;
    }
    else{
        (playerControlled->playerStats[2])++;
        (attackingPlayer->playerStats[3])++;
        numArmies = numArmies-attackingNum;
        return 0;
    }
}
