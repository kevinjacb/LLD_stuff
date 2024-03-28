#include "models.h"

Player::Player(int uid, string name) : tile(0), previousTile(-1), rolls(0), uid(uid), name(name){}

int Player::getUID() const{
    return uid;
}

int Player::getPosition() const{
    return tile;
}

string Player::getName() const{
    return name;
}

int Player::getRolls() const{
    return rolls;
}

void Player::setPosition(int tile){
    previousTile = this -> tile;
    this->tile = tile;
}

void Player::updateRolls(){
    rolls++;
}

// BOARD //

Board::Board(){
    rows = 0; columns = 0; lastTile = -1;
    players = 0; playerLimit = 4; // temporarily set to 4 players max
}

Board& Board::getInstance(){
    static Board instance;
    return instance;
}

void Board::setBoardParams(int rows, int columns, int players){
    this -> rows = rows;
    this -> columns = columns;
    this -> players = players;
    playerPositions = vector<int>(players,0);
}

void Board::setBoardConfig(vector<int> config){
    board = config;
}

int Board::updatePlayer(Player player){
    playerPositions[player.getUID()] = player.getPosition();
    return 0;
}

void Board::getBoardSize(int &rows, int &columns) const{
    rows = this -> rows;
    columns = this -> columns;
}

vector<int> Board::getBoardConfig() const{
    return board;
}

int Board::getLastTile() const{
    return rows * columns;   
}


// Dice //

Dice::Dice(){
    value = -1;
    playerUID = -1;
}

Dice& Dice::getInstance(){
    static Dice instance;
    return instance;
}

void Dice::setValue(int value, int playerUID){
    this -> value = value;
    this -> playerUID = playerUID;
}

int Dice::getValue() const{
    return value;
}

int Dice::getPlayerUID() const{
    return playerUID;
}