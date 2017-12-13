#ifndef USER_H
#define USER_H
#include "card.h"
#include <vector>
enum class Status{INITIAL,STAY, HIT, FOLD, DOUBLEDDOWN, BUST, WAITING, WIN, TIE, LOSE, LOWBALANCE};

class User {
  public:
    virtual void AddCard(Card)=0;
    virtual vector<Card> GetHand()=0;
    virtual void SetStatus(Status)=0;
    virtual Status GetStatus() const =0;
    virtual int GetID() const =0;
    virtual void ClearHand()=0;
  protected:
    vector<Card> hand;
    Status status;
    int id;
};

#endif
