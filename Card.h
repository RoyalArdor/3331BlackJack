#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>
#include <array>
#include "math.h"
using namespace std;

class Card {
    friend ostream& operator<<(ostream& os, const Card& c);
public:
    Card(int _faceValue);
    Card(int _faceValue, bool _revealed);
    static vector<int> GetHandValues(vector<Card> h);
    static vector<Card> MakeDeck();
    static void FlipCard(Card& c);
    int GetCardValue() const;
private:
  int faceValue;
  bool revealed = false;
};

#endif
