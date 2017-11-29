#ifndef BlackJack_H
#define BlackJack_H
#include <string>
#include <iostream>
#include "Dealer.h"
#include "Player.h"
using namespace std;

//Game Logic class
class BlackJack{
public:

    static void PrintIntro(){
        cout << " ======================\n"
            <<  "| Welcome to Blackjack |\n"
            <<  " ======================\n"
            << endl;
    }

    static void PrintTable(){
    cout << "============Dealer============\n"
        <<  "__________|" <<"\n"
        <<  "\n"
        <<  "\n"
        <<  "\n"
        <<  "\n"
        << endl;
    }

    static int playerCount;
    static vector<Player> players;

    static void GetPlayerCount(){
        while(playerCount<1 || playerCount>5){
            cout << "How many players. (1-5)\n";
            cin >> playerCount;
        }
    }
};

#endif
