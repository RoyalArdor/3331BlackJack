#ifndef USER_H
#define USER_H
#include "card.h"
#include <vector>
class User {
  public:
    virtual void AddCard(Card)=0;
    virtual vector<Card> GetHand()=0;
  protected:
    vector<Card> hand;
};

#endif
