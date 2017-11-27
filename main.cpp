#include <iostream>
#include <vector>
using namespace std;

#include "Players.h"

// Global vector
vector<int> PlayerNumber;

int NumOfPlayers();
int main()
{
    cout << "============================" << endl;
    cout << "=  Welcome to BlackJack!!  =" << endl;
    cout << "============================" << endl;

    // Get amount of players
    int playerCount = NumOfPlayers();
    for(size_t i = 0; i < PlayerNumber.size(); i++){
        PlayerNumber.push_back(new Player i);
    }
}

int NumOfPlayers(){
    int count;
    cout << "How many players? (up to 5): ";
    cin >>  count;
    return count;
}
