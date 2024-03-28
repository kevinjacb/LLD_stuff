#include "common.h"
#include "models/models.h"
#include "services/services.h"


int main(){

    ///////// INITIALIZE BOARD AND PLAYERS ////////////////

    // get the size of the board
    int rows, columns;
    IO::readInput("Enter the number of rows.", rows);
    IO::readInput("Enter the number of columns.", columns);

    int playerCount;
    IO::readInput("Enter the number of players", playerCount);

    vector<Player> players;

    // initialize players
    for(int i = 0; i < playerCount; i++){
        string name;
        IO::readInputString("Enter the name of player "+to_string(i)+":", name);
        Player player(i, name);
        players.push_back(player);
    }
    
    // initializze Board
    Board board = Board::getInstance();
    // set board params
    board.setBoardParams(rows, columns, playerCount);
    // generate board config
    SLGenerator::generateSLConfig(board);
    //////////////////////////////////////////////////////

    ///////////////////// DICE ///////////////////////////
    Dice dice = Dice::getInstance(); // singleton

    //////////////////////////////////////////////////////

    ////////////////////// GAME //////////////////////////
    IO::displayBoardConfig(board); // print ladders and snakes

    int currentPlayer = 0;
    while(CheckMove::check(dice, players, board)){ // keep playing till one of the players win
        string ent = players[currentPlayer].getName();
        IO::readInputString("Roll dice for "+ent+" ?",ent);
        
        // roll dice
        MakeRoll::roll(dice, currentPlayer);

        // move the player
        UpdatePlayer::update(dice, players, board);

        // display result of the roll
        IO::displayResult(players[currentPlayer], board, dice);

        // update player
        currentPlayer = (currentPlayer + 1)%players.size();
    }

    //////////////////////////////////////////////////////

    // Display the winner
    currentPlayer = (currentPlayer - 1)%players.size();
    cout<<endl<<players[currentPlayer].getName()<<" wins!!"<<endl;

    return 0;
}