#include <iostream>
#include <vector>
using namespace std;

#include "Players.h"
#include "BlackJack.h"
// Global vector
vector<int> PlayerNumber;

int main()
{
    BlackJack::printIntro();
    BlackJack::SetNumOfPlayers();

//    for(size_t i = 0; i < PlayerNumber.size(); i++){
//        PlayerNumber.push_back(new Players(i));
//    }

//pause
system("Pause");
}
