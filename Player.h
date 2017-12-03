#ifndef PLAYER_H
#define PLAYER_H
#define INITIAL_BALANCE 1000
#include "user.h"

using namespace std;

class Player : public User {
  public:
    Player(int i){
      id=i;
      balance = INITIAL_BALANCE;
    }

    void SetBalance(int _balance) {
      if(_balance > 0){
        balance = _balance;
      }
    }

    int GetBalance() const {return balance;}
    int GetID() const {return id;}
    void AddCard(Card card){
      Card::FlipCard(card);
      hand.push_back(card);
    }

    vector<Card> GetHand(){return hand;}
    
    void SetAnte(int a){
    // cout << "Player " << id << " ante: " << a << endl; 
    balance -= a; 
    ante = a;
    }
  private:
    int id;
    int ante=0;
    int balance=0;
    bool disable = false;
};
#endif