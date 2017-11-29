#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
using namespace std;
//Card class
class Card {
public:
    enum class Face { TWO, THREE, FOUR, FIVE, SIX,
            SEVEN, EIGHT, NINE, TEN, JACK, QUEEN,
            KING, ACE, ENDFACE };

    Card(Face f){
        _face = f;
    }
    Card(Face f, bool r){
        _face = f;
        _revealed = r;
    }
    void setFace(Face f){_face = f;}
    Face getFace()const{return _face;}
    int getFaceValue()const{return int(_face);}
    bool isRevealed()const{return _revealed;}
    void setRevealed(bool r){_revealed = r;}

private:
    Face _face;
    bool _revealed = false;
};

#endif
