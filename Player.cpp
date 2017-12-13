#include "User.h"
#include "Player.h"
#include <array>
using namespace std;

Player::Player(int i, double b){
    id=i;
    SetBalance(b);
    SetStatus(Status::INITIAL);
}

void Player::SetBalance( double _balance) {
    if(_balance > 0){
        balance = _balance;
    }
}

double Player::GetBalance() const {return balance;}

void Player::RemoveBalance(double d){
    if(d>0){balance -= d;}
}

int Player::GetID() const {return id;}

void Player::AddCard(Card card){
    Card::FlipCard(card);
    hand.push_back(card);
}

vector<Card> Player::GetHand(){return hand;}

void Player::AddAnte(double a){
    // cout << "Player " << id << " ante: " << a << endl;
    balance -= a;
    ante += a;
}

void Player::RemoveAnte(double a){
    // cout << "Player " << id << " ante: " << a << endl;
    balance += a;
    ante -= a;
}

void Player::SetStatus(Status s) {status = s;}
Status Player::GetStatus() const{return status;}

void Player::AddAnteToBalanceBlackJackWin() {
    balance += (ante + ante*1.5);
    ante = 0;
}

void Player::AddAnteToBalanceRegularWin() {
    balance += (2*ante);
    ante = 0;
}

void Player::fold(){
    balance += ante/2;
    ante=0;
    status = Status::FOLD;
}

void Player::ClearHand(){
    hand.clear();
}

void Player::SetAnte(double a){ante = a;}
double Player::GetAnte() const {return ante;}
