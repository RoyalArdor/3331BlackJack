#ifndef DEALER_H
#define DEALER_H
#include "user.h"
#include "card.h"
#include "player.h"
#include <random>
#include <ctime>
using namespace std;

class Dealer : public User{
  public:
    Dealer(){
      deck = Card::MakeDeck();
      Status::INITIAL;
    }
    
    void DealFromDeck(User& player){
      srand(time(NULL));
      int deckSize = static_cast<int>(deck.size());
      int randIndex = rand()%deckSize;
      cout << "dealing card from deck: " 
        << deck.at(randIndex).GetCardValue() 
        << endl;
      cout << "RandomIndex: " 
        << randIndex 
        << endl;
      player.AddCard(deck.at(randIndex));
      DeleteFromDeck(randIndex);
    }

    void DeleteFromDeck(int index){
      cout << "deleting card from deck: " 
        << deck.at(index).GetCardValue() 
        << endl;
      cout << "RandomIndex: " 
        << index 
        << endl;
      deck.erase(deck.begin()+index-1);
    }
    void ResetShuffleDeck() {
      deck.clear();
      deck = Card::MakeDeck();
    }
    void AddCard(Card card){
      Card::FlipCard(card);
      hand.push_back(card);
    }

    void ClearHand(){
      hand.clear();
    }
    vector<Card> GetHand(){ return hand;}

    Card& GetCard(int i){
      return hand.at(i);
    }

    int GetDeckSize() const {return deck.size();}

    void SetStatus(Status s) {status = s;}
    Status GetStatus() const {return status;}
  private:
    vector<Card> deck;
};
#endif