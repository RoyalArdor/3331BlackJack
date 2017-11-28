#include <iostream>
#include <stdexcept>
#include "BlackJack.h"
using namespace std;

int BlackJack::numOfPlayers = 0;

void BlackJack::SetNumOfPlayers(){
    cout << "How many players? (up to 5): ";
    cin >> BlackJack::numOfPlayers;
    if(BlackJack::numOfPlayers < 1 && BlackJack::numOfPlayers > 5){
        throw invalid_argument("Player number must be 1-5.");
    }
}

int BlackJack::GetNumOfPlayers(){return BlackJack::numOfPlayers;}

void BlackJack::printIntro() {
    cout << "============================"
        << "\n=  Welcome to BlackJack!!  ="
        << "\n============================" << endl;
}
