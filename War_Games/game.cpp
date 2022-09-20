#include "game.h"

int split(string str, char checker, string words[], int array_size){
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

game::game(){
}
game::game(int np){
    numPlayers = np;
    string str;
    cout<<"Please enter the size of the game board by x,y with a max of 5,5 and min 3,3 (must be a square): ";
    getline(cin,str);
    string splitInput[2];
    split(str,',',splitInput,2);
    string input0 = splitInput[0];
    string input1 = splitInput[1];
    if((input0[0] >= '3' && input0[0] <= '5') && (input1[0] >= '3' && input1[0] <= '5') && (input0 == input1)){
        xSize = stoi(input0);
        //cout<<xSize<<endl;
        ySize = stoi(input1);
        //cout<<ySize<<endl;
    }
    else{
        bool valid = false;
        while(valid == false){
            cout<<"INVALID INPUT PLEASE TRY AGAIN!!!"<<endl<<endl<<endl;
            cout<<"Please enter the size of the game board by x,y with a max of 5,5 and min 3,3 (must be a square): ";
            getline(cin,str);
            string splitInput[2];
            split(str,',',splitInput,2);
            string input0 = splitInput[0];
            string input1 = splitInput[1];
            if((input0[0] >= '3' && input0[0] <= '5') && (input1[0] >= '3' && input1[0] <= '5')){
                valid = true;
                xSize = stoi(input0);
                //cout<<xSize<<endl;
                ySize = stoi(input1);
                //cout<<ySize<<endl;
            }
            else{
                valid = false;
            }
        }
    }
    for(int i = 0; i < numPlayers; i++){
        string str;
        cout<<"Please enter a player name, or ";
        cout<<"enter load to load an existing player: ";
        getline(cin, str);
        if(str == "load"){
            cout<<"Please enter the file the player was saved to: ";
            string fileName;
            getline(cin, fileName);
            playerArray[i] = player(fileName);
        }
        else{
            playerArray[i] = player(str, i);
        }
    }
    for(int i = numPlayers; i < 4; i++){
        playerArray[i] = player("cpu", i);
    }
    playerArray[4] = player("neutral", 4);
    for(int i = 0; i < ySize; i++){
        for(int j = 0; j < xSize; j++){
            gameBoard[i][j] = territory(0, &playerArray[4]);
        }
    }
    gameBoard[0][0] = territory(5, &playerArray[0]);
    gameBoard[0][ySize-1] = territory(5, &playerArray[1]);
    gameBoard[xSize-1][0] = territory(5, &playerArray[2]);
    gameBoard[xSize-1][ySize-1] = territory(5, &playerArray[3]);

    cout<<"Press M at any time to enter the game menu."<<endl;
    turn();
}
game::game(string fileName){
    cout<<"Press M at any time to enter the game menu."<<endl;
    loadGame(fileName);
    turn();
}
game::~game(){
}

int game::getX(){
    return xSize;
}
int game::getY(){
    return ySize;
}

int game::menuCheck(string input){
    ResetColor();
    char m = input[0];
    m = toupper(m);
    int rVal;
    if(m == 'M'){
        bool valid = false;
        while(valid == false){
            cout<<"This is the menu"<<endl;
            cout<<"Menu options: "<<endl;
            cout<<setw(5)<<"\t type S to save game" <<endl;
            cout<<setw(5)<<"\t type R to return to current game" <<endl;
            cout<<setw(5)<<"\t type Q to quit current game" <<endl;
            cout<<setw(5)<<"\t type W to save a player"<<endl;
            cout<<setw(5)<<"\t type P to show a player's stats"<<endl;
            cout<<setw(5)<<"\t other options coming in later versions"<<endl;
            string str;
            getline(cin, str);
            m = 'M';
            m = str[0];
            m = toupper(m);
            if(m == 'R'){
                valid = true;
                return 0;
            }
            else if(m == 'S'){
                valid = true;
                cout<<"Please enter a name to save the game information to (no spaces allowed): "<<endl;
                getline(cin,str);
                string w[1];
                split(str,' ', w,1);
                saveGame(w[0]);
                return 0;
            }
            else if(m == 'Q'){
                valid = true;
                for(int i = 0; i < xSize; i++){
                    for(int j = 0; j < ySize; j++){
                        gameBoard[i][j].newArmy(true,1000,&playerArray[4]);
                    }
                }
                return 1;
            }
            else if(m == 'W'){
                while(valid == false){
                    cout<<"Please enter the name of the player"<<endl;
                    getline(cin,str);
                    if(str != "cpu"){
                        for(int i = 0; i < 4 && valid == false; i++){
                            if(playerArray[i].getPlayerName() == str){
                                cout<<"Please enter a name to save the file to (no spaces allowed): "<<endl;
                                getline(cin,str);
                                string w[1];
                                split(str,' ', w,1);
                                playerArray[i].savePlayerStats(w[0]);
                                valid = true;
                            }
                            else if(i == 3){
                                cout<<"INVALID INPUT PLEASE TRY AGAIN"<<endl;
                            }
                        }
                    }
                    else{
                        cout<<"INVALID INPUT PLEASE TRY AGAIN"<<endl;
                    }
                }

                valid = true;
            }
            else if(m == 'P'){
                while(valid == false){
                    cout<<"Please enter the name of the player"<<endl;
                    getline(cin,str);
                    if(str != "cpu"){
                        for(int i = 0; i < 4 && valid == false; i++){
                            if(playerArray[i].getPlayerName() == str){
                                playerArray[i].showPlayerStats();
                                valid = true;
                            }
                            else if(i == 3){
                                cout<<"INVALID INPUT PLEASE TRY AGAIN"<<endl;
                            }
                        }
                    }
                    else{
                        cout<<"INVALID INPUT PLEASE TRY AGAIN"<<endl;
                    }
                }
            }
            else{
                valid = false;
            }
        }
    }
}

bool game::saveGame(string fileName){
    //cout<<"In save game function"<<endl;
    ofstream myFile("/home/user/Dropbox/Assignments/Assingment8/");
    fileName += ".txt";
    myFile.open(fileName.c_str());
    //cout<<"opened the file"<<endl;
    myFile<<numPlayers<<"\n"<<over<<"\n"<<xSize<<"\n"<<ySize<<"\n";
    for(int i = 0; i < 5; i++){
        myFile<<playerArray[i].getPlayerNumber()<<"\n"<<playerArray[i].getPlayerName()<<"\n";
    }
    cout<<"after player writing"<<endl;
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            myFile<<gameBoard[i][j].getPlayer()->getPlayerNumber()<<"\n"<<gameBoard[i][j].getArmies()<<"\n";
        }
    }
    cout<<"after game board writing"<<endl;

    myFile.close();
    cout<<"closed the file"<<endl;
    return true;
}
void game::loadGame(string fileName){
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
    numPlayers = stoi(lines[cl]);
    cl++;
    if(stoi(lines[cl]) == 1){
        cout<<"ERROR this game is already done!!!"<<endl;
    }
    else{
        over = false;
    }
    cl++;

    xSize = stoi(lines[cl]);
    cl++;
    ySize = stoi(lines[cl]);
    cl++;
    int num;
    for(int i = 0; i < 5; i++){
        string str;
        for(int j = 0; j < 2; j++){
            if(j == 0){
                num = stoi(lines[cl]);
            }
            else{
                str = lines[cl];
            }
            cl++;
        }
        playerArray[i] = player(str, num);
    }

    int armies;
    player* pc;
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            for(int t = 0; t < 2; t++){
                if(t == 0){
                    num =  stoi(lines[cl]);
                }
                else{
                    armies = stoi(lines[cl]);
                }
                cl++;
            }
            for(int t = 0; t < 5; t++){
                if(num == playerArray[t].getPlayerNumber()){
                    pc = &playerArray[t];
                }
            }
            //cout<<"territory "<<i<<" "<<j<<" with armies numbered at "<<armies<<" controlled by player number"<<pc->getPlayerNumber()<<endl;
            gameBoard[i][j] = territory(armies, pc);
        }
    }
}

///enum = enumerated value. Its like a list of things and an object. The variables are all AttrCode,
///but they are set to the values inside the enum.
enum AttrCode {
	FG_RED      = 31,
	FG_GREEN    = 32,
	FG_YELLOW	= 33,
	FG_BLUE     = 34,
	FG_DEFAULT  = 39,
	FG_PURPLE   = 35,
};
///the change color function takes in a AttrCode then uses the number to print a color
///it does this the same way of doing \t, the \x1b[#m just replaces the number
///with what has been passed in and will now format the output so that
///everything will now print with whatever attribute the number was calling
void ChangeColor(AttrCode color){
		cout << "\x1B["<< color <<"m";
}
void game::FindNewColor(int i){
    if(i == 0){
        ChangeColor(FG_BLUE);
    }
    else if(i == 1){
        ChangeColor(FG_GREEN);
    }
    else if(i == 2){
        ChangeColor(FG_YELLOW);
    }
    else if(i == 3){
        ChangeColor(FG_RED);
    }
    else if(i ==4){
        ChangeColor(FG_PURPLE);
    }
    else{
        ChangeColor(FG_DEFAULT);
    }
}
void game::ResetColor(){
    ChangeColor(FG_DEFAULT);
}

void game::coutBoard(){
    FindNewColor(8);
    for(int i = 0; i < 5; i++){
        cout<<"Player ";
        FindNewColor(i);
        cout<<playerArray[i].getPlayerName();
        ResetColor();
        cout<<" is color = ";
        FindNewColor(i);
        cout<<playerArray[i].getPlayerColor() << endl;
        ResetColor();
    }

    cout<< "X values: ";
    for(int i = 0; i < xSize; i++){
        cout<<"\t"<<i+1;
    }
    cout<<endl<<endl;
    for(int i = 0; i < xSize; i++){
        cout<<"Y value:   " <<i+1<<"\t";
        for(int j = 0; j < ySize; j++){
            int t = gameBoard[i][j].getPlayer()->getPlayerNumber();
            FindNewColor(t);
            cout<< gameBoard[i][j].getArmies();
            cout<<"\t";
            ResetColor();
        }
        cout<<endl<<endl<<endl;
    }
}
bool game::isOver(){
    //cout<<"Is over function"<<endl;
    int tester = gameBoard[0][0].getPlayer()->getPlayerNumber();
    bool over1 = true;
    bool over2 = false;
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            if(tester != gameBoard[i][j].getPlayer()->getPlayerNumber()){
                over1 = false;
            }
        }
    }
    //cout<<"between if statements"<<endl;
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            for(int t = 0; t < numPlayers; t++){
                if(gameBoard[i][j].getPlayer()->getPlayerNumber() == playerArray[t].getPlayerNumber()){
                    over2 = true;
                }
            }
        }
    }
    //cout<<"after if statements"<<endl;

    if(over1 == false && over2 == true){
        over = false;
        return over;
    }
    else if (over1 == true && over2 == true && over == false){
        ResetColor();
        cout<<"Congratulations you won the game!!!"<<endl;
        over = true;
        (gameBoard[0][0].getPlayer()->playerStats[0])++;
        return true;
    }
    else if(over2 == false && over == false){
        ResetColor();
        cout<<"You were eliminated you lost the game"<<endl;
        over = true;
        for(int i = 0; i < numPlayers; i++){
            (playerArray[i].playerStats[1])++;
        }
        return true;
    }
}

void game::turn(){
    //while(over == false){
        //cpuTurn(1,playerArray[1]);
      //  isOver();
      //  endTurn();
    //}
    //coutBoard();
    while(over == false){
        int countUsers = 0;
        for(int i = 0; i < 4; i++){
            if(playerArray[i].getPlayerName() != "cpu" && over == false){
                userTurn(playerArray[i]);
                countUsers++;
            }
            else if(over == false){
                cpuTurn(i-countUsers+1, playerArray[i]);
            }
        }
        isOver();
        endTurn();
    }
}
void game::endTurn(){
    for(int i = 0; i < xSize; i++){
        for(int j = 0; j < ySize; j++){
            if(gameBoard[i][j].getPlayer()->getPlayerNumber() != 4){
                gameBoard[i][j].addArmy(1);
            }
        }
    }
    for(int i = 0; i < 10; i++){
        cout<<endl;
    }
}
void game::userTurn(player currentPlayer){
    int i = 0;
    while(i < 3 && over == false){
        bool valid = false;
        ResetColor();
        cout<<"The current game board: "<<endl;
        coutBoard();
        string input;
        string inputSeperated[2];
        int startingCoordinates[2];
        int finishingCoordinates[2];
        int armies;
        FindNewColor(currentPlayer.getPlayerNumber());
        cout<<"This is your "<<i+1<<" turn out of 3. ";
        cout<<"Please enter a Y to continue taking your turns, and a N to stop" <<endl;
        getline(cin, input);
        int rVal = 2;
        rVal = menuCheck(input);
        FindNewColor(currentPlayer.getPlayerNumber());
        if(rVal == 1){
            ResetColor();
            over = true;
            break;
        }
        char in = input[0];
        in = toupper(in);
        if(in == 'Y' && over == false){
            cout<<"Select a territory to move armies from by typing a x value and a y value separated by a comma: "<<endl;
            getline(cin, input);
            rVal = menuCheck(input);
            FindNewColor(currentPlayer.getPlayerNumber());
            if(rVal == 1){
                ResetColor();
                over = true;
                break;
            }
            split(input,',',inputSeperated,2);
            string input0 = inputSeperated[0];
            string input1 = inputSeperated[1];
            input0 = input0[0];
            input1 = input1[0];
            if((input0[0] >= '0' && input0[0] <= '9') &&  (input1[0] >= '0' && input1[0] <= '9')){
                startingCoordinates[0] = stoi(input0)-1;
                startingCoordinates[1] = stoi(input1)-1;
                if((startingCoordinates[1] >= 0 && startingCoordinates[1] < xSize) && (startingCoordinates[0] >= 0 && startingCoordinates[1] < ySize)){
                    valid = true;
                }
            }
            if(valid == false){
                while(valid == false && over == false){
                    cout<<"Error not a correct input"<<endl;
                    cout<<endl;
                    cout<<"Select a territory to move armies from by typing a x value and a y value separated by a comma: "<<endl;
                    getline(cin, input);
                    rVal = menuCheck(input);
                    FindNewColor(currentPlayer.getPlayerNumber());
                    if(rVal == 1){
                        ResetColor();
                        over = true;
                        break;
                    }
                    split(input,',',inputSeperated,2);
                    string input0 = inputSeperated[0];
                    string input1 = inputSeperated[1];
                    input0 = input0[0];
                    input1 = input1[0];
                    if((input0[0] >= '0' && input0[0] <= '9') &&  (input1[0] >= '0' && input1[0] <= '9')){
                        startingCoordinates[0] = stoi(input0)-1;
                        startingCoordinates[1] = stoi(input1)-1;
                        if((startingCoordinates[1] >= 0 && startingCoordinates[1] < xSize) && (startingCoordinates[0] >= 0 && startingCoordinates[1] < ySize)){
                            valid = true;
                        }
                    }
                    else{
                        valid = false;
                    }
                }
                valid = false;
            }
            if(over == false){
                cout<<"Select a territory to move armies to by typing a x value and a y value separated by a comma: "<<endl;
                getline(cin, input);
                rVal = menuCheck(input);
                FindNewColor(currentPlayer.getPlayerNumber());
                if(rVal == 1){
                    ResetColor();
                    over = true;
                    break;
                }
                split(input,',',inputSeperated,2);
                input0 = inputSeperated[0];
                input1 = inputSeperated[1];
                input0 = input0[0];
                input1 = input1[0];
                if((input0[0] >= '0' && input0[0] <= '9') &&  (input1[0] >= '0' && input1[0] <= '9')){
                    finishingCoordinates[0] = stoi(input0)-1;
                    finishingCoordinates[1] = stoi(input1)-1;
                    if((finishingCoordinates[1] >= 0 && finishingCoordinates[1] < xSize) && (finishingCoordinates[0] >= 0 && finishingCoordinates[1] < ySize)){
                        valid = true;
                    }
                }
                if(valid == false){
                    while(valid == false && over == false){
                        cout<<"Error not a correct input"<<endl;
                        cout<<endl;
                        cout<<"Select a territory to move armies to by typing a x value and a y value separated by a comma: "<<endl;
                        getline(cin, input);
                        rVal = menuCheck(input);
                        FindNewColor(currentPlayer.getPlayerNumber());
                        if(rVal == 1){
                            ResetColor();
                            over = true;
                            break;
                        }
                        split(input,',',inputSeperated,2);
                        input0 = inputSeperated[0];
                        input1 = inputSeperated[1];
                        input0 = input0[0];
                        input1 = input1[0];
                        if((input0[0] >= '0' && input0[0] <= '9') &&  (input1[0] >= '0' && input1[0] <= '9')){
                            finishingCoordinates[0] = stoi(input0)-1;
                            finishingCoordinates[1] = stoi(input1)-1;
                            if((finishingCoordinates[1] >= 0 && finishingCoordinates[1] < xSize) && (finishingCoordinates[0] >= 0 && finishingCoordinates[1] < ySize)){
                                valid = true;
                            }
                        }
                        else{
                            valid = false;
                        }
                    }
                    valid = false;
                }
            }
            if(over == false){
                cout<<"Select the number of armies to move: "<<endl;
                getline(cin, input);
                rVal = menuCheck(input);
                FindNewColor(currentPlayer.getPlayerNumber());
                if(rVal == 1){
                    ResetColor();
                    over = true;
                    break;
                }
                if(input[0] >= '0' && input[0] <= '9'){
                    armies = stoi(input);
                }
                else{
                    while(valid == false && over == true){
                        cout<<"Error not a correct input"<<endl;
                        cout<<endl;
                        cout<<"Select the number of armies to move: "<<endl;
                        getline(cin, input);
                        rVal = menuCheck(input);
                        FindNewColor(currentPlayer.getPlayerNumber());
                        if(rVal == 1){
                            ResetColor();
                            over = true;
                            break;
                        }
                        if(input[0] >= '0' && input[0] <= '9'){
                            armies = stoi(input);
                            valid = true;
                        }
                        else{
                            valid = false;
                        }
                    }
                    valid = false;
                }
            }

            territory* startingTerritory = &gameBoard[startingCoordinates[1]][startingCoordinates[0]];
            territory* endingTerritory = &gameBoard[finishingCoordinates[1]][finishingCoordinates[0]];

            valid = false;
            ///using their own territory
            if(startingTerritory->getPlayer()->getPlayerName() == currentPlayer.getPlayerName()){
                cout<<"First if"<<endl;
                if(startingTerritory->getArmies() > armies){
                    cout<<"Second if"<<endl;
                    ///moving to a territory next to starting
                    if( (startingCoordinates[0] + 1 == finishingCoordinates[0] || startingCoordinates[0] - 1 == finishingCoordinates[0]) || (startingCoordinates[1] + 1 == finishingCoordinates[1] || startingCoordinates[1] - 1 == finishingCoordinates[1])){
                        cout<<"Third if"<<endl;
                        valid = true;
                        ///seeing if what they want is to transfer armies
                        if(endingTerritory->getPlayer()->getPlayerNumber() == currentPlayer.getPlayerNumber()){
                            startingTerritory->addArmy(-armies);
                            endingTerritory->addArmy(armies);
                        }
                        else{
                            startingTerritory->addArmy(-armies);
                            bool taken = endingTerritory->isTaken(armies);
                            if(taken == true){
                                endingTerritory->newArmy(taken, armies, startingTerritory->getPlayer());
                            }
                            else{
                                endingTerritory->newArmy(taken, armies, startingTerritory->getPlayer());
                            }
                        }
                    }
                }
            }
        }
        else if(in == 'N'){
            //cout<<"inside N"<<endl;
            i = 3;
            valid=true;
        }
        if(valid == false && over == false){
            cout<<"invalid output please try again"<<endl;
            i+=-1;
        }
        i++;
    }
}
void game::cpuTurn(int currentCPU, player currentPlayer){
    cout<<"Inside cpu turn #"<< currentCPU <<endl;

    for(int t = 0; t < 3; t++){
        int i = 0, j = 0;
        bool territoryfound = false;
        while(i < xSize){
            j = 0;
            while(j < ySize){
                if(gameBoard[i][j].getPlayer()->getPlayerNumber() == currentPlayer.getPlayerNumber()){
                    cout<<"Found a owned territory"<<endl;
                    if(gameBoard[i][j].getArmies() > 1){
                        cout<<"Territory had more than one army"<<endl;
                        territoryfound = true;
                    }
                }
                j++;
            }
            i++;
        }
        if(territoryfound == false){
            t = 4;
            break;
        }
        bool validChoice = false;
        territory* startingTerritory = &gameBoard[0][0];
        territory* endingTerritory = &gameBoard[0][0];
        int numArmies = 0;
        i = 0, j = 0;
        ///srand is the random seed, and it takes its seed from time. The null makes sure that the time is always the current time.
        ///This makes sure that the random numbers will always be different, and never the same for multiple times running the
        ///program
        srand(time(NULL));
        cout<<"finding a place to move from"<<endl;
        while(validChoice == false){
            i = rand() % xSize;
            j = rand() % ySize;
            if(gameBoard[i][j].getPlayer()->getPlayerNumber() == currentPlayer.getPlayerNumber()){
                if(gameBoard[i][j].getArmies() > 1){
                    startingTerritory = &gameBoard[i][j];
                    validChoice = true;
                }
            }
        }
        cout<<"found place " << i << " " << j << " to move from"<<endl;
        int x = 0, y = 0;
        validChoice = false;
        cout<<"finding a place to move to"<<endl;
        while(validChoice == false){
            x = rand() % 3 + -1;
            y = rand() % 3 + -1;
            if((x == 0 && y == 0) || (x == -1 && y == -1) || (x == 1 && y == 1)){
                validChoice = false;
            }
            else{
                if((i+x >= 0 && i+x < xSize) && (j+y >= 0 && j+y < ySize)){
                    validChoice = true;
                }
            }
        }
        cout<<"moving to place " << i+x << " " << j+y << endl;
        endingTerritory = &gameBoard[i+x][j+y];

        cout<<"here";
        int totalArmies = startingTerritory->getArmies();
        cout<<"here";
        numArmies = rand() % (totalArmies-1) + 1;
        cout<<"moving " << numArmies << endl;

        if(endingTerritory->getPlayer()->getPlayerNumber() == currentPlayer.getPlayerNumber()){
            startingTerritory->addArmy(-numArmies);
            endingTerritory->addArmy(numArmies);
        }
        else{
            startingTerritory->addArmy(-numArmies);
            bool taken = endingTerritory->isTaken(numArmies);
            if(taken == true){
                cout<<"Taken true"<<endl;
                endingTerritory->newArmy(taken, numArmies, startingTerritory->getPlayer());
                cout<<"New owner of territory is " << endingTerritory->getPlayer()->getPlayerName() << " " << endingTerritory->getPlayer()->getPlayerNumber()<<endl;
            }
            else{
                cout<<"Taken false"<<endl;
                endingTerritory->newArmy(taken, numArmies, startingTerritory->getPlayer());
            }
        }
        cout<<"The current game board: "<<endl;
        coutBoard();
    }
}


