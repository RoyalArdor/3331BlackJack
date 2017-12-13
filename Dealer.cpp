#include "User.h"
#include "Card.h"
#include "Player.h"
#include "Dealer.h"
#include <random>
#include <ctime>
using namespace std;


Dealer::Dealer(){
    deck = Card::MakeDeck();
    Status::INITIAL;
    id = 0;
}

void Dealer::DealFromDeck(User& player){
    srand(time(NULL));
    int deckSize = static_cast<int>(deck.size());
    int randIndex = rand()%deckSize;
    cout << "\t\tdealing card to ";
    if(player.GetID()==0){cout << "dealer." << endl;}
    else{ cout << "Player " << player.GetID() << "." << endl;}
    //cout << "dealing card from deck.(" << deck.at(randIndex).GetCardValue() <<")\n";
    player.AddCard(deck.at(randIndex));
    DeleteFromDeck(randIndex);
}

void Dealer::DeleteFromDeck(int index){
    //cout << "deleting card from deck.(" << deck.at(index).GetCardValue() <<")\n";
    deck.erase(deck.begin()+index);
}

void Dealer::ResetShuffleDeck() {
    deck.clear();
    deck = Card::MakeDeck();
}

void Dealer::AddCard(Card card){
    Card::FlipCard(card);
    hand.push_back(card);
}

void Dealer::ClearHand(){
    hand.clear();
}

vector<Card> Dealer::GetHand(){ return hand;}

Card& Dealer::GetCard(int i){
    return hand.at(i);
}

int Dealer::GetDeckSize() const {return deck.size();}

void Dealer::SetStatus(Status s) {status = s;}
Status Dealer::GetStatus() const {return status;}

int Dealer::GetID() const {return id;}