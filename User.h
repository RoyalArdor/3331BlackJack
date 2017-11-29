#ifndef USER_H
#define USER_H
#include <vector>
#include <iostream>
#include "Card.h"
using namespace std;
//Parent of every individual
class User{
public:
    //print hand
    friend ostream& operator<<(ostream& output, const User& u){
        cout<< "printing...";
        for(auto const& c : u.getHand()){
            output << "| " << c.getFaceValue() << " |";
        }
        return output;
    }
    vector<Card> getHand()const{
        return _hand;
    }

private:
    vector<Card> _hand;
};

#endif
