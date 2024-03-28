#ifndef SERVICES_H
#define SERVICES_H

#include "../common.h"
#include "../models/models.h"

class MakeRoll{ // makes a random dice roll
    public:
        static void roll(Dice &dice, int uid);
};

class UpdatePlayer{ // updates the player state
    public:
        static void update(Dice dice, vector<Player>& players,Board board); // updates the relevant player
};

class CheckMove{ // checks the states of all the players
    public:
        static bool check(Dice dice, vector<Player>& players,Board board); // returns false when the game ends
};

class IO{ // handles user input
    public:
        static void nextInput(int player);
        static void readInput(string message, int &input);
        static void readInputString(string message, string &input);
        static void displayResult(Player player, Board board, Dice dice);
        static void displayBoardConfig(Board board);
};

class SLGenerator{ //  generates the snakes and ladders randomly
    /*
        normal = 0
        ladder = +tile ** how many tiles ahead 
        snake = -tile ** how many tiles behind
    */
    public:
        static void generateSLConfig(Board &board);
};

#endif