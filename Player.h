#ifndef PLAYER_H
#define PLAYER_H
#define INITIAL_BALANCE 1000
#include "user.h"
#include <array>

using namespace std;

class Player : public User {
  public:
    Player(int i){
      id=i;
      balance = INITIAL_BALANCE;
      status = Status::INITIAL;
    }

    void SetBalance(double _balance) {
      if(_balance > 0){
        balance = _balance;
      }
    }

    double GetBalance() const {return balance;}

    void RemoveBalance(double d){
      if(d>0){balance -= d;}
    }

    int GetID() const {return id;}

    void AddCard(Card card){
      Card::FlipCard(card);
      hand.push_back(card);
    }



    vector<Card> GetHand(){return hand;}
    
    void AddAnte(double a){
    // cout << "Player " << id << " ante: " << a << endl; 
    balance -= a; 
    ante += a;
    }

    void RemoveAnte(double a){
    // cout << "Player " << id << " ante: " << a << endl; 
    balance += a; 
    ante -= a;
    }

    void SetStatus(Status s) {status = s;}
    Status GetStatus() const{return status;}

    void AddAnteToBalanceBlackJackWin() {
        balance += (ante + ante*1.5);
    }

    void AddAnteToBalanceRegularWin() {
        balance += (ante + ante*1.5);
    }

    void fold(){
      balance += ante/2;
      ante=0;
      status = Status::FOLD;
    }
    void ClearHand(){
      hand.clear();
    }
    void SetAnte(double a){ante = a;}
    double GetAnte() const {return ante;}

  private:
    int id;
    double ante=0;
    double balance=0;
};
#endif