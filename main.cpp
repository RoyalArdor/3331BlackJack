#include <vector>
#include <iostream>
#include <random>
#include <array>
#include "BlackJack.h"
#include "Dealer.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"

using namespace std;

int BlackJack::playerCount = 0;
vector<Player> BlackJack::players;

int main(){
    Dealer d;
    BlackJack::PrintIntro();
    BlackJack::GetPlayerCount();
    d.initialDeal(BlackJack::players);
    cout<< "Printing\n";
    cout << User(d);
//    BlackJack::PrintTable();
    system("Pause");
}
