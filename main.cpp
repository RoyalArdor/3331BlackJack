#include <iostream>
#include <vector>
using namespace std;

#include "Players.h"
#include "BlackJack.h"
// Global vector
vector<Players> PlayerNumber;

int main()
{
    BlackJack::printIntro();
    BlackJack::SetNumOfPlayers();
    Players *temp;
    for(size_t i = 0; i < BlackJack::GetNumOfPlayers(); i++){
            temp = new Players(i+1);
        PlayerNumber.push_back(*temp);
        cout << "\n" << i+1 << endl;
    }

//pause
system("Pause");
}

