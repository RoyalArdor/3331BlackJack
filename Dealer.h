#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include <iostream>
#include <string>
#include "Player.h"
#include "User.h"
#include "Deck.h"
using namespace std;
//Dealer that plays against the Players
class Dealer : public User{
public:
    Dealer(){
        _deck.MakeDeck();
    };
    //deal two cards to each player and dealer
    void initialDeal(vector<Player> players){
        for(int i = 0; i<2; i++){
            cout << "initialDeal: dealing card to dealer - " <<i<< "\n";
            _deck.DealCard(User(*this));
            for(auto const& p : players){   //for every player deal a card from deck
                cout << "initialDeal: dealing card to player\n";
                _deck.DealCard(User(p));
                p.getHand().at(i).setRevealed(true);    //reveal all player cards
            }
        }
        getHand().at(0).setRevealed(true);  //reveal just one dealer card
    }

private:
    Deck _deck;
};

#endif
