#ifndef CARD_H
#define CARD_H
#include <vector>
#include <iostream>
#include <array>
#include "math.h"
using namespace std;

class Card {
  public:
    Card(int _faceValue){
      faceValue = _faceValue;
    }

    Card(int _faceValue, bool _revealed){
      faceValue = _faceValue;
      revealed = _revealed;
    }
    
    friend ostream& operator<<(ostream& os, const Card& c){
      if (c.revealed){
        os << c.faceValue;
      }
      else {
        os << "?";
      }
      return os;
    }

    //returns all possible card values based on aces being 1 or 11
    static vector<int> GetHandValues(vector<Card> h){
      vector<int> values;
      int aces = 0;
      int sum = 0;

      //base value
      for(int i=0; i < h.size(); i++){
        if( h.at(i).revealed){
            sum += h.at(i).GetCardValue();
        }
          //  cout << "SUM="<< sum<<endl;
      }
      values.push_back(sum);
      sum=0;

      for(int i=0; i < h.size(); i++){
        // cout << "Checking aces in hand...\n";
        if(h.at(i).GetCardValue()==11 && h.at(i).revealed){
          // cout << "ace found\n";
          aces++;
        }
      }
      //subtract 10 to the base value for every ace (sets ace to 1 from 11)
      for(int i = 0; i < aces; i++){
        sum = values.at(i)-10;
        values.push_back(sum);
        sum = 0;
      }
      
      return values;
    }

    static vector<Card> MakeDeck() {
        array<int,13> _c = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
        vector<Card> _deck;
        Card* temp;
        //cout << "Making deck...\n";
        for(int i=0; i<4; i++){
          // cout << "set " << i+1 << ":\n"
          //   << "card: ";
          for(int j=0; j<13; j++){
            temp = new Card(_c[j]);
            //  cout << _c[j] << ", ";
            _deck.push_back(*temp);
          }
          // cout << endl;
        }
        //cout<< "deck finished\n";
        return _deck;
    }

    static void FlipCard(Card& c) {
      // cout << "Flipping: " << c.faceValue << endl;
      c.revealed = c.revealed ? false: true;
    }

    int GetCardValue() const{ return faceValue; }
    
  private:
    int faceValue;
    bool revealed = false;
};

#endif