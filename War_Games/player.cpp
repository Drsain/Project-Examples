#include "player.h"

int Split(string str, char checker, string words[], int array_size){
    string subsent;
    int c = 0;
    int j = 0;
    int count = 0;
    string tester = checker + str + checker;
    if(str.length() != 0){
        for(int i = 0; i < tester.length(); i++){
            if(tester[i] == checker && i != 0){
                subsent = tester.substr((c+1),(i-c-1));
                //cout << subsent << endl;
                //cout << i << endl;
                if(subsent.length() > 0){
                    words[j] = subsent;
                    count++;
                    j++;
                }
                c = i;
            }
        }
        return count;
    }
    else{
        return 0;
    }
}


player::player(){
    playerName = "";
}
player::player(string n, int pn){
    playerName = n;
    playerNumber = pn;
    if(pn == 0){
        playerColor = "Blue";
    }
    else if(pn == 1){
        playerColor = "Green";
    }
    else if(pn == 2){
        playerColor = "Yellow";
    }
    else if(pn == 3){
        playerColor = "Red";
    }
    else{
        playerColor = "Normal";
    }
    for(int i = 0; i < 6; i++){
        playerStats[i] = 0;
    }
}
player::player(string fileName){
    getPlayerStats(fileName);
}
player::~player(){
}

string player::getPlayerName(){
    return playerName;
}
int player::getPlayerNumber(){
    return playerNumber;
}
string player::getPlayerColor(){
    return playerColor;
}


void player::getPlayerStats(string fileName){
    ifstream dataFile;
    fileName += ".txt";
    dataFile.open(fileName.c_str());

    int count = 0;
    string str;
    string lines[100];
    while(getline(dataFile, str)){
        lines[count] = str;
        count++;
    }
    dataFile.close();

    int cl = 0;
    for(int i = 0; i < 6; i++){
        playerStats[i] = stoi(lines[cl]);
        cl++;
    }
    playerName = lines[cl];
    cl++;
    playerNumber = stoi(lines[cl]);
    cl++;
    playerColor = lines[cl];
    cl++;
}
void player::savePlayerStats(string fileName){
    cout<<"In save player"<<endl;
    ofstream myFile;
    fileName += ".txt";
    myFile.open(fileName.c_str());
    if(myFile.fail() == true){
        cout<<"Failed"<<endl;
    }

    for(int i = 0; i < 6; i++){
        myFile<<playerStats[i]<< "\n";
    }

    myFile<<playerName<< "\n"<<playerNumber<<"\n"<<playerColor<<"\n";
    myFile.close();
    cout<<"saved the player"<<endl;
}
void player::showPlayerStats(){
    cout<<"Player: " << playerName <<endl;
    cout<<"Games won: " << playerStats[0] <<endl;
    cout<<"Games lost: "<< playerStats[1] <<endl;
    cout<<"Battles won: " << playerStats[2] <<endl;
    cout<<"Battles lost: "<<playerStats[3] <<endl;
    cout<<"Territories captured: "<<playerStats[4] <<endl;
    cout<<"Territories lost: " << playerStats[5] <<endl;
}
