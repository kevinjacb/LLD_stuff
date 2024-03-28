#include "services.h"

void MakeRoll::roll(Dice &dice, int uid){
    // get a random value for the dice
    int roll = rand() % 6 + 1;
    dice.setValue(roll, uid);
}


void UpdatePlayer::update(Dice dice, vector<Player>& players, Board board){
    int uid = dice.getPlayerUID(),
    rollVal = dice.getValue();

    Player &currentPlayer = players[uid]; // focus on the player in scope
    int currentPosition = currentPlayer.getPosition();
    currentPlayer.updateRolls(); // increment roll count

    // update the position if the new position is valid

    int newPos = currentPosition + rollVal;
    if(newPos <= board.getLastTile()){
        currentPlayer.setPosition(newPos);
    }else{
        //ignore
        return;
    }

    // check if the square where the player landed has a snake
    // or a ladder
    vector<int> snlData = board.getBoardConfig(); // snake and ladder data
    
    if(snlData[newPos] == 0)
        return;

    if(snlData[newPos] < 0)
        cout<<"Oops! "<<currentPlayer.getName()<<" was bitten by a snake!"<<endl;
    else cout<<"Nice! "<<currentPlayer.getName()<<" climbed up a ladder!"<<endl;


    newPos += snlData[newPos]; // if s or l it skips to some other tile, else no change
    currentPlayer.setPosition(newPos);
    cout<<endl;

}


bool CheckMove::check(Dice dice, vector<Player>& players, Board board){
    // check if the latest updated player is a winner.
    int uid = dice.getPlayerUID();

    Player currentPlayer = players[uid];
    int tile = currentPlayer.getPosition();

    if(tile == board.getLastTile()){
        return false;
    }
    return true;

}

void SLGenerator::generateSLConfig(Board &board){
    // generate a random snakes and ladders config for a board

    int rows, columns;
    board.getBoardSize(rows,columns);

    int linkCount = sqrt(rows*columns/2); // number of snakes and ladders

    // randomly pick the number of snakes
    int snakeCount = max(rand() % (linkCount/2), 3),
    ladderCount = max(rand() % (linkCount/2), 3);// and ladders

    vector<int> config(board.getLastTile(),0);

    // generate snakes
    for(int i = 0; i < snakeCount + ladderCount; i++){
        // choose a set of random tiles
        int t1 = rand()%board.getLastTile(),
        t2 = rand()%board.getLastTile();

        if(t1 == t2){
            i--;
            continue;
        }

        if(i < snakeCount){
        // set a snake from the highest to lowest
        // if snake is at the final square, skip
            if(max(t1,t2) == rows * columns){
                i--;
                continue;
            }
            config[max(t1,t2)] = -abs(t1 - t2);
        }
        else{
            // check if there already exists a snake at the top position
            // skip if yes
            if(config[t1] != 0 || config[t2] != 0){
                i--;
                continue;
            }
            // set a ladder from the lowest to highest
            config[min(t1,t2)] = abs(t1 - t2);
        }
    }
    board.setBoardConfig(config);
}

void IO::nextInput(int player){
    // empty for now
}

void IO::readInput(string message, int &input){
    cout<<message<<endl;
    cin >> input;
}

void IO::readInputString(string message, string &input){
    cout<<message<<endl;
    cin >> input;
}

void IO::displayResult(Player player, Board board, Dice dice){
    cout<<endl<<player.getName()<< " rolled a "<< dice.getValue()<<"."<<endl;
    cout<<"Current Position: "<<player.getPosition()<<" Winning square: "<<board.getLastTile()<<endl<<endl;
}

void IO::displayBoardConfig(Board board){

    cout<<"Board configuration is as follows: "<<endl;

    vector<int> boardConfig = board.getBoardConfig();
    for(int i = 0; i < boardConfig.size(); i++){
        if(boardConfig[i] == 0)
            continue;
        if(boardConfig[i] < 0){
            cout<<"Snake from "<<i+1<<" square to "<<i+1+boardConfig[i]<<" square."<<endl;
        }else
            cout<<"Ladder from "<<i+1<<" square to "<<i+1 + boardConfig[i]<< " square."<<endl;
    }
    cout<<endl;
}