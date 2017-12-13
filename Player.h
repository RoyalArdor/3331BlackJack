#ifndef PLAYER_H
#define PLAYER_H
#define INITIAL_BALANCE 1000
#include "User.h"
#include <array>
using namespace std;

class Player : public User {
public:
    Player(int , double = INITIAL_BALANCE);
    void SetBalance(double );
    double GetBalance() const;
    void RemoveBalance(double );
    int GetID() const;
    void AddCard(Card );
    vector<Card> GetHand();
    void AddAnte(double );
    void RemoveAnte(double );
    void SetStatus(Status );
    Status GetStatus() const;
    void AddAnteToBalanceBlackJackWin();
    void AddAnteToBalanceRegularWin();
    void fold();
    void ClearHand();
    void SetAnte(double );
    double GetAnte() const;

private:
    double ante=0;
    double balance=0;
};

#endif
