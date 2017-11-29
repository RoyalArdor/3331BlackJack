#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "User.h"
using namespace std;
#define INITIAL_BALANCE 1000    //Initial Balance of players in a new game
#define MINIMUM_BET 5           //Minimum bet allowed for each player
#define MAXIMUM_BET 100         //Maximum bet allowed for each player
//Players that play against the Dealer
class Player : public User{
public:
    Player(int b = INITIAL_BALANCE){
        _balance = b;
    }

    void setBalance(int b){ _balance = b;}

private:
    int _balance;
};

#endif
