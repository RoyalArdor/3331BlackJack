#ifndef DEALER_H
#define DEALER_H
#include "user.h"
#include "card.h"
#include "player.h"
#include <random>
using namespace std;

class Dealer : public User{
  public:
    Dealer(){
      deck = Card::MakeDeck();
    }
    
    void DealFromDeck(User& player){
      int deckSize = static_cast<int>(deck.size());
      int randIndex = rand()%deckSize;
      // cout << "dealing card from deck: " 
      //   << deck.at(randIndex).GetCardValue() 
      //   << endl;

      player.AddCard(deck.at(randIndex));
      DeleteFromDeck(randIndex);
    }

    void DeleteFromDeck(int index){
      // cout << "deleting card from deck: " 
      //   << deck.at(index).GetCardValue() 
      //   << endl;

      deck.erase(deck.begin()+index-1);
    }

    void AddCard(Card card){
      hand.push_back(card);
    }

    vector<Card> GetHand(){ return hand;}

    Card& GetCard(int i){
      return hand.at(i);
    }

    int GetDeckSize() const {return deck.size();}

  private:
    vector<Card> deck;
};
#endif