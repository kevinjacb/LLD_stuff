#ifndef MODELS_H
#define MODELS_H

#include "../common.h"
using namespace std;

class Player{
    private:
        int tile, previousTile; // current tile, previous tile
        int rolls; // number of times the player has rolled
        int uid; // id of the player
        string name;
    public:
        Player(int uid, string name);
        int getUID() const;
        int getPosition() const;
        int getRolls() const;
        string getName() const;
        void setPosition(int tile);
        void updateRolls();
};

class Board{ // singleton class
    private:
        int rows, columns, lastTile; // size of the board
        int players, playerLimit; // number of players
        vector<int> playerPositions; // positions of all the players
        vector<int> board; // used for maintaining the positions of all the snakes n ladders
        Board(); // private constructor
    public:
        static Board& getInstance(); // retrieves the instanciated object
        void setBoardParams(int rows, int columns, int players); // size and number of players
        void setBoardConfig(vector<int> config); // updates the snakes and ladders of the game;
        int updatePlayer(Player player); // updates the board data of a player
        void getBoardSize(int& rows, int& columns) const;
        vector<int> getBoardConfig() const; // get board setup
        int getLastTile() const;
};

class Dice{ // singleton class
    private:
        int value; // value of the current play
        int playerUID; // who played the dice
        Dice();
    public:
        static Dice& getInstance();
        void setValue(int value, int playerUID); // set dice value
        int getValue() const; // get dice roll value
        int getPlayerUID() const;
};


#endif