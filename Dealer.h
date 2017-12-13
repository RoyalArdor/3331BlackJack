#ifndef DEALER_H
#define DEALER_H

#include "User.h"
#include "Card.h"
#include "Player.h"
#include "Dealer.h"
#include <random>
#include <ctime>
using namespace std;

class Dealer : public User {
public:
    Dealer();
    void DealFromDeck(User& player);
    void DeleteFromDeck(int index);
    void ResetShuffleDeck();
    void AddCard(Card card);
    void ClearHand();
    vector<Card> GetHand();
    Card& GetCard(int i);
    int GetDeckSize() const;
    void SetStatus(Status s);
    Status GetStatus() const;
    int GetID() const;

private:
  vector<Card> deck;

};

#endif
