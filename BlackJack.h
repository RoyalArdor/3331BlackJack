
#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <string>

class BlackJack{
public:
    static void SetNumOfPlayers();
    static int GetNumOfPlayers();
    static void printIntro();
private:
    static int numOfPlayers;
};
#endif // BLACKJACK_H
