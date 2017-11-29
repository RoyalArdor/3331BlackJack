#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include "Card.h"
#include "Player.h"
using namespace std;

//Deck of cards class
class Deck {
public:
    void MakeDeck(){
        cout << "Making deck\n";
        for(int i = 0; i<4; i++){       //4 sets of each card
            cout << "set of deck: " << i<<"\n";
            for(int j = 0; j < 14; j++){
                cout<< "deck card: "<< int(j)<< "\n";
                //Card card(Card::Face(j));           //card stored in deck using enum for value
                //cards.push_back(card);
            }
        }
        //print deck for debug
        cout << "printing deck...\n";
        for(auto const& c : cards){
            cout << c.getFaceValue()<<", ";
        }
    }

    void DealCard(User p){
        cout << "Dealing random card\n";
        int r = rand()%int(cards.size());
        cout << "adding card to player hand\n";
        p.getHand().push_back(cards.at(r));
        cout << "erasing card from deck\n";
        cards.erase(cards.begin()+r);
    }

private:
    vector<Card> cards;
};

#endif
